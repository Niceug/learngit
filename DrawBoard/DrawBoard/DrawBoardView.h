
// DrawBoardView.h : CDrawBoardView 类的接口
//

#pragma once
#include "atltypes.h"


class CDrawBoardView : public CView
{
protected: // 仅从序列化创建
	CDrawBoardView();
	DECLARE_DYNCREATE(CDrawBoardView)

// 特性
public:
	CDrawBoardDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CDrawBoardView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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

#ifndef _DEBUG  // DrawBoardView.cpp 中的调试版本
inline CDrawBoardDoc* CDrawBoardView::GetDocument() const
   { return reinterpret_cast<CDrawBoardDoc*>(m_pDocument); }
#endif

