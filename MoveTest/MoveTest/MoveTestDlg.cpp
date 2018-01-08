
// MoveTestDlg.cpp : 实现文件
//m_

#include "stdafx.h"
#include "MoveTest.h"
#include "MoveTestDlg.h"
#include "afxdialogex.h"
#include "Setting.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define BKLocation_xy 0
#define WidthAndHigh 15
#define SizeOfQiZi  25

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
int g_Brick[WidthAndHigh][WidthAndHigh];
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


// CMoveTestDlg 对话框



CMoveTestDlg::CMoveTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MOVETEST_DIALOG, pParent)
	, m_MousePoint(1000)
	, OldPoint(0)
	, m_ButtonDownRL(0)
	, m_DoubleGame(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMoveTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMoveTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_BN_CLICKED(IDC_RESTART, &CMoveTestDlg::OnBnClickedRestart)
	ON_BN_CLICKED(IDC_DOUBLEGAME, &CMoveTestDlg::OnBnClickedDoublegame)
	ON_BN_CLICKED(IDC_SETTING, &CMoveTestDlg::OnBnClickedSetting)
	ON_BN_CLICKED(IDC_BKMUSIC, &CMoveTestDlg::OnBnClickedBkmusic)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, &CMoveTestDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMoveTestDlg 消息处理程序

BOOL CMoveTestDlg::OnInitDialog()
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
	MoveWindow(0, 0, (WidthAndHigh + 1) *60, (WidthAndHigh) *60 - 20);		//设置窗口大小
	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMoveTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMoveTestDlg::OnPaint()
{
		CPaintDC dc(this);
		CBitmap bmp;
		bmp.LoadBitmap(IDB_BITMAP2);
		CBrush m_brush;
		m_brush.CreatePatternBrush(&bmp);
		CBrush* pOldBrush = dc.SelectObject(&m_brush);
		CRect rect;
		GetClientRect(&rect);
		dc.Rectangle(0, 0, rect.Width(),rect.Height()); // 这些参数可以调整图片添加位置和大小
		dc.SelectObject(pOldBrush);
		//画棋盘
		CPen pen(PS_SOLID, 2, RGB(0, 0, 0));
		CPen pen1(PS_SOLID, 1, RGB(0, 0, 0));
		dc.SelectObject(pen);
		dc.MoveTo(BKLocation_xy, BKLocation_xy);
		for (int i = 0; i < WidthAndHigh; i++)
		{
			for (int j = 0; j < WidthAndHigh + 1; j++)
			{
				if (j >= WidthAndHigh)
				{
					dc.MoveTo(BKLocation_xy, BKLocation_xy + j * 60);
					dc.LineTo(BKLocation_xy, BKLocation_xy + j * 60);
				}
				else
				dc.LineTo(BKLocation_xy +j * 60, BKLocation_xy +i * 60);
			}
		}

		dc.MoveTo(BKLocation_xy, BKLocation_xy);
		for (int i = 0; i < WidthAndHigh; i++)
		{
			for (int j = 0; j < WidthAndHigh + 1; j++)
			{
				if (j >= WidthAndHigh)
				{
					dc.MoveTo(BKLocation_xy + i * 60, BKLocation_xy);
					dc.LineTo(BKLocation_xy + i * 60, BKLocation_xy);
				}
				else
				dc.LineTo(BKLocation_xy +i * 60, BKLocation_xy +j * 60);
			}
		}
		dc.SelectObject(pen1);
		//绘制棋子
		CBrush brush(RGB(50, 50, 50));
		CBrush brush1(RGB(255, 255, 255));
		for (int i = 0; i < WidthAndHigh + 1; i++)
		{
			for (int j = 0; j < WidthAndHigh + 1; j++)
			{
				if (g_Brick[i][j] == 1)
				{
					dc.SelectObject(&brush);
					dc.Ellipse(i * 60 - SizeOfQiZi, j * 60 - SizeOfQiZi, i * 60 + SizeOfQiZi, j * 60 + SizeOfQiZi);
				}

				if (g_Brick[i][j] == 2)
				{
					dc.SelectObject(&brush1);
					dc.Ellipse(i * 60 - SizeOfQiZi, j * 60 - SizeOfQiZi, i * 60 + SizeOfQiZi, j * 60 + SizeOfQiZi);
				}

				if (g_Brick[i][j] == 3)
				{
					dc.SelectObject(&brush1);
					dc.Ellipse(i * 60 - SizeOfQiZi, j * 60 - SizeOfQiZi, i * 60 + SizeOfQiZi, j * 60 + SizeOfQiZi);
				}
			}
		}
	CDialogEx::OnPaint();
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMoveTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//玩家1控制鼠标左键,默认为人机对战
void CMoveTestDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CTime time = CTime::GetCurrentTime();
	int q = int(time.GetSecond());
	int p = int(time.GetSecond()) + 1;
	int Location_x = ((q + 1) % 4) + 4;
	int Location_y = ((p + 1) % 4) + 4;
	m_ButtonDownRL = 0;
	m_MousePoint = point;
	PlaySound(_T("C:\\Users\\hasee\\Documents\\Visual Studio 2015\\Projects\\MoveTest\\MoveTest\\res\\落地声.wav"), NULL, SND_FILENAME | SND_ASYNC);
	//棋子落子位置
	SetQiZiLocation(m_ButtonDownRL, m_MousePoint);
	//SetTimer(0, 1000, NULL);
	if (m_DoubleGame == false)
	{
		RobotPlayer(Location_x, Location_y);
	}
	Invalidate(false);
	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 1 && g_Brick[i][j + 1] == 1 && g_Brick[i][j + 2] == 1 && g_Brick[i][j + 3] == 1 && g_Brick[i][j + 4] == 1)
			{
				MessageBox(_T("玩家1----Win!"));   return;   return;
			}
			if (g_Brick[i][j] == 1 && g_Brick[i+ 1][j ] == 1 && g_Brick[i + 2][j] == 1 && g_Brick[i + 3][j] == 1 && g_Brick[i+ 4][j] == 1)
			{
				MessageBox(_T("玩家1----Win!"));   return;
			}
			if (g_Brick[i][j] == 1 && g_Brick[i + 1][j + 1] == 1 && g_Brick[i + 2][j + 2] == 1 && g_Brick[i + 3][j + 3] == 1 && g_Brick[i + 4][j + 4] == 1)
			{
				MessageBox(_T("玩家1----Win!"));   return;
			}
			if (g_Brick[i][j] == 1 && g_Brick[i - 1][j + 1] == 1 && g_Brick[i - 2][j + 2] == 1 && g_Brick[i - 3][j + 3] == 1 && g_Brick[i - 4][j + 4] == 1)
			{
				MessageBox(_T("玩家1----Win!"));   return;
			}

//判断电脑胜利
			if (g_Brick[i][j] == 3 && g_Brick[i][j + 1] == 3 && g_Brick[i][j + 2] == 3 && g_Brick[i][j + 3] == 3 && g_Brick[i][j + 4] == 3)
			{
				MessageBox(_T("电脑----Win!"));   return;
			}
			if (g_Brick[i][j] == 3 && g_Brick[i + 1][j] == 3 && g_Brick[i + 2][j] == 3 && g_Brick[i + 3][j] == 3 && g_Brick[i + 4][j] == 3)
			{
				MessageBox(_T("电脑----Win!"));   return;
			}
			if (g_Brick[i][j] == 3 && g_Brick[i + 1][j + 1] == 3 && g_Brick[i + 2][j + 2] == 3 && g_Brick[i + 3][j + 3] == 3 && g_Brick[i + 4][j + 4] == 3)
			{
				MessageBox(_T("电脑----Win!"));   return;
			}
			if (g_Brick[i][j] == 3 && g_Brick[i - 1][j + 1] == 3 && g_Brick[i - 2][j + 2] == 3 && g_Brick[i - 3][j + 3] == 3 && g_Brick[i - 4][j + 4] == 3)
			{
				MessageBox(_T("电脑----Win!"));   return;
			}
		}
		CDialogEx::OnLButtonDown(nFlags, point);
}


