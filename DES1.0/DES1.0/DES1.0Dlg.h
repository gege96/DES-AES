
// DES1.0Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxeditbrowsectrl.h"


// CDES10Dlg 对话框
class CDES10Dlg : public CDialogEx
{
// 构造
public:
	CDES10Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DES10_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedbtnencryptfile();
	CEdit inputFile;
	afx_msg void OnEnChangeEdit1();
	CEdit encryptString;
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnBnClickedbtnencryptstring();
	CEdit encryptStringKey;
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnBnClickedbtndencryptstring();
	CEdit secretText;
	CButton dencryptStrng;
	afx_msg void OnEnChangeMfceditbrowse1();
	CMFCEditBrowseCtrl fileInput;
	CEdit fileOutput;
	
	CButton btnDencryptFile;
	CButton encryptFileButton;
	CEdit fileKey;
	afx_msg void OnEnChangeEdit7();
	CMFCEditBrowseCtrl savePath;
	CEdit secretKey;
	CMFCEditBrowseCtrl outputfile;
	afx_msg void OnBnClickedButton1();
};
