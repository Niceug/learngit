#pragma once


// CSelectGame 对话框

class CSelectGame : public CDialogEx
{
	DECLARE_DYNAMIC(CSelectGame)

public:
	CSelectGame(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSelectGame();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_START };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedGamehelp();
};
