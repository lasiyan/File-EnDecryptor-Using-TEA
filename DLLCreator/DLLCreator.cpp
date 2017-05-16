// DLLCreator.cpp : 해당 DLL의 초기화 루틴을 정의합니다.
//

#include "stdafx.h"
#include "DLLCreator.h"
#include "tea.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: 이 DLL이 MFC DLL에 대해 동적으로 링크되어 있는 경우
//		MFC로 호출되는 이 DLL에서 내보내지는 모든 함수의
//		시작 부분에 AFX_MANAGE_STATE 매크로가
//		들어 있어야 합니다.
//
//		예:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 일반적인 함수 본문은 여기에 옵니다.
//		}
//
//		이 매크로는 MFC로 호출하기 전에
//		각 함수에 반드시 들어 있어야 합니다.
//		즉, 매크로는 함수의 첫 번째 문이어야 하며 
//		개체 변수의 생성자가 MFC DLL로
//		호출할 수 있으므로 개체 변수가 선언되기 전에
//		나와야 합니다.
//
//		자세한 내용은
//		MFC Technical Note 33 및 58을 참조하십시오.
//

// CDLLCreatorApp

BEGIN_MESSAGE_MAP(CDLLCreatorApp, CWinApp)
END_MESSAGE_MAP()


// CDLLCreatorApp 생성

CDLLCreatorApp::CDLLCreatorApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CDLLCreatorApp 개체입니다.

CDLLCreatorApp theApp;


// CDLLCreatorApp 초기화

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

	// 파일 끝에 키 정보 저장
	fputc(TEAKey[0], CreatedFile);
	fputc(TEAKey[1], CreatedFile);
	fputc(TEAKey[2], CreatedFile);
	fputc(TEAKey[3], CreatedFile);

	fclose(CreatedFile);
	fclose(FileCreate);
	// 일반적인 함수 본문은 여기에 옵니다.

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
		// 일반적인 함수 본문은 여기에 옵니다.

		return true;
	}
	
	return false;
}