#pragma once


// CSelectGame �Ի���

class CSelectGame : public CDialogEx
{
	DECLARE_DYNAMIC(CSelectGame)

public:
	CSelectGame(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSelectGame();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_START };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedGamehelp();
};
