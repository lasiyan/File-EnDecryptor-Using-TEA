
// FileEnDecryptorDlg.cpp : ���� ����
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

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CFileEnDecryptorDlg ��ȭ ����



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


// CFileEnDecryptorDlg �޽��� ó����

BOOL CFileEnDecryptorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	//((CEdit*)GetDlgItem(IDC_EDIT2))->LimitText(7);

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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
		if (MessageBox(L"���α׷��� �����Ͻðڽ��ϱ�?", L"Software EXIT", MB_YESNO) == IDYES)
		{
			exit(0);
		}
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CFileEnDecryptorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CFileEnDecryptorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CFileEnDecryptorDlg::OnBnClickedButtonFilepath()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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

		FileEecoding(FileName, FilePathExt, p0, p1, p2, p3); // Encryption , ��ȣȭ
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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