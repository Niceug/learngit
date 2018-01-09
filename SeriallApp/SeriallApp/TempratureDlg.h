#pragma once


// CTempratureDlg 对话框

class CTempratureDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTempratureDlg)

public:
	CTempratureDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTempratureDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TEMPRATURE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_DlgDevice;
	CString m_DlgTime;
	CString m_DlgTemprature;
};
