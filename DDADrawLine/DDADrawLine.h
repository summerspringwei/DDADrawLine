
// DDADrawLine.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDDADrawLineApp: 
// �йش����ʵ�֣������ DDADrawLine.cpp
//

class CDDADrawLineApp : public CWinApp
{
public:
	CDDADrawLineApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDDADrawLineApp theApp;