//玩家对战玩家2控制鼠标右键
void CMoveTestDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_DoubleGame == true)
	{
		m_ButtonDownRL = 1;
		m_MousePoint = point;
		SetQiZiLocation(m_ButtonDownRL, m_MousePoint);
		Invalidate(false);
		for (int i = 0; i < WidthAndHigh; i++)
			for (int j = 0; j < WidthAndHigh; j++)
			{
				if (g_Brick[i][j] == 2 && g_Brick[i][j + 1] == 2 && g_Brick[i][j + 2] == 2 && g_Brick[i][j + 3] == 2 && g_Brick[i][j + 4] == 2)
				{
					MessageBox(_T("玩家2--Win!"));   return;
				}
				if (g_Brick[i][j] == 2 && g_Brick[i + 1][j] == 2 && g_Brick[i + 2][j] == 2 && g_Brick[i + 3][j] == 2 && g_Brick[i + 4][j] == 2)
				{
					MessageBox(_T("玩家2--Win!"));   return;
				}
				if (g_Brick[i][j] == 2 && g_Brick[i + 1][j + 1] == 2 && g_Brick[i + 2][j + 2] == 2 && g_Brick[i + 3][j + 3] == 2 && g_Brick[i + 4][j + 4] == 2)
				{
					MessageBox(_T("玩家2--Win!"));   return;
				}
				if (g_Brick[i][j] == 2 && g_Brick[i - 1][j + 1] == 2 && g_Brick[i - 2][j + 2] == 2 && g_Brick[i - 3][j + 3] == 2 && g_Brick[i - 4][j + 4] == 2)
				{
					MessageBox(_T("玩家2--Win!"));   return;
				}
			}
		
	}
	CDialogEx::OnRButtonDown(nFlags, point);
}

//重新开始游戏
void CMoveTestDlg::OnBnClickedRestart()
{
	for (int i = 0; i < WidthAndHigh; i++)
	{
		for (int j = 0; j < WidthAndHigh; j++)
		{
			g_Brick[i][j] = 0;
		}
	}
	
	Invalidate();
	// TODO: 在此添加控件通知处理程序代码
}

//////////////////////////////////////////////////////
/////////////////////////////各种判断/////////////////
//////////////////////////////////////////////////////

