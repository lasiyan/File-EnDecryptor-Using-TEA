// DLLCreator.cpp : �ش� DLL�� �ʱ�ȭ ��ƾ�� �����մϴ�.
//

#include "stdafx.h"
#include "DLLCreator.h"
#include "tea.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: �� DLL�� MFC DLL�� ���� �������� ��ũ�Ǿ� �ִ� ���
//		MFC�� ȣ��Ǵ� �� DLL���� ���������� ��� �Լ���
//		���� �κп� AFX_MANAGE_STATE ��ũ�ΰ�
//		��� �־�� �մϴ�.
//
//		��:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �Ϲ����� �Լ� ������ ���⿡ �ɴϴ�.
//		}
//
//		�� ��ũ�δ� MFC�� ȣ���ϱ� ����
//		�� �Լ��� �ݵ�� ��� �־�� �մϴ�.
//		��, ��ũ�δ� �Լ��� ù ��° ���̾�� �ϸ� 
//		��ü ������ �����ڰ� MFC DLL��
//		ȣ���� �� �����Ƿ� ��ü ������ ����Ǳ� ����
//		���;� �մϴ�.
//
//		�ڼ��� ������
//		MFC Technical Note 33 �� 58�� �����Ͻʽÿ�.
//

// CDLLCreatorApp

BEGIN_MESSAGE_MAP(CDLLCreatorApp, CWinApp)
END_MESSAGE_MAP()


// CDLLCreatorApp ����

CDLLCreatorApp::CDLLCreatorApp()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}


// ������ CDLLCreatorApp ��ü�Դϴ�.

CDLLCreatorApp theApp;


// CDLLCreatorApp �ʱ�ȭ

BOOL CDLLCreatorApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

extern "C" __declspec(dllexport) void FileEecoding(char* FileName, char* FilePathExt,
	char* p0, char* p1, char* p2, char* p3)
{
#pragma warning (disable:4996)
#include "tea.h"

	FILE *FileCreate = NULL;
	FILE *CreatedFile = NULL;
	unsigned char buffer[9], bufferin[9];
	char OriginFullPath[512] = { NULL };
	char AfterFilePath[512] = { NULL };
	char AfterFileName[256] = { NULL };

	strcpy(OriginFullPath, FilePathExt);
	strcat(OriginFullPath, FileName);

	TEAKey[0] = atoi(p0);
	TEAKey[1] = atoi(p1);
	TEAKey[2] = atoi(p2);
	TEAKey[3] = atoi(p3);

	FileCreate = fopen(OriginFullPath, "rb+");

	strcpy(AfterFileName, "[Enc] ");
	strcat(AfterFileName, FileName);

	strcpy(AfterFilePath, strcat(FilePathExt, AfterFileName));

	CreatedFile = fopen(AfterFilePath, "wb+");

	while (fread(buffer, 1, 8, FileCreate) == 8)
	{
		for (int i = 0; i<8; i++)
		{
			bufferin[i] = buffer[i];
		}

		simpleencrypt(buffer);

		fwrite(buffer, 1, 8, CreatedFile);
	}

	// ���� ���� Ű ���� ����
	fputc(TEAKey[0], CreatedFile);
	fputc(TEAKey[1], CreatedFile);
	fputc(TEAKey[2], CreatedFile);
	fputc(TEAKey[3], CreatedFile);

	fclose(CreatedFile);
	fclose(FileCreate);
	// �Ϲ����� �Լ� ������ ���⿡ �ɴϴ�.

}
extern "C" __declspec(dllexport) bool FileDecoding(char* FileName, char* FilePathExt,
	char* p0, char* p1, char* p2, char* p3)
{
#pragma warning (disable:4996)
#include "tea.h"
	FILE *DecFileCreate = NULL;
	FILE *DecCreatedFile = NULL;
	unsigned char buffer[9], bufferin[9], bufferout[9];
	char OriginFullPath[512] = { NULL };
	char AfterFilePath[512] = { NULL };
	char AfterFileName[256] = { NULL };
	int i;

	strcat(OriginFullPath, FilePathExt);
	strcat(OriginFullPath, FileName);

	TEAKey[0] = atoi(p0);
	TEAKey[1] = atoi(p1);
	TEAKey[2] = atoi(p2);
	TEAKey[3] = atoi(p3);

	DecFileCreate = fopen(OriginFullPath, "rb+");

	int count = 0;
	fseek(DecFileCreate, -4, SEEK_END);
	for (int j = 0; j < 4; j++) {
		if (fgetc(DecFileCreate) == TEAKey[j])
			count++;
	}
	if (count == 4) {
		fseek(DecFileCreate, 0, SEEK_SET);

		strcpy(AfterFileName, "[Dec] ");
		for (int j = 6; j < strlen(FileName); j++) {
			AfterFileName[j] = FileName[j];
		}

		strcpy(AfterFilePath, strcat(FilePathExt, AfterFileName));

		DecCreatedFile = fopen(AfterFilePath, "wb+");

		while (fread(buffer, 1, 8, DecFileCreate) == 8)
		{
			for (i = 0; i < 8; i++)
			{
				bufferin[i] = buffer[i];
			}

			for (i = 0; i < 8; i++)
			{
				bufferout[i] = buffer[i];
			}
			simpledecrypt(bufferout);
			fwrite(bufferout, 1, 8, DecCreatedFile);
		}

		fclose(DecCreatedFile);
		fclose(DecFileCreate);
		// �Ϲ����� �Լ� ������ ���⿡ �ɴϴ�.

		return true;
	}
	
	return false;
}