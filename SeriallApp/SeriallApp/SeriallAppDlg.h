
// SeriallAppDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CSeriallAppDlg �Ի���
class CSeriallAppDlg : public CDialogEx
{
// ����
public:
	CSeriallAppDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERIALLAPP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
