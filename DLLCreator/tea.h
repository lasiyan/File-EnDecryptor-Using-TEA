// Implement Tiny Encryption Algorithm

#pragma once
#include <stdint.h>
#define DELTA 0x9e3779b9
#define MX ((z>>5^y<<2) + (y>>3^z<<4)) ^ ((sum^y) + (k[(p&3)^e] ^ z));

typedef unsigned int uint32_t;
static uint32_t TEAKey[4];
void encrypt(uint32_t* v, const uint32_t* k);
void decrypt(uint32_t* v, const uint32_t* k);
void encryptBlock(uint8_t * data, uint32_t * len, uint32_t * key);
void decryptBlock(uint8_t * data, uint32_t * len, uint32_t * key);
void btea(uint32_t *v, int n, uint32_t const k[4]);

void simpleencrypt(unsigned char * buffer);
void simpledecrypt(unsigned char * buffer);



/* encrypt
*   Encrypt 64 bits with a 128 bit key using TEA
*   From http://en.wikipedia.org/wiki/Tiny_Encryption_Algorithm
* Arguments:
*   v - array of two 32 bit uints to be encoded in place
*   k - array of four 32 bit uints to act as key
* Returns:
*   v - encrypted result
* Side effects:
*   None
*/
void encrypt(uint32_t* v, const uint32_t* k) {
	uint32_t v0 = v[0], v1 = v[1], sum = 0, i;           /* set up */
	uint32_t delta = 0x9e3779b9;                     /* a key schedule constant */
	uint32_t k0 = k[0], k1 = k[1], k2 = k[2], k3 = k[3];   /* cache key */
	for (i = 0; i < 32; i++) {                       /* basic cycle start */
		sum += delta;
		v0 += ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
		v1 += ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
	}                                              /* end cycle */
	v[0] = v0; v[1] = v1;
}



/* decrypt
*   Decrypt 64 bits with a 128 bit key using TEA
*   From http://en.wikipedia.org/wiki/Tiny_Encryption_Algorithm
* Arguments:
*   v - array of two 32 bit uints to be decoded in place
*   k - array of four 32 bit uints to act as key
* Returns:
*   v - decrypted result
* Side effects:
*   None
*/
void decrypt(uint32_t* v, const uint32_t* k) {
	uint32_t v0 = v[0], v1 = v[1], sum = 0xC6EF3720, i;  /* set up */
	uint32_t delta = 0x9e3779b9;                     /* a key schedule constant */
	uint32_t k0 = k[0], k1 = k[1], k2 = k[2], k3 = k[3];   /* cache key */
	for (i = 0; i<32; i++) {                         /* basic cycle start */
		v1 -= ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
		v0 -= ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
		sum -= delta;
	}                                              /* end cycle */
	v[0] = v0; v[1] = v1;
}


/* encryptBlock
*   Encrypts byte array data of length len with key key using TEA
* Arguments:
*   data - pointer to 8 bit data array to be encrypted - SEE NOTES
*   len - length of array
*   key - Pointer to four integer array (16 bytes) holding TEA key
* Returns:
*   data - encrypted data held here
*   len - size of the new data array
* Side effects:
*   Modifies data and len
* NOTES:
* data size must be equal to or larger than ((len + 7) / 8) * 8 + 8
* TEA encrypts in 8 byte blocks, so it must include enough space to
* hold the entire data to pad out to an 8 byte boundary, plus another
* 8 bytes at the end to give the length to the decrypt algorithm.
*
*  - Shortcut - make sure that data is at least len + 15 bytes in size.
*/
void encryptBlock(uint8_t * data, uint32_t * len, uint32_t * key)
{
	uint32_t blocks, i;
	uint32_t * data32;

	// treat the data as 32 bit unsigned integers
	data32 = (uint32_t *)data;

	// Find the number of 8 byte blocks, add one for the length
	blocks = (((*len) + 7) / 8) + 1;

	// Set the last block to the original data length
	data32[(blocks * 2) - 1] = *len;

	// Set the encrypted data length
	*len = blocks * 8;

	for (i = 0; i< blocks; i++)
	{
		encrypt(&data32[i * 2], key);
	}
}