//判断玩家连子数并作出对策
void CMoveTestDlg::RobotPlayer(int Location_x, int Location_y)
{

//判断玩家连子数
	if (Robot4Qizi() == 0)//AI没有4个子
	{
		//玩家斜着4个子1
		for (int i = 0; i < WidthAndHigh; i++)
			for (int j = 0; j < WidthAndHigh; j++)
			{
				if (g_Brick[i][j] == 1 && g_Brick[i + 1][j + 1] == 1 && g_Brick[i + 2][j + 2] == 1 && g_Brick[i + 3][j + 3] == 1)
				{
					if (g_Brick[i + 4][j + 4] == 0 && g_Brick[i - 1][j - 1] == 0)
					{
						if (Robot3QiZi() == 0)
						{
							AIPlay(Location_x, Location_y);
							return;
						}
						else
							return;
					}
					if (g_Brick[i + 4][j + 4] == 0 && g_Brick[i - 1][j - 1] != 0)
					{
						if (i + 4 < WidthAndHigh && j + 4 < WidthAndHigh)
						{
							g_Brick[i + 4][j + 4] = 3;
							return;
						}
							
					}
					if (g_Brick[i + 4][j + 4] != 0 && g_Brick[i - 1][j - 1] == 0)
					{
						if (i - 1 >= 0 && j - 1 >= 0)
						{
							g_Brick[i - 1][j - 1] = 3;
							return;
						}
					}
					if (g_Brick[i + 4][j + 4] != 0 && g_Brick[i - 1][j - 1] != 0)
					{
						if (Robot3QiZi() == 0)
						{
							AIPlay(Location_x, Location_y);
							return;
						}
						else
							return;
					}
				}
			}

		//玩家斜着4个子2
		for (int i = 0; i < WidthAndHigh; i++)
			for (int j = 0; j < WidthAndHigh; j++)
			{
				if (g_Brick[i][j] == 1 && g_Brick[i - 1][j + 1] == 1 && g_Brick[i - 2][j + 2] == 1 && g_Brick[i - 3][j + 3] == 1)
				{
					//MessageBox(_T("玩家斜着4个子"));
					if (g_Brick[i - 4][j + 4] == 0 && g_Brick[i + 1][j - 1] == 0)
					{

						if (Robot3QiZi() == 0)
						{
							AIPlay(Location_x, Location_y);
							return;
						}
						else
							return;
					}
					if (g_Brick[i + 1][j - 1] != 0 && g_Brick[i - 4][j + 4] == 0)
					{
						if (i - 4 >=0 && j + 4 < WidthAndHigh)
						{
							g_Brick[i - 4][j + 4] = 3;
							return;
						}
					}
					if (g_Brick[i + 1][j - 1] == 0 && g_Brick[i - 4][j + 4] != 0)
					{
						if (i + 1 < WidthAndHigh && j - 1>=0)
						{
							g_Brick[i + 1][j - 1] = 3;
							return;
						}
					}
					if (g_Brick[i - 4][j + 4] != 0 && g_Brick[i + 1][j - 1] != 0)
					{
						if (Robot3QiZi() == 0)
						{
							AIPlay(Location_x, Location_y);
							return;
						}
						else
							return;
					}
				}
			}
		//玩家竖着4个子
		for (int i = 0; i < WidthAndHigh; i++)
			for (int j = 0; j < WidthAndHigh; j++)
			{
				if (g_Brick[i][j] == 1 && g_Brick[i][j + 1] == 1 && g_Brick[i][j + 2] == 1 && g_Brick[i][j + 3] == 1)
				{
					if (g_Brick[i][j + 4] == 0 && g_Brick[i][j - 1] == 0)
					{
						if (Robot3QiZi() == 0)
						{
							AIPlay(Location_x, Location_y);
							return;
						}
						else
							return;
					}
					else if (g_Brick[i][j - 1] != 0 && g_Brick[i][j + 4] == 0)
					{
						if (j + 4 < WidthAndHigh)
						{
							g_Brick[i][j + 4] = 3;
							return;
						}
					}
					else if (g_Brick[i][j - 1] == 0 && g_Brick[i][j + 4] != 0)
					{
						if (j - 1 >= 0)
						{
							g_Brick[i][j - 1] = 3;
							return;
						}
					}
					else if (g_Brick[i][j - 1] != 0 && g_Brick[i][j + 4] != 0)
						if (Robot3QiZi() == 0)
						{
							AIPlay(Location_x, Location_y);
							return;
						}
						else
							return;
				}
			}

		//玩家横着4个子
		for (int i = 0; i < WidthAndHigh; i++)
			for (int j = 0; j < WidthAndHigh; j++)
			{
				if (g_Brick[i][j] == 1 && g_Brick[i + 1][j] == 1 && g_Brick[i + 2][j] == 1 && g_Brick[i + 3][j] == 1)
				{
					if (g_Brick[i + 4][j] == 0 && g_Brick[i - 1][j] == 0)
					{
						if (Robot3QiZi() == 0)
						{
							AIPlay(Location_x, Location_y);
							return;
						}
						else
							return;
					}
					if (g_Brick[i - 1][j] != 0 && g_Brick[i + 4][j] == 0)
					{
						if (i + 4 < WidthAndHigh)
						{
							g_Brick[i + 4][j] = 3;
							return;
						}
					}
					if (g_Brick[i - 1][j] == 0 && g_Brick[i + 4][j] != 0)
					{
						if (i - 1 >=0)
						{
							g_Brick[i - 1][j] = 3;
							return;
						}
					}
					if (g_Brick[i - 1][j] != 0 && g_Brick[i + 4][j] != 0)
						if (Robot3QiZi() == 0)
						{
							AIPlay(Location_x, Location_y);
							return;
						}
						else
							return;
				}
			}

		if (0 == Robot3QiZi())//AI没有3个子
		{
//判断玩家是否有3个子
			//玩家三子情况
			//1101型
			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i - 1][j - 1] != 3 && g_Brick[i][j] == 1 && g_Brick[i + 1][j + 1] == 0 && g_Brick[i + 2][j + 2] == 1 && g_Brick[i + 3][j + 3] == 1 && g_Brick[i + 4][j + 4] != 3)
					{
						if (i + 1 < WidthAndHigh && j + 1 < WidthAndHigh)
						{
							g_Brick[i + 1][j + 1] = 3;
							return;
						}
					}
				}
			//1011型
			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i - 1][j - 1] != 3 && g_Brick[i][j] == 1 && g_Brick[i + 1][j + 1] == 1 && g_Brick[i + 2][j + 2] == 0 && g_Brick[i + 3][j + 3] == 1 && g_Brick[i + 4][j + 4] != 3)
					{
						if (i + 2 < WidthAndHigh && j + 2 < WidthAndHigh)
						{
							g_Brick[i + 2][j + 2] = 3;
							return;
						}
					}
				}
			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i + 1][j - 1] != 3 && g_Brick[i][j] == 1 && g_Brick[i - 1][j + 1] == 0 && g_Brick[i - 2][j + 2] == 1 && g_Brick[i - 3][j + 3] == 1 && g_Brick[i - 4][j + 4] != 3)
					{
						if (i - 1 >= 0 && j + 1 < WidthAndHigh)
						{
							g_Brick[i - 1][j + 1] = 3;
							return;
						}
					}
				}
			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i + 1][j - 1] != 3 && g_Brick[i][j] == 1 && g_Brick[i - 1][j + 1] == 1 && g_Brick[i - 2][j + 2] == 0 && g_Brick[i - 3][j + 3] == 1 && g_Brick[i - 4][j + 4] != 3)
					{
						if (i - 2 >= 0 && j + 2 < WidthAndHigh)
						{
							g_Brick[i - 2][j + 2] = 3;
							return;
						}
					}
				}
			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i][j - 1] != 3 && g_Brick[i][j] == 1 && g_Brick[i][j + 1] == 0 && g_Brick[i][j + 2] == 1 && g_Brick[i][j + 3] == 1 && g_Brick[i][j + 4] != 3)
					{
						if (j + 1 < WidthAndHigh)
						{
							g_Brick[i][j + 1] = 3;
							return;
						}
					}
				}
			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i][j - 1] != 3 && g_Brick[i][j] == 1 && g_Brick[i][j + 1] == 1 && g_Brick[i][j + 2] == 0 && g_Brick[i][j + 3] == 1 && g_Brick[i][j + 4] != 3)
					{
						if (j + 2 < WidthAndHigh)
						{
							g_Brick[i][j + 2] = 3;
							return;
						}
					}
				}
			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i - 1][j] != 3 && g_Brick[i][j] == 1 && g_Brick[i + 1][j] == 0 && g_Brick[i + 2][j] == 1 && g_Brick[i + 3][j] == 1 && g_Brick[i + 4][j] != 3)
					{
						if (i + 1 < WidthAndHigh)
						{
							g_Brick[i + 1][j] = 3;
							return;
						}
					}
				}

			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i - 1][j] != 3 && g_Brick[i][j] == 1 && g_Brick[i + 1][j] == 1 && g_Brick[i + 2][j] == 0 && g_Brick[i + 3][j] == 1 && g_Brick[i + 4][j] != 3)
					{
						if (i + 2 < WidthAndHigh)
						{
							g_Brick[i + 2][j] = 3;
							return;
						}
					}
				}
			//玩家竖着3个子
			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{

					if (g_Brick[i][j] == 1 && g_Brick[i][j + 1] == 1 && g_Brick[i][j + 2] == 1)
					{
						//MessageBox(_T("玩家竖着3个子"));
						if (g_Brick[i][j + 3] == 0 && g_Brick[i][j - 1] == 0)
						{
							if (j + 3 < WidthAndHigh)
							{
								g_Brick[i][j + 3] = 3;
								return;
							}
						}
					}
				}
			//玩家横着3个子
			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i][j] == 1 && g_Brick[i + 1][j] == 1 && g_Brick[i + 2][j] == 1)
					{
						//MessageBox(_T("玩家横着3个子"));
						if (g_Brick[i - 1][j] == 0 && g_Brick[i + 3][j] == 0)
						{
							if (i + 3 < WidthAndHigh)
							{
								g_Brick[i + 3][j] = 3;
								return;
							}
						}
					}
				}

			//玩家斜着3个子
			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i][j] == 1 && g_Brick[i + 1][j + 1] == 1 && g_Brick[i + 2][j + 2] == 1)
					{
						//MessageBox(_T("玩家斜着3个子"));
						if (g_Brick[i - 1][j - 1] == 0 && g_Brick[i + 3][j + 3] == 0)
						{
							if (i + 3 < WidthAndHigh && j + 3 < WidthAndHigh)
							{
								g_Brick[i + 3][j + 3] = 3;
								return;
							}
						}
					}
				}
			//玩家斜着3个子
			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i][j] == 1 && g_Brick[i + 1][j - 1] == 1 && g_Brick[i + 2][j - 2] == 1)
					{
						//MessageBox(_T("玩家斜着3个子"));
						if (g_Brick[i - 1][j + 1] == 0 && g_Brick[i + 3][j - 3] == 0)
						{
							if (i + 3 < WidthAndHigh && j - 3 >= 0)
							{
								g_Brick[i + 3][j - 3] = 3;
								return;
							}
						}
					}
				}

			//玩家斜着3个子
			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i][j] == 1 && g_Brick[i - 1][j + 1] == 1 && g_Brick[i - 2][j + 2] == 1)
					{
						//MessageBox(_T("玩家斜着3个子"));
						if (g_Brick[i + 1][j - 1] == 0 && g_Brick[i - 3][j + 3] == 0)
						{
							if (i -3 >= 0 && j + 3 < WidthAndHigh)
							{
								g_Brick[i - 3][j + 3] = 3;
								return;
							}
						}
					}
				}

			//玩家斜着2个子
			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i + 4][j] == 1 && g_Brick[i][j] == 1 && g_Brick[i + 1][j + 1] == 1 && g_Brick[i + 3][j + 1] == 1)
					{
						if (g_Brick[i + 2][j + 2] == 0)
						{
							//MessageBox(_T("1"));
							if (i + 2 < WidthAndHigh && j + 2 < WidthAndHigh)
							{
								g_Brick[i + 2][j + 2] = 3;
								return;
							}
						}
					}
				}

			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i + 2][j] == 1 && g_Brick[i][j] == 1 && g_Brick[i - 1][j + 1] == 1 && g_Brick[i + 3][j + 1] == 1)
					{
						if (g_Brick[i + 1][j - 1] == 0)
						{
							if (i + 1 < WidthAndHigh && j - 1 >= 0)
							{
								//MessageBox(_T("2"));
								g_Brick[i + 1][j - 1] = 3;
								return;
							}
						}
					}
				}

			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i + 2][j] == 1 && g_Brick[i][j] == 1 && g_Brick[i + 1][j + 1] == 1 && g_Brick[i + 2][j + 1] == 1)
					{
						if (g_Brick[i + 2][j + 2] == 0)
						{
							if (i + 2 < WidthAndHigh && j + 2 < WidthAndHigh)
							{
								//MessageBox(_T("3"));
								g_Brick[i + 2][j + 2] = 3;
								return;
							}
						}
					}
				}
			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i - 1][j] == 1 && g_Brick[i][j] == 1 && g_Brick[i + 1][j + 1] == 1 && g_Brick[i - 1][j + 1] == 1)
					{
						if (g_Brick[i - 1][j - 1] == 0)
						{
							if (i - 1 >= 0 && j - 1 >= 0)
							{
								//MessageBox(_T("4"));
								g_Brick[i - 1][j - 1] = 3;
								return;
							}
						}
					}
				}

			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i][j + 4] == 1 && g_Brick[i][j] == 1 && g_Brick[i + 1][j + 1] == 1 && g_Brick[i + 1][j + 3] == 1)
					{
						if (g_Brick[i + 2][j + 2] == 0)
						{
							if (i + 2 < WidthAndHigh && j + 2 < WidthAndHigh)
							{
								//MessageBox(_T("5"));
								g_Brick[i + 2][j + 2] = 3;
								return;
							}
						}
					}
				}

			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i][j - 2] == 1 && g_Brick[i][j] == 1 && g_Brick[i + 1][j + 1] == 1 && g_Brick[i + 1][j - 3] == 1)
					{
						if (g_Brick[i + 2][j + 2] == 0)
						{
							if (i - 1 >= 0 && j - 1 >= 0)
							{
								//MessageBox(_T("6"));
								g_Brick[i - 1][j - 1] = 3;
								return;
							}
						}
					}
				}

			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i - 1][j] == 1 && g_Brick[i][j] == 1 && g_Brick[i][j + 1] == 1 && g_Brick[i - 2][j + 1] == 1)
					{
						if (g_Brick[i][j - 1] == 0)
						{
							if (j -1 >= 0)
							{
								//MessageBox(_T("7"));
								g_Brick[i][j - 1] = 3;
								return;
							}
						}
					}
				}
			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i][j - 1] == 1 && g_Brick[i][j] == 1 && g_Brick[i + 1][j] == 1 && g_Brick[i + 2][j - 1] == 1)
					{
						if (g_Brick[i][j + 1] == 0)
						{
							if (j + 1 < WidthAndHigh)
							{
								//MessageBox(_T("8"));
								g_Brick[i][j + 1] = 3;
								return;
							}
						}
					}
				}

			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i - 1][j] == 1 && g_Brick[i][j] == 1 && g_Brick[i][j + 1] == 1 && g_Brick[i - 1][j + 2] == 1)
					{
						if (g_Brick[i + 1][j] == 0)
						{
							if (i + 1 < WidthAndHigh)
							{
								//MessageBox(_T("9"));
								g_Brick[i + 1][j] = 3;
								return;
							}
						}
					}
				}

			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i + 1][j] == 1 && g_Brick[i][j] == 1 && g_Brick[i][j + 1] == 1 && g_Brick[i + 1][j + 2] == 1)
					{
						if (g_Brick[i - 1][j] == 0)
						{
							if (i - 1 >= 0)
							{
								//MessageBox(_T("10"));
								g_Brick[i - 1][j] = 3;
								return;
							}
						}
					}
				}

			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i + 1][j + 2] == 1 && g_Brick[i][j] == 1 && g_Brick[i + 1][j + 1] == 1 && g_Brick[i][j + 2] == 1)
					{
						if (g_Brick[i + 2][j + 2] == 0)
						{
							if (i + 2 < WidthAndHigh && j + 2 < WidthAndHigh)
							{
								//MessageBox(_T("11"));
								g_Brick[i + 2][j + 2] = 3;
								return;
							}
						}
					}
				}

			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i + 1][j - 1] == 1 && g_Brick[i][j] == 1 && g_Brick[i][j + 1] == 1 && g_Brick[i + 1][j + 1] == 1)
					{
						if (g_Brick[i - 1][j + 1] == 0)
						{
							if (i - 1>= 0 && j + 1 < WidthAndHigh)
							{
								//MessageBox(_T("12"));
								g_Brick[i - 1][j + 1] = 3;
								return;
							}
						}
					}
				}

			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i][j - 1] == 1 && g_Brick[i][j] == 1 && g_Brick[i - 1][j + 2] == 1 && g_Brick[i - 2][j + 3] == 1)
					{
						if (g_Brick[i][j + 1] == 0)
						{
							if (j + 1 < WidthAndHigh)
							{
								//MessageBox(_T("13"));
								g_Brick[i][j + 1] = 3;
								return;
							}
						}
					}
				}

			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i][j - 1] == 1 && g_Brick[i][j] == 1 && g_Brick[i + 1][j + 2] == 1 && g_Brick[i + 2][j + 3] == 1)
					{
						if (g_Brick[i][j + 1] == 0)
						{
							if (j + 1 < WidthAndHigh)
							{
								//MessageBox(_T("14"));
								g_Brick[i][j + 1] = 3;
								return;
							}
						}
					}
				}

			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i - 1][j + 1] == 1 && g_Brick[i][j] == 1 && g_Brick[i + 2][j - 1] == 1 && g_Brick[i + 3][j - 1] == 1)
					{
						if (g_Brick[i + 1][j - 1] == 0)
						{
							if (i + 1 < WidthAndHigh && j - 1 >= 0)
							{
								//MessageBox(_T("15"));
								g_Brick[i + 1][j - 1] = 3;
								return;
							}
						}
					}
				}

			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i - 1][j] == 1 && g_Brick[i][j] == 1 && g_Brick[i + 2][j + 1] == 1 && g_Brick[i + 3][j + 2] == 1)
					{
						if (g_Brick[i + 1][j] == 0)
						{
							if (i + 1 < WidthAndHigh)
							{
								//MessageBox(_T("16"));
								g_Brick[i + 1][j] = 3;
								return;
							}
						}
					}
				}

			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i + 1][j + 3] == 1 && g_Brick[i][j] == 1 && g_Brick[i - 1][j - 1] == 1 && g_Brick[i + 1][j + 2] == 1)
					{
						if (g_Brick[i + 1][j + 1] == 0)
						{
							if (i + 1 < WidthAndHigh && j + 1 < WidthAndHigh)
							{
								//MessageBox(_T("17"));
								g_Brick[i + 1][j + 1] = 3;
								return;
							}
						}
					}
				}

			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i - 1][j + 3] == 1 && g_Brick[i][j] == 1 && g_Brick[i + 1][j - 1] == 1 && g_Brick[i - 1][j + 2] == 1)
					{
						if (g_Brick[i - 1][j + 1] == 0)
						{
							if (i - 1>=0 && j + 1 < WidthAndHigh)
							{
								//MessageBox(_T("18"));
								g_Brick[i - 1][j + 1] = 3;
								return;
							}
						}
					}
				}

			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i + 2][j + 1] == 1 && g_Brick[i][j] == 1 && g_Brick[i + 1][j + 1] == 1 && g_Brick[i + 3][j + 1] == 1)
					{
						if (g_Brick[i + 2][j + 2] == 0)
						{
							if (i + 2 < WidthAndHigh && j + 2 < WidthAndHigh)
							{
								//MessageBox(_T("19"));
								g_Brick[i + 2][j + 2] = 3;
								return;
							}
						}
					}
				}

			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i - 1][j] == 1 && g_Brick[i][j] == 1 && g_Brick[i + 2][j - 1] == 1 && g_Brick[i + 3][j - 2] == 1)
					{
						if (g_Brick[i + 1][j] == 0)
						{
							if (i + 1 < WidthAndHigh)
							{
								//MessageBox(_T("20"));
								g_Brick[i + 1][j] = 3;
								return;
							}
						}
					}
				}

			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i - 1][j] == 1 && g_Brick[i][j] == 1 && g_Brick[i + 1][j - 1] == 1 && g_Brick[i + 1][j - 2] == 1)
					{
						if (g_Brick[i + 1][j] == 0)
						{
							if (i + 1 < WidthAndHigh)
							{
								//MessageBox(_T("21"));
								g_Brick[i + 1][j] = 3;
								return;
							}
						}
					}
				}

			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i][j - 1] == 1 && g_Brick[i][j] == 1 && g_Brick[i + 1][j + 1] == 1 && g_Brick[i + 2][j + 1] == 1)
					{
						if (g_Brick[i][j + 1] == 0)
						{
							if (j + 1 < WidthAndHigh)
							{
								//MessageBox(_T("22"));
								g_Brick[i][j + 1] = 3;
								return;
							}
						}
					}
				}

			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i - 1][j] == 1 && g_Brick[i][j] == 1 && g_Brick[i + 1][j + 1] == 1 && g_Brick[i + 1][j + 2] == 1)
					{
						if (g_Brick[i + 1][j] == 0)
						{
							if (i + 1 < WidthAndHigh)
							{
								//MessageBox(_T("23"));
								g_Brick[i + 1][j] = 3;
								return;
							}
						}
					}
				}

			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i][j - 1] == 1 && g_Brick[i][j] == 1 && g_Brick[i + 1][j - 1] == 1 && g_Brick[i + 2][j - 1] == 1)
					{
						if (g_Brick[i][j - 1] == 0)
						{
							if (j - 1 >= 0)
							{
								//MessageBox(_T("24"));
								g_Brick[i][j - 1] = 3;
								return;
							}
						}
					}
				}

			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i - 1][j] == 1 && g_Brick[i][j] == 1 && g_Brick[i + 2][j] == 1 && g_Brick[i + 3][j] == 1)
					{
						if (g_Brick[i + 1][j] == 0)
						{
							if (i + 1 < WidthAndHigh)
							{
								//MessageBox(_T("25"));
								g_Brick[i + 1][j] = 3;
								return;
							}
						}
					}
				}

			for (int i = 0; i < WidthAndHigh; i++)
				for (int j = 0; j < WidthAndHigh; j++)
				{
					if (g_Brick[i][j - 1] == 1 && g_Brick[i][j] == 1 && g_Brick[i][j + 2] == 1 && g_Brick[i][j + 3] == 1)
					{
						if (g_Brick[i][j + 1] == 0)
						{
							if (j + 1 < WidthAndHigh)
							{
								//MessageBox(_T("26"));
								g_Brick[i][j + 1] = 3;
								return;
							}
						}
					}
				}
			//以上情况都不符合，玩家没有3个子,AI自己下
			AIPlay(Location_x, Location_y);
			return;
		}
		else
			return;
	}
	else
		return;
}

