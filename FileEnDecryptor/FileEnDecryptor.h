
// FileEnDecryptor.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CFileEnDecryptorApp:
// �� Ŭ������ ������ ���ؼ��� FileEnDecryptor.cpp�� �����Ͻʽÿ�.
//

class CFileEnDecryptorApp : public CWinApp
{
public:
	CFileEnDecryptorApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CFileEnDecryptorApp theApp;