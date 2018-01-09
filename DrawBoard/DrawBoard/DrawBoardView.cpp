
// DrawBoardView.cpp : CDrawBoardView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
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

// CDrawBoardView ����/����

CDrawBoardView::CDrawBoardView()
	: m_nLineType(2)
	, OldPoint(0)
	, m_LineWidth(1)
	, m_dLineType(0)
	, LButtonDown(false)
{
	// TODO: �ڴ˴���ӹ������

}

CDrawBoardView::~CDrawBoardView()
{
}

BOOL CDrawBoardView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CDrawBoardView ����

void CDrawBoardView::OnDraw(CDC* /*pDC*/)
{
	CDrawBoardDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CDrawBoardView ��ӡ

BOOL CDrawBoardView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CDrawBoardView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CDrawBoardView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CDrawBoardView ���

#ifdef _DEBUG
void CDrawBoardView::AssertValid() const
{
	CView::AssertValid();
}

void CDrawBoardView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDrawBoardDoc* CDrawBoardView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrawBoardDoc)));
	return (CDrawBoardDoc*)m_pDocument;
}
#endif //_DEBUG


// CDrawBoardView ��Ϣ�������


void CDrawBoardView::OnDline()
{
	m_nLineType = 1;
	// TODO: �ڴ���������������
}


void CDrawBoardView::OnDstraightline()
{
	m_nLineType = 2;
	// TODO: �ڴ���������������
}


void CDrawBoardView::OnDellipse()
{
	m_nLineType = 3;
	// TODO: �ڴ���������������
}


void CDrawBoardView::OnDrectangle()
{
	m_nLineType = 4;
	// TODO: �ڴ���������������
}

void CDrawBoardView::OnDheart()
{
	m_nLineType = 5;
	// TODO: �ڴ���������������
}

void CDrawBoardView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	LButtonDown = true;
	OldPoint = point;
	CView::OnLButtonDown(nFlags, point);
}


void CDrawBoardView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO: �ڴ���������������
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
	// TODO: �ڴ���������������
}