void CMoveTestDlg::OnBnClickedDoublegame()
{
	m_DoubleGame = true;
	// TODO: 在此添加控件通知处理程序代码
}


//AI4子情况
int CMoveTestDlg::Robot4Qizi()
{
	//AI斜着4个子
	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{

			if (g_Brick[i][j] == 3 && g_Brick[i + 1][j + 1] == 3 && g_Brick[i + 2][j + 2] == 3 && g_Brick[i + 3][j + 3] == 3)
			{
				if (g_Brick[i + 4][j + 4] == 0)
				{
					if (i + 4 < WidthAndHigh && j + 4 < WidthAndHigh)
					{
						g_Brick[i + 4][j + 4] = 3;
						return 1;
					}
				}
				else if (g_Brick[i - 1][j - 1] == 0)
				{
					if (i - 1 >= 0 && j - 1 >= 0)
					{
						g_Brick[i - 1][j - 1] = 3;
						return 1;
					}
				}
				else if (g_Brick[i + 4][j + 4] != 0 && g_Brick[i - 1][j - 1] != 0)
				{
					break;
				}
			}
		}

	//AI斜着4个子
	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3 && g_Brick[i - 1][j + 1] == 3 && g_Brick[i - 2][j + 2] == 3 && g_Brick[i - 3][j + 3] == 3)
			{
				if (g_Brick[i - 4][j + 4] == 0)
				{
					if (i - 4 >= 0 && j + 4 < WidthAndHigh)
					{
						g_Brick[i - 4][j + 4] = 3;
						return 1;
					}
				}
				else if (g_Brick[i + 1][j - 1] == 0)
				{
					if (i + 1 < WidthAndHigh && j - 1 >= 0)
					{
						g_Brick[i + 1][j - 1] = 3;
						return 1;
					}
				}
				else if (g_Brick[i - 4][j + 4] != 0 && g_Brick[i + 1][j - 1] != 0)
				{
					break;
				}
			}
		}

	//横着有4个子
	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3 && g_Brick[i][j + 1] == 3 && g_Brick[i][j + 2] == 3 && g_Brick[i][j + 3] == 3)
			{
				if (g_Brick[i][j + 4] == 0)
				{
					if (j + 4 < WidthAndHigh)
					{
						g_Brick[i][j + 4] = 3;
						return 1;
					}
				}
				else if (g_Brick[i][j - 1] == 0)
				{
					if (j - 1 >= 0)
					{
						g_Brick[i][j - 1] = 3;
						return 1;
					}
				}
				if (g_Brick[i][j + 4] != 0 && g_Brick[i][j - 1] != 0)
				{
					break;
				}
			}
		}

	//竖着有4个子
	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3 && g_Brick[i + 1][j] == 3 && g_Brick[i + 2][j] == 3 && g_Brick[i + 3][j] == 3)
			{
				if (g_Brick[i + 4][j] == 0)
				{
					if (i + 4 < WidthAndHigh)
					{
						g_Brick[i + 4][j] = 3;
						return 1;
					}
				}
				if (g_Brick[i - 1][j] == 0)
				{
					if (i - 1 >= 0)
					{
						g_Brick[i - 1][j] = 3;
						return 1;
					}
				}
				if (g_Brick[i + 4][j] != 0 && g_Brick[i - 1][j] != 0)
				{
					break;
				}
			}
		}
	return 0;
}


