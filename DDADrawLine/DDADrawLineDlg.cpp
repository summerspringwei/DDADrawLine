
// DDADrawLineDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DDADrawLine.h"
#include "DDADrawLineDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDDADrawLineDlg 对话框



CDDADrawLineDlg::CDDADrawLineDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDDADrawLineDlg::IDD, pParent)
	, p1x(0)
	, p1y(0)
	, p2x(0)
	, p2y(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDDADrawLineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);//控件和变量交换数据（竟然还要我自己添加！）
	DDX_Text(pDX, IDC_EDIT_P1X,p1x);
	DDX_Text(pDX, IDC_EDIT_P1Y, p1y);
	DDX_Text(pDX, IDC_EDIT_P2X, p2x);
	DDX_Text(pDX, IDC_EDIT_P2Y, p2y);
}

BEGIN_MESSAGE_MAP(CDDADrawLineDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_DDA, &CDDADrawLineDlg::OnBnClickedButtonDda)
	ON_BN_CLICKED(IDC_BUTTON_BRES, &CDDADrawLineDlg::OnBnClickedButtonBres)
END_MESSAGE_MAP()


// CDDADrawLineDlg 消息处理程序

BOOL CDDADrawLineDlg::OnInitDialog()
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

	// TODO:  在此添加额外的初始化代码
	numOfLine = 200;
	numOfCol = 100;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDDADrawLineDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDDADrawLineDlg::OnPaint()
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

	drawTable();
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDDADrawLineDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//绘制表格
void CDDADrawLineDlg::drawTable()
{
	CClientDC dc(this);
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));//设置画笔
	dc.SelectObject(&pen);//选择画笔

	const int seg = 5;//网格大小（pixel）

	for (int i = 0; i < numOfLine; i++)
	{
		for (int j = 0; j < numOfCol; j++)
		{
			myPoints[i][j].x = 50 + seg * i;//点在屏幕上坐标赋值
			myPoints[i][j].y = 60 + seg * j;
		}
	}

	//画竖线
	for (int i = 0; i < numOfLine; i++)
	{
		dc.MoveTo(myPoints[i][0].x, myPoints[i][0].y);
		dc.LineTo(myPoints[i][numOfCol-1].x, myPoints[i][numOfCol-1].y);
	}
	//画横线
	for (int i = 0; i < numOfCol; i++)
	{
		dc.MoveTo(myPoints[0][i].x, myPoints[0][i].y);
		dc.LineTo(myPoints[numOfLine-1][i].x, myPoints[numOfLine-1][i].y);
	}
	/*
	for (int i = 0; i < numOfLine; i++)
	{
		for (int j = 0; j < numOfCol; j++)
		{
			if (i < numOfLine - 1 && j < numOfCol - 1)
			{
				//画线（垂直网格）
				dc.MoveTo(myPoints[i][j].x, myPoints[i][j].y);
				dc.LineTo(myPoints[i + 1][j].x, myPoints[i][j].y);
				dc.MoveTo(myPoints[i][j].x, myPoints[i][j].y);
				dc.LineTo(myPoints[i][j].x, myPoints[i][j + 1].y);
			}
			if (i == numOfLine - 1 && j != numOfCol - 1)//绘制最后一行
			{
				dc.MoveTo(myPoints[i][j].x, myPoints[i][j].y);
				dc.LineTo(myPoints[i][j].x, myPoints[i][j + 1].y);
			}
			if (j == numOfCol - 1 && i != numOfLine - 1)//绘制最后一列
			{
				dc.MoveTo(myPoints[i][j].x, myPoints[i][j].y);
				dc.LineTo(myPoints[i + 1][j].x, myPoints[i][j].y);
			}
		}
	}
	*/
}


//DDA算法函数
void CDDADrawLineDlg::dda()
{
	
	//判断输入的数据是否超过最大值或者是否为负数
	if (p1x > numOfLine || p2x > numOfLine || p1y > numOfCol || p2y > numOfCol)
	{
		MessageBox(_T("输入数据过大！请重新输入"));
		return;
	}
	if (p1x <0 || p2x <0 || p1y <0 || p2y <0)
	{
		MessageBox(_T("输入数据不能为负数！请重新输入"));
		return;
	}
	else
	{
		CClientDC dc(this);
		CPen pen(PS_SOLID, 1, RGB(255, 0, 0));//设置画笔
		CBrush brush(RGB(0, 255, 0));
		dc.SelectObject(&brush);//选择画笔


		if (p1x == p2x)//垂直的情况单独处理
		{
			for (int i = min(p1y, p2y); i <= max(p1y, p2y); i++)
			{
				CRect rect(myPoints[p1x][i], myPoints[p1x+1][i+1]);//设置要填充的矩形区域
				dc.FillRect(&rect, &brush);//绘制填充矩形
			}
		}
		else
		{
			double m = (double)(p1y - p2y) / (double)(p1x - p2x);
			
			if (m >= -1 && m <= 1)//m<1时按照x轴方向绘制
			{
				if (p1x > p2x)//设置p1点位左边的点
				{
					int tempx = p1x;
					int tempy = p1y;
					p1x = p2x;
					p1y = p2y;
					p2x = tempx;
					p2y = tempy;
				}
				double y = p1y;
				for (int i = p1x; i <= p2x; i++)
				{
					CRect rect(myPoints[i][(int)(y + 0.5)], myPoints[i + 1][(int)(y + 0.5) + 1]);
					dc.FillRect(&rect, &brush);
					y = y + m;//DDA画线算法的增量
				}
			}
			else
			{
				if (p1y > p2y)//设置p1点位上边的点
				{
					int tempx = p1x;
					int tempy = p1y;
					p1x = p2x;
					p1y = p2y;
					p2x = tempx;
					p2y = tempy;
				}

				double x = p1x;
				for (int j = p1y; j <= p2y; j++)
				{
					CRect rect(myPoints[(int)(x + 0.5)][j], myPoints[(int)(x + 0.5)+1][j + 1]);
					dc.FillRect(&rect, &brush);
					x = x + 1 / m;//x轴方向
				}
			}
		}
	}
}

