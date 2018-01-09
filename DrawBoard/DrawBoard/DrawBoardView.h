
// DrawBoardView.h : CDrawBoardView ��Ľӿ�
//

#pragma once
#include "atltypes.h"


class CDrawBoardView : public CView
{
protected: // �������л�����
	CDrawBoardView();
	DECLARE_DYNCREATE(CDrawBoardView)

// ����
public:
	CDrawBoardDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CDrawBoardView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
protected:
	unsigned int m_nLineType;
public:
	afx_msg void OnDline();
	afx_msg void OnDstraightline();
	afx_msg void OnDellipse();
	afx_msg void OnDrectangle();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	CPoint OldPoint;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSetcolor();
	afx_msg void OnSetlinewidth();
	COLORREF m_color;
	int m_LineWidth;
	int m_dLineType;
	bool LButtonDown;
	afx_msg void OnDheart();
};

#ifndef _DEBUG  // DrawBoardView.cpp �еĵ��԰汾
inline CDrawBoardDoc* CDrawBoardView::GetDocument() const
   { return reinterpret_cast<CDrawBoardDoc*>(m_pDocument); }
#endif

