
// ProtocolDemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//ProtocolDemo.h : PROJECT_NAME Main head file of program

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
	//#error "Include "stdafx.h" before including this file to generate PCH file"
#endif

#include "resource.h"		// ������   //Main symbol


// CProtocolDemoApp: 
// �йش����ʵ�֣������ ProtocolDemo.cpp
//Refer to ProtocolDemo.cpp to implement the class

class CProtocolDemoApp : public CWinApp
{
public:
	CProtocolDemoApp();

// ��д
//Overwrite
public:
	virtual BOOL InitInstance();

// ʵ��
//Implement

	DECLARE_MESSAGE_MAP()
};

extern CProtocolDemoApp theApp;