//AI三子情况
int CMoveTestDlg::Robot3QiZi()
{
	//斜着WidthAndHigh01
	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3 && g_Brick[i + 1][j + 1] == 0 && g_Brick[i + 2][j + 2] == 3 && g_Brick[i + 3][j + 3] == 3)
			{
				if (g_Brick[i - 1][j - 1] != 1)
				{
					if (i + 1 < WidthAndHigh && j + 1 < WidthAndHigh)
					{
						g_Brick[i + 1][j + 1] = 3;
						return 1;
					}
				}
				if (g_Brick[i + 4][j + 4] != 1)
				{
					if (i + 1 < WidthAndHigh && j + 1 < WidthAndHigh)
					{
						g_Brick[i + 1][j + 1] = 3;
						return 1;
					}
				}
				if (g_Brick[i + 4][j + 4] == 1 && g_Brick[i - 1][j - 1] == 1)
					break;
			}
		}

	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3 && g_Brick[i + 1][j + 1] == 3 && g_Brick[i + 2][j + 2] == 0 && g_Brick[i + 3][j + 3] == 3)
			{
				if (g_Brick[i - 1][j - 1] != 1)
				{
					if (i + 2 < WidthAndHigh && j + 2 < WidthAndHigh)
					{
						g_Brick[i + 2][j + 2] = 3;
						return 1;
					}
				}
				if (g_Brick[i + 4][j + 4] != 1)
				{
					if (i + 2 < WidthAndHigh && j + 2 < WidthAndHigh)
					{
						g_Brick[i + 2][j + 2] = 3;
						return 1;
					}
				}
				if (g_Brick[i + 4][j + 4] == 1 && g_Brick[i - 1][j - 1] == 1)
					break;
			}
		}
	//斜着WidthAndHigh01
	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3 && g_Brick[i - 1][j + 1] == 0 && g_Brick[i - 2][j + 2] == 3 && g_Brick[i - 3][j + 3] == 3)
			{
				if (g_Brick[i + 1][j - 1] != 1)
				{
					if (i - 1 >= 0 && j + 1 < WidthAndHigh)
					{
						g_Brick[i - 1][j + 1] = 3;
						return 1;
					}
				}
				if (g_Brick[i - 4][j + 4] != 1)
				{
					if (i - 1 >= 0 && j + 1 < WidthAndHigh)
					{
						g_Brick[i - 1][j + 1] = 3;
						return 1;
					}
				}
				if (g_Brick[i - 4][j + 4] == 1 && g_Brick[i + 1][j - 1] == 1)
					break;
			}
		}

	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3 && g_Brick[i - 1][j + 1] == 3 && g_Brick[i - 2][j + 2] == 0 && g_Brick[i - 3][j + 3] == 3)
			{
				if (g_Brick[i + 1][j - 1] != 1)
				{
					if (i - 2 >= 0 && j + 2 < WidthAndHigh)
					{
						g_Brick[i - 2][j + 2] = 3;
						return 1;
					}
				}
				if (g_Brick[i - 4][j + 4] != 1)
				{
					if (i - 2 >= 0 && j + 2 < WidthAndHigh)
					{
						g_Brick[i - 2][j + 2] = 3;
						return 1;
					}
				}
				if (g_Brick[i - 4][j + 4] == 1 && g_Brick[i + 1][j - 1] == 1)
					break;
			}
		}
	//横着1101
	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3 && g_Brick[i][j + 1] == 0 && g_Brick[i][j + 2] == 3 && g_Brick[i][j + 3] == 3)
			{
				if (g_Brick[i][j - 1] != 1)
				{
					if (j + 1 < WidthAndHigh)
					{
						g_Brick[i][j + 1] = 3;
						return 1;
					}
				}
				if (g_Brick[i][j + 4] != 1)
				{
					if (j + 1 < WidthAndHigh)
					{
						g_Brick[i][j + 1] = 3;
						return 1;
					}
				}
				if (g_Brick[i][j + 4] == 1 && g_Brick[i][j - 1] == 1)
					break;
			}
		}

	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3 && g_Brick[i][j + 1] == 3 && g_Brick[i][j + 2] == 0 && g_Brick[i][j + 3] == 3)
			{
				if (g_Brick[i][j - 1] != 1)
				{
					if (j + 2 < WidthAndHigh)
					{
						g_Brick[i][j + 2] = 3;
						return 1;
					}
				}
				if (g_Brick[i][j + 4] != 1)
				{
					if (j + 2 < WidthAndHigh)
					{
						g_Brick[i][j + 2] = 3;
						return 1;
					}
				}
				if (g_Brick[i][j + 4] == 1 && g_Brick[i][j - 1] == 1)
					break;
			}
		}
	//竖着WidthAndHigh01
	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3 && g_Brick[i + 1][j] == 0 && g_Brick[i + 2][j] == 3 && g_Brick[i + 3][j] == 3)
			{
				if (g_Brick[i - 1][j] != 1)
				{
					if (j + 1 < WidthAndHigh)
					{
						g_Brick[i + 1][j] = 3;
						return 1;
					}
				}
				if (g_Brick[i + 4][j] != 1)
				{
					if (i + 1 < WidthAndHigh)
					{
						g_Brick[i + 1][j] = 3;
						return 1;
					}
				}
				if (g_Brick[i + 4][j] == 1 && g_Brick[i - 1][j] == 1)
					break;
			}
		}
	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3 && g_Brick[i + 1][j] == 3 && g_Brick[i + 2][j] == 0 && g_Brick[i + 3][j] == 3)
			{
				if (g_Brick[i - 1][j] != 1)
				{
					if (i + 2 < WidthAndHigh)
					{
						g_Brick[i + 2][j] = 3;
						return 1;
					}
				}
				if (g_Brick[i + 4][j] != 1)
				{
					if (i + 2 < WidthAndHigh)
					{
						g_Brick[i + 2][j] = 3;
						return 1;
					}
				}
				if (g_Brick[i + 4][j] == 1 && g_Brick[i - 1][j] == 1)
					break;
			}
		}
	//处理三个子的情况
	//AI斜着三个子
	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3 && g_Brick[i + 1][j + 1] == 3 && g_Brick[i + 2][j + 2] == 3)
			{
				if (g_Brick[i + 3][j + 3] == 0)
				{
					if (j + 3 < WidthAndHigh && i + 3 < WidthAndHigh)
					{
						g_Brick[i + 3][j + 3] = 3;
						return 1;
					}
				}
				else if (g_Brick[i - 1][j - 1] == 0)
				{
					if (i- 1 >= 0 && j- 1>=0)
					{
						g_Brick[i - 1][j - 1] = 3;
						return 1;
					}
				}
				else if (g_Brick[i + 3][j + 3] == 1 && g_Brick[i - 1][j - 1] == 1)
				{
					break;
				}
			}
		}

	//AI斜着三个子
	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3 && g_Brick[i - 1][j + 1] == 3 && g_Brick[i - 2][j + 2] == 3)
			{
				if (g_Brick[i - 3][j + 3] == 0)
				{
					if (j + 3 < WidthAndHigh && i - 3 >= 0)
					{
						g_Brick[i - 3][j + 3] = 3;
						return 1;
					}
				}
				else if (g_Brick[i + 1][j - 1] == 0)
				{
					if (j + 1 < WidthAndHigh && i - 1 >= 0)
					{
						g_Brick[i + 1][j - 1] = 3;
						return 1;
					}
				}
				else if (g_Brick[i - 3][j + 3] == 1 && g_Brick[i + 1][j - 1] == 1)
				{
					break;
				}
			}
		}


	//横着有3个子
	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3 && g_Brick[i][j + 1] == 3 && g_Brick[i][j + 2] == 3)
			{
				if (g_Brick[i][j + 3] == 0)
				{
					if (j + 3 < WidthAndHigh)
					{
						g_Brick[i][j + 3] = 3;
						return 1;
					}
				}
				else if (g_Brick[i][j - 1] == 0)
				{
					if (j - 1 >= 0)
					{
						g_Brick[i][j - 1] = 3;
						return 1;
					}
				}
				if (g_Brick[i][j + 3] == 1 && g_Brick[i][j - 1] == 1)
				{
					break;
				}
			}
		}
	//竖着有3个子
	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3 && g_Brick[i + 1][j] == 3 && g_Brick[i + 2][j] == 3)
			{
				if (g_Brick[i + 3][j] == 0)
				{
					if (i + 3 < WidthAndHigh)
					{
						g_Brick[i + 3][j] = 3;
						return 1;
					}
				}
				if (g_Brick[i - 1][j] == 0)
				{
					if (i - 1 >= 0)
					{
						g_Brick[i - 1][j] = 3;
						return 1;
					}
				}
				if (g_Brick[i + 3][j] == 1 && g_Brick[i - 1][j] == 1)
				{
					break;
				}
			}
		}
	return 0;
}


