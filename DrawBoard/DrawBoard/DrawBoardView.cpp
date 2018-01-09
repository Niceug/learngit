
// DrawBoardView.cpp : CDrawBoardView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "DrawBoard.h"
#endif

#include "DrawBoardDoc.h"
#include "DrawBoardView.h"
#include "LineWidthType.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDrawBoardView

IMPLEMENT_DYNCREATE(CDrawBoardView, CView)

BEGIN_MESSAGE_MAP(CDrawBoardView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_DLINE, &CDrawBoardView::OnDline)
	ON_COMMAND(ID_DSTRAIGHTLINE, &CDrawBoardView::OnDstraightline)
	ON_COMMAND(ID_DELLIPSE, &CDrawBoardView::OnDellipse)
	ON_COMMAND(ID_DRECTANGLE, &CDrawBoardView::OnDrectangle)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_SETCOLOR, &CDrawBoardView::OnSetcolor)
	ON_COMMAND(ID_SETLINEWIDTH, &CDrawBoardView::OnSetlinewidth)
	ON_WM_NCMOUSEMOVE()
	ON_COMMAND(ID_DHEART, &CDrawBoardView::OnDheart)
END_MESSAGE_MAP()

// CDrawBoardView 构造/析构

CDrawBoardView::CDrawBoardView()
	: m_nLineType(2)
	, OldPoint(0)
	, m_LineWidth(1)
	, m_dLineType(0)
	, LButtonDown(false)
{
	// TODO: 在此处添加构造代码

}

CDrawBoardView::~CDrawBoardView()
{
}

BOOL CDrawBoardView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CDrawBoardView 绘制

void CDrawBoardView::OnDraw(CDC* /*pDC*/)
{
	CDrawBoardDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CDrawBoardView 打印

BOOL CDrawBoardView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CDrawBoardView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CDrawBoardView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CDrawBoardView 诊断

#ifdef _DEBUG
void CDrawBoardView::AssertValid() const
{
	CView::AssertValid();
}

void CDrawBoardView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDrawBoardDoc* CDrawBoardView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrawBoardDoc)));
	return (CDrawBoardDoc*)m_pDocument;
}
#endif //_DEBUG


// CDrawBoardView 消息处理程序


void CDrawBoardView::OnDline()
{
	m_nLineType = 1;
	// TODO: 在此添加命令处理程序代码
}


void CDrawBoardView::OnDstraightline()
{
	m_nLineType = 2;
	// TODO: 在此添加命令处理程序代码
}


void CDrawBoardView::OnDellipse()
{
	m_nLineType = 3;
	// TODO: 在此添加命令处理程序代码
}


void CDrawBoardView::OnDrectangle()
{
	m_nLineType = 4;
	// TODO: 在此添加命令处理程序代码
}

void CDrawBoardView::OnDheart()
{
	m_nLineType = 5;
	// TODO: 在此添加命令处理程序代码
}

void CDrawBoardView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	LButtonDown = true;
	OldPoint = point;
	CView::OnLButtonDown(nFlags, point);
}


void CDrawBoardView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	LButtonDown = false;
	CClientDC dc(this);
	CPen MyPen(m_dLineType, m_LineWidth, m_color+100);
	CBrush MyBrush(m_color);
	dc.SelectObject(MyBrush);
	dc.SelectObject(MyPen);
	POINT aPoint[3] = { 10, 200, 20, 20, 30, 40};
	switch (m_nLineType)
	{
	case 2: dc.MoveTo(OldPoint); dc.LineTo(point); break;
	case 3: dc.Ellipse(OldPoint.x, OldPoint.y, point.x, point.y); break;
	case 4: dc.Rectangle(OldPoint.x, OldPoint.y, point.x, point.y); break;
	case 5: dc.PolyBezier(aPoint, 5);
			break;
	}
	CView::OnLButtonUp(nFlags, point);
}


void CDrawBoardView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (LButtonDown)
	{
		CClientDC dc(this);
		CPen MyPen(m_dLineType, m_LineWidth, m_color);
		dc.SelectObject(MyPen);
		switch (m_nLineType)
		{
		case 1: 
			if (abs((point.y - OldPoint.y)*(point.y - OldPoint.y) - ((point.x - OldPoint.x)*(point.x - OldPoint.x))) > 10)
			{
				dc.MoveTo(OldPoint); dc.LineTo(point); OldPoint = point;
			} 
			break;
		}
	}
	
	CView::OnMouseMove(nFlags, point);
}


void CDrawBoardView::OnSetcolor()
{
	// TODO: 在此添加命令处理程序代码
	CColorDialog CCDlg;
	if (IDOK == CCDlg.DoModal())
	{
		m_color = CCDlg.m_cc.rgbResult;
	}
}


void CDrawBoardView::OnSetlinewidth()
{
	CLineWidthType CLWT;
	CLWT.m_ELineWidth = m_LineWidth;
	CLWT.m_ELineType = m_dLineType;
	if (IDOK == CLWT.DoModal())
	{
		m_LineWidth = CLWT.m_ELineWidth;
		m_dLineType = CLWT.m_ELineType;
	}
	// TODO: 在此添加命令处理程序代码
}


