// SelectGame.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Tetris.h"
#include "SelectGame.h"
#include "afxdialogex.h"

// CSelectGame �Ի���

IMPLEMENT_DYNAMIC(CSelectGame, CDialogEx)

CSelectGame::CSelectGame(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_START, pParent)
{

}

CSelectGame::~CSelectGame()
{
}

void CSelectGame::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSelectGame, CDialogEx)
END_MESSAGE_MAP()
