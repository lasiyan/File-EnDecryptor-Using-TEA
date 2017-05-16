
// FileEnDecryptorDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "FileEnDecryptor.h"
#include "FileEnDecryptorDlg.h"
#include "afxdialogex.h"
#include <stdio.h>
#include <string.h>
#include <atlstr.h> 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(lib, "../x64/Release/DLLCreator.lib")
// extern "C" __declspec(dllimport) void FileEecoding(char*, char*, char*, char*, char*);
// extern "C" __declspec(dllimport) void FileDecoding(char*, char*, char*, char*, char*);
extern "C" __declspec(dllimport) void FileEecoding(char*, char*, char*, char*, char*, char*);
extern "C" __declspec(dllimport) bool FileDecoding(char*, char*, char*, char*, char*, char*);

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFileEnDecryptorDlg 대화 상자



CFileEnDecryptorDlg::CFileEnDecryptorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FILEENDECRYPTOR_DIALOG, pParent)
	, m_edFilePath(_T(""))
	, m_edPassword(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFileEnDecryptorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_edFilePath);
	DDX_Text(pDX, IDC_EDIT2, m_edPassword);
}

BEGIN_MESSAGE_MAP(CFileEnDecryptorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_FilePath, &CFileEnDecryptorDlg::OnBnClickedButtonFilepath)
	ON_BN_CLICKED(IDOK, &CFileEnDecryptorDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CFileEnDecryptorDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CFileEnDecryptorDlg 메시지 처리기

BOOL CFileEnDecryptorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	//((CEdit*)GetDlgItem(IDC_EDIT2))->LimitText(7);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CFileEnDecryptorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else if (nID == SC_CLOSE)
	{
		if (MessageBox(L"프로그램을 종료하시겠습니까?", L"Software EXIT", MB_YESNO) == IDYES)
		{
			exit(0);
		}
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CFileEnDecryptorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CFileEnDecryptorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CFileEnDecryptorDlg::OnBnClickedButtonFilepath()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString strMsg("All Files(*.*)|*.*||");
	CFileDialog FileDlg(TRUE, _T("VBL"), NULL,
		OFN_HIDEREADONLY | OFN_CREATEPROMPT | OFN_PATHMUSTEXIST | OFN_EXPLORER, strMsg);

	if (IDOK == FileDlg.DoModal())
	{
		m_edFilePath = FileDlg.GetPathName();
		_FileName = FileDlg.GetFileName();
		int i = m_edFilePath.ReverseFind('\\');
		_FilePathExt = m_edFilePath.Left(i);
		_FilePathExt += '\\';
		UpdateData(FALSE);
	}

}

bool CFileEnDecryptorDlg::chkPasswordLength(CString Cpwd) {
	char* pwd = (LPSTR)((LPCTSTR)Cpwd);
	if (strlen(pwd) == 7)
		return 1;
	else return 0;
}

void CFileEnDecryptorDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	char *FileName, *FilePathExt;
	char *p0, *p1, *p2, *p3;

	FileName = (char*)malloc(sizeof(char) * 256);
	FilePathExt = (char*)malloc(sizeof(char) * 256);

	p0 = (char*)malloc(sizeof(char) * 10);
	p1 = (char*)malloc(sizeof(char) * 10);
	p2 = (char*)malloc(sizeof(char) * 10);
	p3 = (char*)malloc(sizeof(char) * 10);

	FileName = (LPSTR)((LPCTSTR)_FileName);
	FilePathExt = (LPSTR)((LPCTSTR)_FilePathExt);
	USES_CONVERSION;
	FileName = W2A(_FileName);
	FilePathExt = W2A(_FilePathExt);
	UpdateData(TRUE);
	
	if (m_edPassword.GetLength() == _PASSWORD_LENGTH) {
		CString cp0 = m_edPassword.Left(2);
		p0 = (LPSTR)((LPCTSTR)cp0);

		CString cp1 = m_edPassword.Mid(2, 2);
		p1 = (LPSTR)((LPCTSTR)cp1);

		CString cp2 = m_edPassword.Mid(4, 2);
		p2 = (LPSTR)((LPCTSTR)cp2);

		CString cp3 = m_edPassword.Mid(6, 2);
		p3 = (LPSTR)((LPCTSTR)cp3);

		FileEecoding(FileName, FilePathExt, p0, p1, p2, p3); // Encryption , 암호화
		AfxMessageBox(L"Encrypt Complete!!");

		CDialogEx::OnOK();
	}
	else {
		AfxMessageBox(L"Please enter 7 digit password");
		GetDlgItem(IDC_EDIT2)->SetFocus();
	}
}

void CFileEnDecryptorDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	char *FileName, *FilePathExt;
	char *p0, *p1, *p2, *p3;
	FileName = (char*)malloc(sizeof(char) * 256);
	FilePathExt = (char*)malloc(sizeof(char) * 256);
	p0 = (char*)malloc(sizeof(char) * 10);
	p1 = (char*)malloc(sizeof(char) * 10);
	p2 = (char*)malloc(sizeof(char) * 10);
	p3 = (char*)malloc(sizeof(char) * 10);
	FileName = (LPSTR)((LPCTSTR)_FileName);
	FilePathExt = (LPSTR)((LPCTSTR)_FilePathExt);
	USES_CONVERSION;
	FileName = W2A(_FileName);
	FilePathExt = W2A(_FilePathExt);
	UpdateData(TRUE);

	if (m_edPassword.GetLength() == _PASSWORD_LENGTH) {
		CString cp0 = m_edPassword.Left(2);
		p0 = (LPSTR)((LPCTSTR)cp0);

		CString cp1 = m_edPassword.Mid(2, 2);
		p1 = (LPSTR)((LPCTSTR)cp1);

		CString cp2 = m_edPassword.Mid(4, 2);
		p2 = (LPSTR)((LPCTSTR)cp2);

		CString cp3 = m_edPassword.Mid(6, 2);
		p3 = (LPSTR)((LPCTSTR)cp3);
		if (FileDecoding(FileName, FilePathExt, p0, p1, p2, p3) == true) {
			AfxMessageBox(_T("Decrypt Complete!!"));
			CDialogEx::OnCancel();
		}
		else {
			AfxMessageBox(_T("Password is not correct"));
			GetDlgItem(IDC_EDIT2)->SetFocus();
		}
	}
	else {
		AfxMessageBox(L"Please enter 7 digit password");
		GetDlgItem(IDC_EDIT2)->SetFocus();
	}
}