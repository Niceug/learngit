
// DrawBoard.h : DrawBoard Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CDrawBoardApp:
// �йش����ʵ�֣������ DrawBoard.cpp
//

class CDrawBoardApp : public CWinApp
{
public:
	CDrawBoardApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CDrawBoardApp theApp;
