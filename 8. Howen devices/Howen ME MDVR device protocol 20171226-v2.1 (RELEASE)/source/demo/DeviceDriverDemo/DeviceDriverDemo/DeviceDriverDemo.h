
// DeviceDriverDemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
// DeviceDriverDemo.h : PROJECT_NAME application mather header file 
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������   // Main symbol


// CDeviceDriverDemoApp: 
// �йش����ʵ�֣������ DeviceDriverDemo.cpp
// to carry out the below application, please refer to" DeviceDriverDemo.cpp"
//

class CDeviceDriverDemoApp : public CWinApp
{
public:
	CDeviceDriverDemoApp();

// ��д     // rewrite 
public:
	virtual BOOL InitInstance();

// ʵ��   // achieve 

	DECLARE_MESSAGE_MAP()
};

extern CDeviceDriverDemoApp theApp;