//AI2子情况
bool CMoveTestDlg::AIPlay(int Location_x, int Location_y)
{
//AI斜着2个子
	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{

			if (g_Brick[i][j] == 3 && g_Brick[i + 1][j + 1] == 3)
			{
				if (g_Brick[i + 2][j + 2] == 0)
				{
					if (j + 2 < WidthAndHigh && i + 2 < WidthAndHigh)
					{
						g_Brick[i + 2][j + 2] = 3;
						return 1;
					}
				}
				else if (g_Brick[i - 1][j - 1] == 0)
				{
					if (i - 1 >= 0 && j - 1 >= 0)
					{
						g_Brick[i - 1][j - 1] = 3;
						return 1;
					}
				}
				else if (g_Brick[i + 3][j + 3] != 0 && g_Brick[i - 1][j - 1] != 0)
				{
					break;
				}
			}
		}

	//AI斜着2个子
	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3 && g_Brick[i - 1][j + 1] == 3)
			{
				if (g_Brick[i - 2][j + 2] == 0)
				{
					if (j + 2 < WidthAndHigh && i  - 2 >= 0)
					{
						g_Brick[i - 2][j + 2] = 3;
						return 1;
					}
				}
				else if (g_Brick[i + 1][j - 1] == 0)
				{
					if (i + 1 < WidthAndHigh && j - 1 >= 0)
					{
						g_Brick[i + 1][j - 1] = 3;
						return 1;
					}
				}
				else if (g_Brick[i - 2][j + 2] != 0 && g_Brick[i + 1][j - 1] != 0)
				{
					break;
				}
			}
		}

	//横着有2个子
	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3 && g_Brick[i][j + 1] == 3)
			{
				if (g_Brick[i][j + 2] == 0)
				{
					if (j + 2 < WidthAndHigh)
					{
						g_Brick[i][j + 2] = 3;
						return 1;
					}
				}
				else if (g_Brick[i][j - 1] == 0)
				{
					if (j - 1 >= 0)
					{
						g_Brick[i][j - 1] = 3;
						return 1;
					}
				}
				if (g_Brick[i][j + 2] != 0 && g_Brick[i][j - 1] != 0)
				{
					break;
				}
			}
		}

	//竖着有2个子
	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3 && g_Brick[i + 1][j] == 3)
			{
				if (g_Brick[i + 2][j] == 0)
				{
					if (i + 2 < WidthAndHigh)
					{
						g_Brick[i + 2][j] = 3;
						return 1;
					}
				}
				if (g_Brick[i - 1][j] == 0)
				{
					if (i - 1 >= 0)
					{
						g_Brick[i - 1][j] = 3;
						return 1;
					}
				}
				if (g_Brick[i + 2][j] != 0 && g_Brick[i - 1][j] != 0)
				{
					break;
				}
			}
		}

	//AI1子情况
	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3)
			{
				if (g_Brick[i + 1][j] == 0)
				{
					if (i + 1 < WidthAndHigh)
					{
						g_Brick[i + 1][j] = 3;
						return 1;
					}
				}
				if (g_Brick[i - 1][j] == 0)
				{
					if (i - 1 >= 0)
					{
						g_Brick[i - 1][j] = 3;
						return 1;
					}
				}
				if (g_Brick[i - 1][j - 1] == 0)
				{
					if (i - 1 >= 0 && j - 1 >= 0)
					{
						g_Brick[i - 1][j - 1] = 3;
						return 1;
					}
				}
				if (g_Brick[i + 1][j + 1] == 0)
				{
					if (i + 1 < WidthAndHigh && j + 1 < WidthAndHigh)
					{
						g_Brick[i + 1][j + 1] = 3;
						return 1;
					}
				}
				if (g_Brick[i][j + 1] == 0)
				{
					if (j + 1 < WidthAndHigh)
					{
						g_Brick[i][j + 1] = 3;
						return 1;
					}
				}
				if (g_Brick[i][j - 1] == 0)
				{
					if (j - 1 >= 0)
					{
						g_Brick[i][j - 1] = 3;
						return 1;
					}
				}
			}
		}


	//以上情况都不符合AI随机下

	while (1)
	{
		int robotRandom_x = rand() % (WidthAndHigh - 5);
		int robotRandom_y = rand() % (WidthAndHigh - 5);
		robotRandom_x+=3;
		robotRandom_y+=3;
		if (g_Brick[robotRandom_x][robotRandom_y] == 0)
		{
			g_Brick[robotRandom_x][robotRandom_y] = 3;
			break;
		}
	}
}


