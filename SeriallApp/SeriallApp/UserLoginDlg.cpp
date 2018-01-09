// UserLoginDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SeriallApp.h"
#include "UserLoginDlg.h"
#include "afxdialogex.h"


// CUserLoginDlg �Ի���

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


// CUserLoginDlg ��Ϣ�������


void CUserLoginDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CUserSet Userrecordset;
	CString strSQL;
	UpdateData(TRUE);
	CSeriallAppApp* ptheApp = (CSeriallAppApp*)AfxGetApp();
	//����û����Ƿ�����
	if (m_strUserName.IsEmpty())
	{
		MessageBox(_T("�������û���!"));
		m_ctrUserName.SetFocus();
		return;
	}

	if (m_strUserPassword.IsEmpty())
	{
		MessageBox(_T("����������!"));
		m_ctrUserPassword.SetFocus();
		return;
	}
	if (m_strDevice.IsEmpty())
	{
		MessageBox(_T("��ѡ���豸��!"));
		m_ctrDevice.SetFocus();
		return;
	}

	strSQL.Format(_T("select * from UserDeviceManage where UserName='%s'AND Password='%s'AND Device ='%s'"), m_strUserName, m_strUserPassword, m_strDevice);

	if (!Userrecordset.Open(AFX_DB_USE_DEFAULT_TYPE, strSQL))
	{
		MessageBox(_T("�����ݿ�ʧ��!"));
		return;
	}

	if (Userrecordset.GetRecordCount() == 0)
	{
		Userrecordset.Close();
		MessageBox(_T("�û��������������û����������豸�Ų�ƥ������������!"));
		m_ctrUserName.SetFocus();
		UpdateData(FALSE);
	}
	else
	{
		Userrecordset.Close();
		CDialogEx::OnOK();
	}
}
