// UserLoginDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SeriallApp.h"
#include "UserLoginDlg.h"
#include "afxdialogex.h"


// CUserLoginDlg 对话框

IMPLEMENT_DYNAMIC(CUserLoginDlg, CDialogEx)

CUserLoginDlg::CUserLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_USERDLG, pParent)
	, m_strUserName(_T(""))
	, m_strUserPassword(_T(""))
	, m_strDevice(_T(""))
{

}

CUserLoginDlg::~CUserLoginDlg()
{
}

void CUserLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_strUserName);
	DDX_Text(pDX, IDC_EDIT_USERPASSWORD, m_strUserPassword);
	DDX_Control(pDX, IDC_EDIT_USERNAME, m_ctrUserName);
	DDX_Control(pDX, IDC_EDIT_USERPASSWORD, m_ctrUserPassword);
	DDX_CBString(pDX, IDC_COMBO1, m_strDevice);
	DDX_Control(pDX, IDC_COMBO1, m_ctrDevice);
	if (m_strDevice.IsEmpty())
	{
		m_ctrDevice.AddString(_T("1725"));
		m_ctrDevice.AddString(_T("1726"));
		m_ctrDevice.AddString(_T("1727"));
	}
}


BEGIN_MESSAGE_MAP(CUserLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CUserLoginDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CUserLoginDlg 消息处理程序


void CUserLoginDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CUserSet Userrecordset;
	CString strSQL;
	UpdateData(TRUE);
	CSeriallAppApp* ptheApp = (CSeriallAppApp*)AfxGetApp();
	//检查用户名是否输入
	if (m_strUserName.IsEmpty())
	{
		MessageBox(_T("请输入用户名!"));
		m_ctrUserName.SetFocus();
		return;
	}

	if (m_strUserPassword.IsEmpty())
	{
		MessageBox(_T("请输入密码!"));
		m_ctrUserPassword.SetFocus();
		return;
	}
	if (m_strDevice.IsEmpty())
	{
		MessageBox(_T("请选择设备号!"));
		m_ctrDevice.SetFocus();
		return;
	}

	strSQL.Format(_T("select * from UserDeviceManage where UserName='%s'AND Password='%s'AND Device ='%s'"), m_strUserName, m_strUserPassword, m_strDevice);

	if (!Userrecordset.Open(AFX_DB_USE_DEFAULT_TYPE, strSQL))
	{
		MessageBox(_T("打开数据库失败!"));
		return;
	}

	if (Userrecordset.GetRecordCount() == 0)
	{
		Userrecordset.Close();
		MessageBox(_T("用户名或密码错误或用户名密码与设备号不匹配请重新输入!"));
		m_ctrUserName.SetFocus();
		UpdateData(FALSE);
	}
	else
	{
		Userrecordset.Close();
		CDialogEx::OnOK();
	}
}
