
// DDADrawLineDlg.h : ͷ�ļ�
//

#pragma once


// CDDADrawLineDlg �Ի���
class CDDADrawLineDlg : public CDialogEx
{
// ����
public:
	CDDADrawLineDlg(CWnd* pParent = NULL);	// ��׼���캯��

	int numOfLine;
	int numOfCol;
	POINT myPoints[200][200];


	void drawTable();//��������
	void dda();//DDA�㷨����ֱ��
	void bres();//bresenham�����㷨


// �Ի�������
	enum { IDD = IDD_DDADRAWLINE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
