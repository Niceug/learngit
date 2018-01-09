
// SeriallAppDlg.cpp : 实现文件
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
	char str[100];//存放每次读取的字符
	memset(str, '\0', 100);//清空数组
	DWORD wCount = 100;//一次读取的字节数 
	BOOL bReadStat;//标记读串口是否成功

	bReadStat = ReadFile(hCom, str, wCount, &wCount, NULL);//往str中写入字符
	if (!bReadStat)
	{
		AfxMessageBox(L"读串口失败!,点击确定关闭程序");
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

//枚举串口  
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

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CSeriallAppDlg 对话框

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


// CSeriallAppDlg 消息处理程序

BOOL CSeriallAppDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。
	// IDM_ABOUTBOX 必须在系统命令范围内。
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
	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	com_combobox.AddString(_T("COM1"));
	com_combobox.AddString(_T("COM2"));
	com_combobox.AddString(_T("COM3"));
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSeriallAppDlg::OnPaint()
{
		CPaintDC dc(this); // 用于绘制的设备上下文

		//SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0
		dc.MoveTo(230, 60);
		dc.LineTo(230, 200);
		dc.LineTo(500, 200);
		CDialogEx::OnPaint();
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSeriallAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSeriallAppDlg::OnBnClickedOpencombtn()
{
	// TODO: 在此添加控件通知处理程序代码  
	/*串口的初始化*/
	CString str_com = L"";
	com_combobox.GetWindowTextW(str_com);
	hCom = CreateFile(str_com, GENERIC_READ | GENERIC_WRITE,
		0, NULL, OPEN_EXISTING, 0, NULL);   //打开串口  
	if (hCom == (HANDLE)-1)
	{
		MessageBox(L"打开COM失败!");
	}
	else {
		open_btn.EnableWindow(FALSE);
		close_btn.EnableWindow(TRUE);
		send_btn.EnableWindow(TRUE);
		com_combobox.EnableWindow(FALSE);
		SetupComm(hCom, 100, 100); //输入缓冲区和输出缓冲区的大小都是100 
		COMMTIMEOUTS TimeOuts;

		//设定读超时  
		TimeOuts.ReadIntervalTimeout = MAXDWORD;
		TimeOuts.ReadTotalTimeoutMultiplier = 0;
		TimeOuts.ReadTotalTimeoutConstant = 0;
		//在读一次输入缓冲区的内容后读操作就立即返回，  
		//而不管是否读入了要求的字符。  

		//设定写超时  
		TimeOuts.WriteTotalTimeoutMultiplier = 100;
		TimeOuts.WriteTotalTimeoutConstant = 500;
		SetCommTimeouts(hCom, &TimeOuts); //设置超时  
		DCB dcb;
		GetCommState(hCom, &dcb);
		dcb.BaudRate = 4800; //波特率为9600
		dcb.ByteSize = 8; //每个字节有8位  
		dcb.Parity = NOPARITY; //无奇偶校验位  
		dcb.StopBits = ONESTOPBIT; //停止位  
		SetCommState(hCom, &dcb);
		PurgeComm(hCom, PURGE_TXCLEAR | PURGE_RXCLEAR);

		//创建新线程读取串口数据  
		HANDLE hThread_receiver;
		hThread_receiver = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)UpdateUIThread, this, 0, (unsigned long *)&ThreadID);

		//HANDLE hThread_SendToDB;
		//hThread_SendToDB = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)SendToDB, this, 0, (unsigned long *)&SendID);

		/*if (!m_TMSet.Open(AFX_DB_USE_DEFAULT_TYPE))
		{
			AfxMessageBox(_T("打开数据库失败"));
			return;
		}*/

	}
	// TODO: 在此添加控件通知处理程序代码
}

//
void CSeriallAppDlg::OnBnClickedSendbtn()
{
	// TODO: 在此添加控件通知处理程序代码  
	UpdateData(true);  
	CString str_senddata = L"";
	send_edit.GetWindowTextW(str_senddata);//需要发送到数据  
	CStringA str_senddataA = "";

	/*CString 转换为CStringA*/
	int len = WideCharToMultiByte(CP_ACP, 0, LPCTSTR(str_senddata), -1, NULL, 0, NULL, NULL);
	char *str = new char[len];
	memset(str, 0, len * sizeof(char));
	WideCharToMultiByte(CP_ACP, 0, LPCWSTR(str_senddata), -1, str, len, NULL, NULL);
	str_senddataA = str;
	delete str;
	/*转换结束*/

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
		MessageBox(L"设置报警温度失败!");
	}
}