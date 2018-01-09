
// cFileDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "cFile.h"
#include "cFileDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
SOCKET sock;
UINT recv_thd(LPVOID p);
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


// CcFileDlg 对话框



CcFileDlg::CcFileDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CFILE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CcFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, edit1);
	DDX_Control(pDX, IDC_EDIT2, send_edit);
	DDX_Control(pDX, IDC_EDIT3, ip_edit);
	DDX_Control(pDX, IDC_btnConnect, btnconn);
}

BEGIN_MESSAGE_MAP(CcFileDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SEND, &CcFileDlg::OnBnClickedSend)
	ON_BN_CLICKED(IDC_btnConnect, &CcFileDlg::OnBnClickedbtnconnect)
END_MESSAGE_MAP()


// CcFileDlg 消息处理程序

BOOL CcFileDlg::OnInitDialog()
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
	ip_edit.SetWindowText("192.168.1.108");

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CcFileDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CcFileDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CcFileDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CcFileDlg::update(CString s)
{
	edit1.ReplaceSel(s + "\r\n");
}

UINT recv_thd(LPVOID p)
{
	int res;
	char msg[1024];
	CString s;
	CcFileDlg * dlg = (CcFileDlg *)AfxGetApp()->GetMainWnd();
	dlg->update("连接成功");

	while (1)
	{
		if ((res = recv(sock, msg, 1024, 0)) == -1)
		{
			dlg->update("失去连接");
			break;
		}
		else
		{
			msg[res] = '\0';
			dlg->update("server:" + CString(msg));
		}
	}

	//closesocket(sock);
	return 0;
}

void CcFileDlg::OnBnClickedSend()
{
	CString s;
	char * msg;
	send_edit.GetWindowText(s);
	msg = s.GetBuffer(s.GetLength());
	if (send(sock, msg, strlen(msg), 0) == SOCKET_ERROR)
	{
		update("发送失败");
	}
	else if (s == "")
	{
		MessageBox("请输入信息");
	}
	else
	{
		update("client:" + s);//消息上屏，清空输入，并重获焦点
		send_edit.SetWindowText("");
		send_edit.SetFocus();
	}
	// TODO: 在此添加控件通知处理程序代码
}


void CcFileDlg::OnBnClickedbtnconnect()
{
	WSADATA wsaData;
	SOCKADDR_IN server_addr;
	WORD wVersion;
	wVersion = MAKEWORD(2, 2);
	WSAStartup(wVersion, &wsaData);
	// WSAStartup(0x0202, &wsaData);
	CString ip;
	ip_edit.GetWindowText(ip);//取得服务器的IP地址
	server_addr.sin_addr.s_addr = inet_addr(ip);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(5150);
	if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	{
		edit1.ReplaceSel("create socket error\r\n");
	}
	if (connect(sock, (struct sockaddr *) &server_addr, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
	{
		edit1.ReplaceSel("连接失败\r\n");
	}
	else
	{
		edit1.ReplaceSel("连接成功\r\n");
		AfxBeginThread(&recv_thd, 0);
		btnconn.EnableWindow(FALSE);//按钮变灰
	}
	// TODO: 在此添加控件通知处理程序代码
}
