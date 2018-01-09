#pragma once
#include "afxwin.h"
#include "UserSet.h"

// CUserLoginDlg �Ի���

class CUserLoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUserLoginDlg)

public:
	CUserLoginDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUserLoginDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USERDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
