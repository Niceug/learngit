
// cFileDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CcFileDlg 对话框
class CcFileDlg : public CDialogEx
{
// 构造
public:
	CcFileDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CFILE_DIALOG };
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
	void update(CString s);
private:
	CEdit edit1;
	CEdit send_edit;
	CEdit ip_edit;
	CButton btnconn;
public:
	afx_msg void OnBnClickedSend();
	afx_msg void OnBnClickedbtnconnect();
};