//bresenham算法函数
void CDDADrawLineDlg::bres()
{
	if (p1x > numOfLine || p2x > numOfLine || p1y > numOfCol || p2y > numOfCol)
	{
		MessageBox(_T("输入数据过大！请重新输入"));
		return;
	}
	if (p1x <0 || p2x <0 || p1y <0 || p2y <0)
	{
		MessageBox(_T("输入数据不能为负数！请重新输入"));
		return;
	}
	else
	{
		CClientDC dc(this);
		CPen pen(PS_SOLID, 1, RGB(255, 0, 0));//设置画笔
		CBrush brush(RGB(255, 0, 0));
		dc.SelectObject(&brush);//选择画笔

		if (p1x == p2x)//垂直的情况单独处理
		{
			for (int i = min(p1y, p2y); i <= max(p1y, p2y); i++)
			{
				CRect rect(myPoints[p1x][i], myPoints[p1x + 1][i + 1]);
				dc.FillRect(&rect, &brush);
			}
		}

		else
		{
			int dx = max(p1x, p2x) - min(p1x, p2x);
			int dy = max(p1y, p2y) - min(p1y, p2y);
			double m = (double)(p1y - p2y) / (double)(p1x - p2x);

			//直线斜率绝对值小于1，按照x轴方向绘制
			if (m >= -1 && m <= 1)
			{
				if (p1x > p2x)//设置p1点位左边的点
				{
					int tempx = p1x;
					int tempy = p1y;
					p1x = p2x;
					p1y = p2y;
					p2x = tempx;
					p2y = tempy;
				}
				//绘制起点
				CRect rect(myPoints[p1x][p1y], myPoints[p1x + 1][p1y + 1]);
				dc.FillRect(&rect, &brush);

				double p = 2 * dy - dx;//设置决策函数初始值p0
				int y = p1y;
				int k = 0;
				for (int i = p1x+1; i < p2x; i++)
				{
					if (p>0&&m>0)//决策函数大于零并且斜率大于0，则y=y+1
					{
						y = y + 1;
						k = 1;
					}
					else if (p > 0 && m < 0)//否则y=y-1
					{
						y = y - 1;
						k = 1;
					}
					else if (p <= 0)//否则y值不变
					{
						k = 0;
					}
					CRect rect(myPoints[i][y], myPoints[i + 1][y + 1]);
					dc.FillRect(&rect, &brush);
					p = p + 2 * dy - 2 * dx * k;//决策函数
				}
			}
			//直线斜率绝对值大于1，按照y轴方向绘制
			else
			{
				if (p1y > p2y)//设置p1点位上边的点
				{
					int tempx = p1x;
					int tempy = p1y;
					p1x = p2x;
					p1y = p2y;
					p2x = tempx;
					p2y = tempy;
				}
				//绘制起点
				CRect rect(myPoints[p1x][p1y], myPoints[p1x + 1][p1y + 1]);
				dc.FillRect(&rect, &brush);

				double p = 2 * dx - dy;
				int x = p1x;
				int k = 0;
				for (int j = p1y; j < p2y; j++)
				{
					if (p >= 0 && m >= 0)
					{
						x = x + 1;
						k = 1;
					}
					else if (p > 0 && m < 0)
					{
						x = x - 1;
						k = 1;
					}
					else
					{
						k = 0;
					}
					CRect rect(myPoints[x][j], myPoints[x + 1][j + 1]);
					dc.FillRect(&rect, &brush);
					p = p + 2 * dx - 2 * dy*k;//决策函数
				}
			}
		}


	}
}

//DDA按钮消息相应函数，点击使用DDA算法绘制直线
void CDDADrawLineDlg::OnBnClickedButtonDda()
{
	// TODO:  在此添加控件通知处理程序代码
	//将控件值传递给变量
	UpdateData(TRUE);
	//DDA画线函数
	dda();
}


void CDDADrawLineDlg::OnBnClickedButtonBres()
{
	// TODO:  在此添加控件通知处理程序代码
	//将控件值传递给变量
	UpdateData(TRUE);
	//DDA画线函数
	bres();
}
