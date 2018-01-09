
// SeriallAppDlg.cpp : ʵ���ļ�
//
#pragma warning(disable:4996)

#include "stdafx.h"
#include "SeriallApp.h"
#include "SeriallAppDlg.h"
#include "afxdialogex.h"
#include <string>
#include "UserLoginDlg.h"
#include "TempManageSet.h"
#include "TempratureDlg.h"
#include <windows.h>
#include <iostream>
using namespace std;

CWinThread * pWinThread;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HANDLE hCom;
DWORD ThreadID;
DWORD SendID;
HWND m_hwnd = GetActiveWindow();

CString readdata() {
	char str[100];//���ÿ�ζ�ȡ���ַ�
	memset(str, '\0', 100);//�������
	DWORD wCount = 100;//һ�ζ�ȡ���ֽ��� 
	BOOL bReadStat;//��Ƕ������Ƿ�ɹ�

	bReadStat = ReadFile(hCom, str, wCount, &wCount, NULL);//��str��д���ַ�
	if (!bReadStat)
	{
		AfxMessageBox(L"������ʧ��!,���ȷ���رճ���");
		exit(0);
	}
	PurgeComm(hCom, PURGE_TXABORT |
		PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
	return (CString)str;
}
CTempManageSet m_TMSet;

void SendToDB()
{
	CTime time = CTime::GetCurrentTime();
	CString strTime;
	strTime = time.Format(_T("%Y-%m-%d %H:%M:%S"));
	CString priviousTime;
	m_TMSet.AddNew();
	if (priviousTime == strTime)
	{
		m_TMSet.m_Time = strTime + '0';
	}
	m_TMSet.m_Device = _T("1725");
	m_TMSet.m_Time = strTime;
	priviousTime = strTime;
	m_TMSet.m_Temperature = "37C";
	m_TMSet.Update();
}

void UpdateUIThread(CSeriallAppDlg *p) 
{

	CString str = L"";
	CString str_previous = L"";

	while (1)
	{
		str_previous = str;
		str.Append(readdata());
		
		if (str_previous != str)
		{
			p->receive_edit.SetWindowTextW(str);
		}
	}
}

//ö�ٴ���  
void EnumerateSerialPorts(CUIntArray& ports)
{
	ports.RemoveAll();
	for (UINT i = 1; i<256; i++)
	{
		//Form the Raw device name  
		CString sPort;
		sPort.Format(_T("\\\\.\\COM%d"), i);

		//Try to open the port  
		BOOL bSuccess = FALSE;
		HANDLE hPort = ::CreateFile(sPort, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);
		if (hPort == INVALID_HANDLE_VALUE)
		{
			DWORD dwError = GetLastError();
			//Check to see if the error was because some other app had the port open or a general failure  
			if (dwError == ERROR_ACCESS_DENIED || dwError == ERROR_GEN_FAILURE)
				bSuccess = TRUE;
		}
		else
		{
			//The port was opened successfully  
			bSuccess = TRUE;
			CloseHandle(hPort);
		}
		//Add the port number to the array which will be returned  
		if (bSuccess)
			ports.Add(i);
	}
}

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSeriallAppDlg �Ի���

CSeriallAppDlg::CSeriallAppDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SERIALLAPP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
}

void CSeriallAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OPENCOMBTN, open_btn);
	DDX_Control(pDX, IDC_SENDBTN, send_btn);
	DDX_Control(pDX, IDC_CLOSECOMBTN, close_btn);
	DDX_Control(pDX, IDC_EDIT_SEND, send_edit);
	DDX_Control(pDX, IDC_COMBO2, com_combobox);
	DDX_Control(pDX, IDC_EDIT_RECEIVE, receive_edit);
}

BEGIN_MESSAGE_MAP(CSeriallAppDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPENCOMBTN, &CSeriallAppDlg::OnBnClickedOpencombtn)
	ON_BN_CLICKED(IDC_SENDBTN, &CSeriallAppDlg::OnBnClickedSendbtn)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CSeriallAppDlg ��Ϣ�������

