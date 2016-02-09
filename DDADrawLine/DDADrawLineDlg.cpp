
// DDADrawLineDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DDADrawLine.h"
#include "DDADrawLineDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CDDADrawLineDlg �Ի���



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
	CDialogEx::DoDataExchange(pDX);//�ؼ��ͱ����������ݣ���Ȼ��Ҫ���Լ���ӣ���
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


// CDDADrawLineDlg ��Ϣ�������

BOOL CDDADrawLineDlg::OnInitDialog()
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	numOfLine = 200;
	numOfCol = 100;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDDADrawLineDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
		
	}
	else
	{
		CDialogEx::OnPaint();
	}

	drawTable();
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CDDADrawLineDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//���Ʊ��
void CDDADrawLineDlg::drawTable()
{
	CClientDC dc(this);
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));//���û���
	dc.SelectObject(&pen);//ѡ�񻭱�

	const int seg = 5;//�����С��pixel��

	for (int i = 0; i < numOfLine; i++)
	{
		for (int j = 0; j < numOfCol; j++)
		{
			myPoints[i][j].x = 50 + seg * i;//������Ļ�����긳ֵ
			myPoints[i][j].y = 60 + seg * j;
		}
	}

	//������
	for (int i = 0; i < numOfLine; i++)
	{
		dc.MoveTo(myPoints[i][0].x, myPoints[i][0].y);
		dc.LineTo(myPoints[i][numOfCol-1].x, myPoints[i][numOfCol-1].y);
	}
	//������
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
				//���ߣ���ֱ����
				dc.MoveTo(myPoints[i][j].x, myPoints[i][j].y);
				dc.LineTo(myPoints[i + 1][j].x, myPoints[i][j].y);
				dc.MoveTo(myPoints[i][j].x, myPoints[i][j].y);
				dc.LineTo(myPoints[i][j].x, myPoints[i][j + 1].y);
			}
			if (i == numOfLine - 1 && j != numOfCol - 1)//�������һ��
			{
				dc.MoveTo(myPoints[i][j].x, myPoints[i][j].y);
				dc.LineTo(myPoints[i][j].x, myPoints[i][j + 1].y);
			}
			if (j == numOfCol - 1 && i != numOfLine - 1)//�������һ��
			{
				dc.MoveTo(myPoints[i][j].x, myPoints[i][j].y);
				dc.LineTo(myPoints[i + 1][j].x, myPoints[i][j].y);
			}
		}
	}
	*/
}


//DDA�㷨����
void CDDADrawLineDlg::dda()
{
	
	//�ж�����������Ƿ񳬹����ֵ�����Ƿ�Ϊ����
	if (p1x > numOfLine || p2x > numOfLine || p1y > numOfCol || p2y > numOfCol)
	{
		MessageBox(_T("�������ݹ�������������"));
		return;
	}
	if (p1x <0 || p2x <0 || p1y <0 || p2y <0)
	{
		MessageBox(_T("�������ݲ���Ϊ����������������"));
		return;
	}
	else
	{
		CClientDC dc(this);
		CPen pen(PS_SOLID, 1, RGB(255, 0, 0));//���û���
		CBrush brush(RGB(0, 255, 0));
		dc.SelectObject(&brush);//ѡ�񻭱�


		if (p1x == p2x)//��ֱ�������������
		{
			for (int i = min(p1y, p2y); i <= max(p1y, p2y); i++)
			{
				CRect rect(myPoints[p1x][i], myPoints[p1x+1][i+1]);//����Ҫ���ľ�������
				dc.FillRect(&rect, &brush);//����������
			}
		}
		else
		{
			double m = (double)(p1y - p2y) / (double)(p1x - p2x);
			
			if (m >= -1 && m <= 1)//m<1ʱ����x�᷽�����
			{
				if (p1x > p2x)//����p1��λ��ߵĵ�
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
					y = y + m;//DDA�����㷨������
				}
			}
			else
			{
				if (p1y > p2y)//����p1��λ�ϱߵĵ�
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
					x = x + 1 / m;//x�᷽��
				}
			}
		}
	}
}

//bresenham�㷨����
void CDDADrawLineDlg::bres()
{
	if (p1x > numOfLine || p2x > numOfLine || p1y > numOfCol || p2y > numOfCol)
	{
		MessageBox(_T("�������ݹ�������������"));
		return;
	}
	if (p1x <0 || p2x <0 || p1y <0 || p2y <0)
	{
		MessageBox(_T("�������ݲ���Ϊ����������������"));
		return;
	}
	else
	{
		CClientDC dc(this);
		CPen pen(PS_SOLID, 1, RGB(255, 0, 0));//���û���
		CBrush brush(RGB(255, 0, 0));
		dc.SelectObject(&brush);//ѡ�񻭱�

		if (p1x == p2x)//��ֱ�������������
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

			//ֱ��б�ʾ���ֵС��1������x�᷽�����
			if (m >= -1 && m <= 1)
			{
				if (p1x > p2x)//����p1��λ��ߵĵ�
				{
					int tempx = p1x;
					int tempy = p1y;
					p1x = p2x;
					p1y = p2y;
					p2x = tempx;
					p2y = tempy;
				}
				//�������
				CRect rect(myPoints[p1x][p1y], myPoints[p1x + 1][p1y + 1]);
				dc.FillRect(&rect, &brush);

				double p = 2 * dy - dx;//���þ��ߺ�����ʼֵp0
				int y = p1y;
				int k = 0;
				for (int i = p1x+1; i < p2x; i++)
				{
					if (p>0&&m>0)//���ߺ��������㲢��б�ʴ���0����y=y+1
					{
						y = y + 1;
						k = 1;
					}
					else if (p > 0 && m < 0)//����y=y-1
					{
						y = y - 1;
						k = 1;
					}
					else if (p <= 0)//����yֵ����
					{
						k = 0;
					}
					CRect rect(myPoints[i][y], myPoints[i + 1][y + 1]);
					dc.FillRect(&rect, &brush);
					p = p + 2 * dy - 2 * dx * k;//���ߺ���
				}
			}
			//ֱ��б�ʾ���ֵ����1������y�᷽�����
			else
			{
				if (p1y > p2y)//����p1��λ�ϱߵĵ�
				{
					int tempx = p1x;
					int tempy = p1y;
					p1x = p2x;
					p1y = p2y;
					p2x = tempx;
					p2y = tempy;
				}
				//�������
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
					p = p + 2 * dx - 2 * dy*k;//���ߺ���
				}
			}
		}


	}
}

//DDA��ť��Ϣ��Ӧ���������ʹ��DDA�㷨����ֱ��
void CDDADrawLineDlg::OnBnClickedButtonDda()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//���ؼ�ֵ���ݸ�����
	UpdateData(TRUE);
	//DDA���ߺ���
	dda();
}


void CDDADrawLineDlg::OnBnClickedButtonBres()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//���ؼ�ֵ���ݸ�����
	UpdateData(TRUE);
	//DDA���ߺ���
	bres();
}
