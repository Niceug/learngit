#pragma once


// CTempratureDlg �Ի���

class CTempratureDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTempratureDlg)

public:
	CTempratureDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTempratureDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TEMPRATURE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_DlgDevice;
	CString m_DlgTime;
	CString m_DlgTemprature;
};
