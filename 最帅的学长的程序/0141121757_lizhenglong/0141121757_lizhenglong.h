
// 0141121757_lizhenglong.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy0141121757_lizhenglongApp:
// �йش����ʵ�֣������ 0141121757_lizhenglong.cpp
//

class CMy0141121757_lizhenglongApp : public CWinApp
{
public:
	CMy0141121757_lizhenglongApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy0141121757_lizhenglongApp theApp;