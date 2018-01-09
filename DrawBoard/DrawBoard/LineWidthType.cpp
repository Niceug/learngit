// LineWidthType.cpp : 实现文件
//

#include "stdafx.h"
#include "DrawBoard.h"
#include "LineWidthType.h"
#include "afxdialogex.h"


// CLineWidthType 对话框

IMPLEMENT_DYNAMIC(CLineWidthType, CDialogEx)

CLineWidthType::CLineWidthType(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LINETYPE, pParent)
	, m_ELineWidth(0)
	, m_ELineType(0)
{

}

CLineWidthType::~CLineWidthType()
{
}

void CLineWidthType::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITLINEWIDTH, m_ELineWidth);
	DDV_MinMaxUInt(pDX, m_ELineWidth, 0, 40);
	DDX_Radio(pDX, IDC_RADIO1, m_ELineType);
}


BEGIN_MESSAGE_MAP(CLineWidthType, CDialogEx)
END_MESSAGE_MAP()


// CLineWidthType 消息处理程序
