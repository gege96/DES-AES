
// DES1.0Dlg.cpp : 实现文件
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


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CDES10Dlg 对话框



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


// CDES10Dlg 消息处理程序

BOOL CDES10Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDES10Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
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

	// TODO:  在此添加控件通知处理程序代码
}


void CDES10Dlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CDES10Dlg::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
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

	// TODO:  在此添加控件通知处理程序代码
}


void CDES10Dlg::OnEnChangeEdit4()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CDES10Dlg::OnBnClickedbtndencryptstring()
{
	// TODO:  在此添加控件通知处理程序代码

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
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CDES10Dlg::OnEnChangeEdit7()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CDES10Dlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码

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
