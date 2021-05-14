
// ProtocolDemo.h : PROJECT_NAME 应用程序的主头文件
//ProtocolDemo.h : PROJECT_NAME Main head file of program

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
	//#error "Include "stdafx.h" before including this file to generate PCH file"
#endif

#include "resource.h"		// 主符号   //Main symbol


// CProtocolDemoApp: 
// 有关此类的实现，请参阅 ProtocolDemo.cpp
//Refer to ProtocolDemo.cpp to implement the class

class CProtocolDemoApp : public CWinApp
{
public:
	CProtocolDemoApp();

// 重写
//Overwrite
public:
	virtual BOOL InitInstance();

// 实现
//Implement

	DECLARE_MESSAGE_MAP()
};

extern CProtocolDemoApp theApp;