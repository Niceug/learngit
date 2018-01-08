
// TetrisView.h : CTetrisView ��Ľӿ�
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
protected: // �������л�����
	CTetrisView();
	DECLARE_DYNCREATE(CTetrisView)

// ����
public:
	CTetrisDoc* GetDocument() const;
public:
	void DrawImage(CBin* bin, unsigned char** image, CDC* pDC);

// ����
public:

	CBin *bin; //������Ϸ���ο�ָ��
	CBrick *activeBrick; //����ָ��ǰ����ש���ָ��
	int gameOver; //�ж���Ϸ�Ƿ����
	int brickInFlight; //�ж�ש���Ƿ�������״̬
	int brickType; //ש�����
	unsigned int initOrientation; //��ʼ״̬
	int notCollide; //��ͻ��
	unsigned int numLines; //��������
	unsigned char** outputImage;
	int difficulty;

public:
	CBin *bin1;
	CBrick *activeBrick1; //����ָ��ǰ����ש���ָ��
	int gameOver1; //�ж���Ϸ�Ƿ����
	int brickInFlight1; //�ж�ש���Ƿ�������״̬
	int brickType1; //ש�����
	unsigned int initOrientation1; //��ʼ״̬
	int notCollide1; //��ͻ��
	unsigned int numLines1; //��������
	unsigned char** outputImage1;

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
	virtual ~CTetrisView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // TetrisView.cpp �еĵ��԰汾
inline CTetrisDoc* CTetrisView::GetDocument() const
   { return reinterpret_cast<CTetrisDoc*>(m_pDocument); }
#endif

