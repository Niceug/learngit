
// SeriallApp.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSeriallAppApp: 
// �йش����ʵ�֣������ SeriallApp.cpp
//

class CSeriallAppApp : public CWinApp
{
public:
	CSeriallAppApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bIsAdmin;
};

extern CSeriallAppApp theApp;