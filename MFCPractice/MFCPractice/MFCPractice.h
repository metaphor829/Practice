
// MFCPractice.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once
//extern "C" __declspec(dllexport)void ShowDialog();

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"// ������



 //CMFCPracticeApp: 
// �йش����ʵ�֣������ MFCPractice.cpp
//


// ���ڷ�װ��������
class CMFCPracticeApp : public CWinApp 
{
public:
	CMFCPracticeApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFCPracticeApp theApp;

