#pragma once


// CLineWidthType �Ի���

class CLineWidthType : public CDialogEx
{
	DECLARE_DYNAMIC(CLineWidthType)

public:
	CLineWidthType(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLineWidthType();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LINETYPE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	UINT m_ELineWidth;
	int m_ELineType;
};
