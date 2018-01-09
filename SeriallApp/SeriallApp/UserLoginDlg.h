#pragma once
#include "afxwin.h"
#include "UserSet.h"

// CUserLoginDlg 对话框

class CUserLoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUserLoginDlg)

public:
	CUserLoginDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUserLoginDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USERDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strUserName;
	CString m_strUserPassword;
	CEdit m_ctrUserName;
	afx_msg void OnBnClickedOk();
	CEdit m_ctrUserPassword;
	CString m_strDevice;
	CComboBox m_ctrDevice;
};
