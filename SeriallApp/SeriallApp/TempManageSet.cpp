// TempManageSet.h : CTempManageSet ���ʵ��



// CTempManageSet ʵ��

// ���������� 2017��7��10��, 21:14

#include "stdafx.h"
#include "TempManageSet.h"
IMPLEMENT_DYNAMIC(CTempManageSet, CRecordset)

CTempManageSet::CTempManageSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_Device = "";
	m_Time;
	m_Temperature = "";
	m_nFields = 3;
	m_nDefaultType = dynaset;
}
//#error ��ȫ����: �����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CTempManageSet::GetDefaultConnect()
{
	return _T("DSN=TempManageODBC;Description=\x6e29\x5ea6\x7ba1\x7406\x6570\x636e\x6e90;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae 2015;WSID=LTPZ7M-SL7D2;DATABASE=TempManagerDB;Network=DBMSSOCN");
}

CString CTempManageSet::GetDefaultSQL()
{
	return _T("[dbo].[TempManage]");
}

void CTempManageSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Text(pFX, _T("[Device]"), m_Device);
	RFX_Text(pFX, _T("[Time]"), m_Time);
	RFX_Text(pFX, _T("[Temperature]"), m_Temperature);

}
/////////////////////////////////////////////////////////////////////////////
// CTempManageSet ���

#ifdef _DEBUG
void CTempManageSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CTempManageSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


