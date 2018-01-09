// UserSet.h : CUserSet ���ʵ��



// CUserSet ʵ��

// ���������� 2017��7��9��, 12:23

#include "stdafx.h"
#include "UserSet.h"
IMPLEMENT_DYNAMIC(CUserSet, CRecordset)

CUserSet::CUserSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_UserName = "";
	m_Password = "";
	m_Device = "";
	m_nFields = 3;
	m_nDefaultType = dynaset;
}
//#error ��ȫ����: �����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CUserSet::GetDefaultConnect()
{
	return _T("DSN=TempManageODBC;Description=\x6e29\x5ea6\x7ba1\x7406\x6570\x636e\x6e90;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae 2015;WSID=LTPZ7M-SL7D2;DATABASE=TempManagerDB;Network=DBMSSOCN");
}

CString CUserSet::GetDefaultSQL()
{
	return _T("[dbo].[UserDeviceManage]");
}

void CUserSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Text(pFX, _T("[UserName]"), m_UserName);
	RFX_Text(pFX, _T("[Password]"), m_Password);
	RFX_Text(pFX, _T("[Device]"), m_Device);
}
/////////////////////////////////////////////////////////////////////////////
// CUserSet ���

#ifdef _DEBUG
void CUserSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CUserSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


