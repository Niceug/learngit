// TempManageSet.h : CTempManageSet 类的实现



// CTempManageSet 实现

// 代码生成在 2017年7月10日, 21:14

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
//#error 安全问题: 连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
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
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Text(pFX, _T("[Device]"), m_Device);
	RFX_Text(pFX, _T("[Time]"), m_Time);
	RFX_Text(pFX, _T("[Temperature]"), m_Temperature);

}
/////////////////////////////////////////////////////////////////////////////
// CTempManageSet 诊断

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