//玩家棋子位置
void CMoveTestDlg::SetQiZiLocation(int m_ButtonDownRL, CPoint m_MousePoint)
{
	if ((m_MousePoint.x - BKLocation_xy) % 60 > 30)
	{
		if ((m_MousePoint.y - BKLocation_xy) % 60 > 30)
		{
			int i = (int)m_MousePoint.x / 60 + 1;
			int j = (int)m_MousePoint.y / 60 + 1;
			if (g_Brick[i][j] == 0)
			{
				if (m_ButtonDownRL == 0)
				{
					g_Brick[i][j] = 1;
				}
				else
					g_Brick[i][j] = 2;
			}
		}
		if ((m_MousePoint.y - BKLocation_xy) % 60 < 30)
		{
			int i = (int)m_MousePoint.x / 60 + 1;
			int j = (int)m_MousePoint.y / 60;
			if (g_Brick[i][j] == 0)
			{
				if (m_ButtonDownRL == 0)
				{
					g_Brick[i][j] = 1;
				}
				else
					g_Brick[i][j] = 2;
			}
		}
	}

	if ((m_MousePoint.x - BKLocation_xy) % 60 < 30)
	{
		if ((m_MousePoint.y - BKLocation_xy) % 60 > 30)
		{
			int i = (int)m_MousePoint.x / 60;
			int j = (int)m_MousePoint.y / 60 + 1;
			if (g_Brick[i][j] == 0)
			{
				if (m_ButtonDownRL == 0)
				{
					g_Brick[i][j] = 1;
				}
				else
					g_Brick[i][j] = 2;
			}
		}
		if ((m_MousePoint.y - BKLocation_xy) % 60 < 30)
		{
			int i = (int)m_MousePoint.x / 60;
			int j = (int)m_MousePoint.y / 60;
			if (g_Brick[i][j] == 0)
			{
				if (m_ButtonDownRL == 0)
				{
					g_Brick[i][j] = 1;
				}
				else
					g_Brick[i][j] = 2;
			}
		}
	}

}


void CMoveTestDlg::OnBnClickedSetting()
{
	CSetting SetDlg;
	//WidthAndHigh = m_nSizeOfQiPan;
	//SizeOfQiZi = m_nSizeOfQiZi;
	if (IDOK == SetDlg.DoModal())
	{
	//	m_nSizeOfQiPan = SetDlg.m_SizeOfQiPan;
	//	m_nSizeOfQiZi = SetDlg.m_SizeOfQiZi;
	}
}


void CMoveTestDlg::OnBnClickedBkmusic()
{
	PlaySound(_T("C:\\Users\\hasee\\Documents\\Visual Studio 2015\\Projects\\MoveTest\\MoveTest\\res\\Night.wav"), NULL, SND_FILENAME | SND_ASYNC);
	// TODO: 在此添加控件通知处理程序代码
}


void CMoveTestDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	PlaySound(_T("C:\\Users\\hasee\\Documents\\Visual Studio 2015\\Projects\\MoveTest\\MoveTest\\res\\落地声.wav"), NULL, SND_FILENAME | SND_ASYNC);
	CDialogEx::OnTimer(nIDEvent);
}


void CMoveTestDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
