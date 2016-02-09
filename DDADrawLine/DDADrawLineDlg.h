
// DDADrawLineDlg.h : 头文件
//

#pragma once


// CDDADrawLineDlg 对话框
class CDDADrawLineDlg : public CDialogEx
{
// 构造
public:
	CDDADrawLineDlg(CWnd* pParent = NULL);	// 标准构造函数

	int numOfLine;
	int numOfCol;
	POINT myPoints[200][200];


	void drawTable();//绘制网格
	void dda();//DDA算法绘制直线
	void bres();//bresenham画线算法


// 对话框数据
	enum { IDD = IDD_DDADRAWLINE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int p1x;
	int p1y;
	int p2x;
	int p2y;
	afx_msg void OnBnClickedButtonDda();
	afx_msg void OnBnClickedButtonBres();
};
