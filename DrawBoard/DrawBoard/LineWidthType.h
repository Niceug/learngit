#pragma once


// CLineWidthType 对话框

class CLineWidthType : public CDialogEx
{
	DECLARE_DYNAMIC(CLineWidthType)

public:
	CLineWidthType(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLineWidthType();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LINETYPE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	UINT m_ELineWidth;
	int m_ELineType;
};
