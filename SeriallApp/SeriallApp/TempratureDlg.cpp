// TempratureDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SeriallApp.h"
#include "TempratureDlg.h"
#include "afxdialogex.h"


// CTempratureDlg 对话框

IMPLEMENT_DYNAMIC(CTempratureDlg, CDialogEx)

CTempratureDlg::CTempratureDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_TEMPRATURE, pParent)
	, m_DlgDevice(_T(""))
	, m_DlgTime(_T(""))
	, m_DlgTemprature(_T(""))
{

}

CTempratureDlg::~CTempratureDlg()
{
}

void CTempratureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DEVICE, m_DlgDevice);
	DDX_Text(pDX, IDC_EDIT_TIME, m_DlgTime);
	DDX_Text(pDX, IDC_EDIT_TEMPRATURE, m_DlgTemprature);
}


BEGIN_MESSAGE_MAP(CTempratureDlg, CDialogEx)
END_MESSAGE_MAP()


// CTempratureDlg 消息处理程序
