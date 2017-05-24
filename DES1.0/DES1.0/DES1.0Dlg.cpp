
// DES1.0Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DES1.0.h"
#include "DES1.0Dlg.h"
#include "afxdialogex.h"


#include"des.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDES10Dlg �Ի���



CDES10Dlg::CDES10Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDES10Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDES10Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT3, encryptString);
	DDX_Control(pDX, IDC_EDIT4, encryptStringKey);
	DDX_Control(pDX, IDC_EDIT5, secretText);
	DDX_Control(pDX, btndencryptString, dencryptStrng);
	DDX_Control(pDX, IDC_MFCEDITBROWSE1, fileInput);
	DDX_Control(pDX, IDC_BUTTON1, btnDencryptFile);
	DDX_Control(pDX, btnEncryptFile, encryptFileButton);

	DDX_Control(pDX, IDC_EDIT7, secretKey);
	DDX_Control(pDX, IDC_MFCEDITBROWSE3, outputfile);
}

BEGIN_MESSAGE_MAP(CDES10Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(btnEncryptFile, &CDES10Dlg::OnBnClickedbtnencryptfile)
	
	ON_EN_CHANGE(IDC_EDIT3, &CDES10Dlg::OnEnChangeEdit3)
	ON_BN_CLICKED(btnEncryptString, &CDES10Dlg::OnBnClickedbtnencryptstring)
	ON_EN_CHANGE(IDC_EDIT4, &CDES10Dlg::OnEnChangeEdit4)
	ON_BN_CLICKED(btndencryptString, &CDES10Dlg::OnBnClickedbtndencryptstring)
	ON_EN_CHANGE(IDC_MFCEDITBROWSE1, &CDES10Dlg::OnEnChangeMfceditbrowse1)

	ON_BN_CLICKED(IDC_BUTTON1, &CDES10Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDES10Dlg ��Ϣ�������

BOOL CDES10Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CDES10Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDES10Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CDES10Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDES10Dlg::OnBnClickedbtnencryptfile()
{

	CString cs1, cs2, cs3;
	fileInput.GetWindowTextW(cs1);
	secretKey.GetWindowTextW(cs2);
	outputfile.GetWindowTextW(cs3);
	//fileOutput.SetWindowTextW(cs1);


	// Convert a TCHAR string to a LPCSTR
	CT2CA pszConvertedAnsiString1(cs1);
	CT2CA pszConvertedAnsiString2(cs2);
	CT2CA pszConvertedAnsiString3(cs3);
	// construct a std::string using the LPCSTR input
	std::string str1(pszConvertedAnsiString1);
	std::string str2(pszConvertedAnsiString2);
	std::string str3(pszConvertedAnsiString3);
	encyptFile(str1, str2, str3);

	//std::string str3;
	//str3 = encyptString(str1, str2);

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CDES10Dlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CDES10Dlg::OnEnChangeEdit3()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CDES10Dlg::OnBnClickedbtnencryptstring()
{
	CString cs1,cs2;
	encryptString.GetWindowTextW(cs1);
	encryptStringKey.GetWindowTextW(cs2);
	
	
	// Convert a TCHAR string to a LPCSTR
	CT2CA pszConvertedAnsiString1(cs1);
	CT2CA pszConvertedAnsiString2(cs2);
	// construct a std::string using the LPCSTR input
	std::string str1(pszConvertedAnsiString1);
	std::string str2(pszConvertedAnsiString2);
	//encyptString(str1, str2);
	std::string str3;
	str3 = encyptString(str1, str2);
	//std::string s("Hello");
	CString cs3(str3.c_str());
	secretText.SetWindowTextW(cs3);

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CDES10Dlg::OnEnChangeEdit4()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CDES10Dlg::OnBnClickedbtndencryptstring()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	CString cs1, cs2;
	secretText.GetWindowTextW(cs1);
	encryptStringKey.GetWindowTextW(cs2);


	// Convert a TCHAR string to a LPCSTR
	CT2CA pszConvertedAnsiString1(cs1);
	CT2CA pszConvertedAnsiString2(cs2);
	// construct a std::string using the LPCSTR input
	std::string str1(pszConvertedAnsiString1);
	std::string str2(pszConvertedAnsiString2);
	//encyptString(str1, str2);
	std::string str3;
	str3 = dencryptString(str1, str2);
	//std::string s("Hello");
	CString cs3(str3.c_str());
	encryptString.SetWindowTextW(cs3);

}


void CDES10Dlg::OnEnChangeMfceditbrowse1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CDES10Dlg::OnEnChangeEdit7()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CDES10Dlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	CString cs1, cs2, cs3;
	fileInput.GetWindowTextW(cs1);
	secretKey.GetWindowTextW(cs2);
	outputfile.GetWindowTextW(cs3);
	//fileOutput.SetWindowTextW(cs1);


	// Convert a TCHAR string to a LPCSTR
	CT2CA pszConvertedAnsiString1(cs1);
	CT2CA pszConvertedAnsiString2(cs2);
	CT2CA pszConvertedAnsiString3(cs3);
	// construct a std::string using the LPCSTR input
	std::string str1(pszConvertedAnsiString1);
	std::string str2(pszConvertedAnsiString2);
	std::string str3(pszConvertedAnsiString3);
	dencryptFile(str1, str2, str3);
}