BOOL CSeriallAppDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�
	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	com_combobox.AddString(_T("COM1"));
	com_combobox.AddString(_T("COM2"));
	com_combobox.AddString(_T("COM3"));
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CSeriallAppDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSeriallAppDlg::OnPaint()
{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		//SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0
		dc.MoveTo(230, 60);
		dc.LineTo(230, 200);
		dc.LineTo(500, 200);
		CDialogEx::OnPaint();
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSeriallAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSeriallAppDlg::OnBnClickedOpencombtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������  
	/*���ڵĳ�ʼ��*/
	CString str_com = L"";
	com_combobox.GetWindowTextW(str_com);
	hCom = CreateFile(str_com, GENERIC_READ | GENERIC_WRITE,
		0, NULL, OPEN_EXISTING, 0, NULL);   //�򿪴���  
	if (hCom == (HANDLE)-1)
	{
		MessageBox(L"��COMʧ��!");
	}
	else {
		open_btn.EnableWindow(FALSE);
		close_btn.EnableWindow(TRUE);
		send_btn.EnableWindow(TRUE);
		com_combobox.EnableWindow(FALSE);
		SetupComm(hCom, 100, 100); //���뻺����������������Ĵ�С����100 
		COMMTIMEOUTS TimeOuts;

		//�趨����ʱ  
		TimeOuts.ReadIntervalTimeout = MAXDWORD;
		TimeOuts.ReadTotalTimeoutMultiplier = 0;
		TimeOuts.ReadTotalTimeoutConstant = 0;
		//�ڶ�һ�����뻺���������ݺ���������������أ�  
		//�������Ƿ������Ҫ����ַ���  

		//�趨д��ʱ  
		TimeOuts.WriteTotalTimeoutMultiplier = 100;
		TimeOuts.WriteTotalTimeoutConstant = 500;
		SetCommTimeouts(hCom, &TimeOuts); //���ó�ʱ  
		DCB dcb;
		GetCommState(hCom, &dcb);
		dcb.BaudRate = 4800; //������Ϊ9600
		dcb.ByteSize = 8; //ÿ���ֽ���8λ  
		dcb.Parity = NOPARITY; //����żУ��λ  
		dcb.StopBits = ONESTOPBIT; //ֹͣλ  
		SetCommState(hCom, &dcb);
		PurgeComm(hCom, PURGE_TXCLEAR | PURGE_RXCLEAR);

		//�������̶߳�ȡ��������  
		HANDLE hThread_receiver;
		hThread_receiver = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)UpdateUIThread, this, 0, (unsigned long *)&ThreadID);

		//HANDLE hThread_SendToDB;
		//hThread_SendToDB = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)SendToDB, this, 0, (unsigned long *)&SendID);

		/*if (!m_TMSet.Open(AFX_DB_USE_DEFAULT_TYPE))
		{
			AfxMessageBox(_T("�����ݿ�ʧ��"));
			return;
		}*/

	}
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

//
void CSeriallAppDlg::OnBnClickedSendbtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������  
	UpdateData(true);  
	CString str_senddata = L"";
	send_edit.GetWindowTextW(str_senddata);//��Ҫ���͵�����  
	CStringA str_senddataA = "";

	/*CString ת��ΪCStringA*/
	int len = WideCharToMultiByte(CP_ACP, 0, LPCTSTR(str_senddata), -1, NULL, 0, NULL, NULL);
	char *str = new char[len];
	memset(str, 0, len * sizeof(char));
	WideCharToMultiByte(CP_ACP, 0, LPCWSTR(str_senddata), -1, str, len, NULL, NULL);
	str_senddataA = str;
	delete str;
	/*ת������*/

	int len1 = str_senddata.GetLength();
	DWORD dwBytesWrite = len1;
	COMSTAT ComStat;
	DWORD dwErrorFlags;
	BOOL bWriteStat;
	ClearCommError(hCom, &dwErrorFlags, &ComStat);
	bWriteStat = WriteFile(hCom, str_senddataA, dwBytesWrite, &
		dwBytesWrite, NULL);
	if (!bWriteStat)
	{
		MessageBox(L"���ñ����¶�ʧ��!");
	}
}