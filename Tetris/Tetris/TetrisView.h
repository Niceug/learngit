
// TetrisView.h : CTetrisView 类的接口
//

#pragma once
#include "Bin.h" 
#include "Brick.h"
#include "IBrick.h"
#include "LBrick.h"
#include "SBrick.h"
#include "OBrick.h"
#include "TBrick.h"

class CTetrisView : public CView
{
protected: // 仅从序列化创建
	CTetrisView();
	DECLARE_DYNCREATE(CTetrisView)

// 特性
public:
	CTetrisDoc* GetDocument() const;
public:
	void DrawImage(CBin* bin, unsigned char** image, CDC* pDC);

// 操作
public:

	CBin *bin; //定义游戏矩形框指针
	CBrick *activeBrick; //定义指向当前下落砖块的指针
	int gameOver; //判断游戏是否结束
	int brickInFlight; //判断砖块是否处于下落状态
	int brickType; //砖块类别
	unsigned int initOrientation; //初始状态
	int notCollide; //冲突否
	unsigned int numLines; //消的行数
	unsigned char** outputImage;
	int difficulty;

public:
	CBin *bin1;
	CBrick *activeBrick1; //定义指向当前下落砖块的指针
	int gameOver1; //判断游戏是否结束
	int brickInFlight1; //判断砖块是否处于下落状态
	int brickType1; //砖块类别
	unsigned int initOrientation1; //初始状态
	int notCollide1; //冲突否
	unsigned int numLines1; //消的行数
	unsigned char** outputImage1;

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
	virtual ~CTetrisView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnGameStart();
	afx_msg void OnDiffEasy();
	afx_msg void OnDiffMid();
	afx_msg void OnDiffSup();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	void ShowActiveBrick(CDC* dc);
	COLORREF GetLightColor(COLORREF m_crBody);
	COLORREF GetDarkColor(COLORREF m_crBody);
};

#ifndef _DEBUG  // TetrisView.cpp 中的调试版本
inline CTetrisDoc* CTetrisView::GetDocument() const
   { return reinterpret_cast<CTetrisDoc*>(m_pDocument); }
#endif