/* decryptBlock
*   Decrypts byte array data of length len with key key using TEA
* Arguments:
*   data - pointer to 8 bit data array to be decrypted - SEE NOTES
*   len - length of array
*   key - Pointer to four integer array (16 bytes) holding TEA key
* Returns:
*   data - decrypted data held here
*   len - size of the new data array
* Side effects:
*   Modifies data and len
* NOTES:
*   None
*/
void decryptBlock(uint8_t * data, uint32_t * len, uint32_t * key)
{
	uint32_t blocks, i;
	uint32_t * data32;

	// treat the data as 32 bit unsigned integers
	data32 = (uint32_t *)data;

	// Find the number of 8 byte blocks
	blocks = (*len) / 8;

	for (i = 0; i< blocks; i++)
	{
		decrypt(&data32[i * 2], key);
	}

	// Return the length of the original data
	*len = data32[(blocks * 2) - 1];
}

void btea(uint32_t *v, int n, uint32_t const k[4]) {
	uint32_t y, z, sum;
	unsigned p, rounds, e;
	if (n > 1) {          /* Coding Part */
		rounds = 6 + 52 / n;
		sum = 0;
		z = v[n - 1];
		do {
			sum += DELTA;
			e = (sum >> 2) & 3;
			for (p = 0; p < n - 1; p++)
				y = v[p + 1], z = v[p] += MX;
			y = v[0];
			z = v[n - 1] += MX;
		} while (--rounds);
	}
	else if (n < -1) {  /* Decoding Part */
		n = -n;
		rounds = 6 + 52 / n;
		sum = rounds*DELTA;
		y = v[0];
		do {
			e = (sum >> 2) & 3;
			for (p = n - 1; p > 0; p--)
				z = v[p - 1], y = v[p] -= MX;
			z = v[n - 1];
			y = v[0] -= MX;
		} while ((sum -= DELTA) != 0);
	}
}

void simpleencrypt(unsigned char * buffer)
{
	uint32_t datablock[2];

	datablock[0] = (buffer[0] << 24) | (buffer[1] << 16) | (buffer[2] << 8) | (buffer[3]);
	datablock[1] = (buffer[4] << 24) | (buffer[5] << 16) | (buffer[6] << 8) | (buffer[7]);

	encrypt(datablock, TEAKey);

	buffer[0] = (char)((datablock[0] >> 24) & 0xFF);
	buffer[1] = (char)((datablock[0] >> 16) & 0xFF);
	buffer[2] = (char)((datablock[0] >> 8) & 0xFF);
	buffer[3] = (char)((datablock[0]) & 0xFF);
	buffer[4] = (char)((datablock[1] >> 24) & 0xFF);
	buffer[5] = (char)((datablock[1] >> 16) & 0xFF);
	buffer[6] = (char)((datablock[1] >> 8) & 0xFF);
	buffer[7] = (char)((datablock[1]) & 0xFF);
}

void simpledecrypt(unsigned char * buffer)
{
	uint32_t datablock[2];

	datablock[0] = (buffer[0] << 24) | (buffer[1] << 16) | (buffer[2] << 8) | (buffer[3]);
	datablock[1] = (buffer[4] << 24) | (buffer[5] << 16) | (buffer[6] << 8) | (buffer[7]);

	decrypt(datablock, TEAKey);

	buffer[0] = (char)((datablock[0] >> 24) & 0xFF);
	buffer[1] = (char)((datablock[0] >> 16) & 0xFF);
	buffer[2] = (char)((datablock[0] >> 8) & 0xFF);
	buffer[3] = (char)((datablock[0]) & 0xFF);
	buffer[4] = (char)((datablock[1] >> 24) & 0xFF);
	buffer[5] = (char)((datablock[1] >> 16) & 0xFF);
	buffer[6] = (char)((datablock[1] >> 8) & 0xFF);
	buffer[7] = (char)((datablock[1]) & 0xFF);
}