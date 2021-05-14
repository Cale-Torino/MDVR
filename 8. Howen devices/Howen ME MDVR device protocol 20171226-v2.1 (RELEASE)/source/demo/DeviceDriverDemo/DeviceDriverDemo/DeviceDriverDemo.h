
// DeviceDriverDemo.h : PROJECT_NAME 应用程序的主头文件
// DeviceDriverDemo.h : PROJECT_NAME application mather header file 
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号   // Main symbol


// CDeviceDriverDemoApp: 
// 有关此类的实现，请参阅 DeviceDriverDemo.cpp
// to carry out the below application, please refer to" DeviceDriverDemo.cpp"
//

class CDeviceDriverDemoApp : public CWinApp
{
public:
	CDeviceDriverDemoApp();

// 重写     // rewrite 
public:
	virtual BOOL InitInstance();

// 实现   // achieve 

	DECLARE_MESSAGE_MAP()
};

extern CDeviceDriverDemoApp theApp;