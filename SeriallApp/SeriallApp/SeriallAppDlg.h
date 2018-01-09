
// SeriallAppDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CSeriallAppDlg 对话框
class CSeriallAppDlg : public CDialogEx
{
// 构造
public:
	CSeriallAppDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERIALLAPP_DIALOG };
#endif

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
	afx_msg void OnBnClickedOpencombtn();
	afx_msg void OnBnClickedSendbtn();
	CButton open_btn;
//	CButton close_btn;
	CButton send_btn;
	CButton close_btn;
	CEdit send_edit;
	CComboBox com_combobox;
	CEdit receive_edit;
};
