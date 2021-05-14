
/*
V 1.0
作者: 黄佳 <13735641@qq.com,13927488810>
日期: 2017年03月22日
描述: 控制者
历史:
1、2017年03月22日 初步创建
使用说明:
*/

#ifndef _controller_h_
#define _controller_h_

#pragma once

#include "deviceManager.h"
#include "network/server.h"

class controller
{
public:
	controller();
	virtual ~controller();

public:
	static controller* getInstance();

public:
	deviceManager& getDeviceManager();

public:
	//启动工作
	//Start work
	bool startWork(HWND msgWnd,unsigned port);

	//停止工作
	//Stop work
	void stopWork();

	//设备上下线
	//Device online and offline
	void onoffline(const char* deviceID, protocol::business_ptr session, bool online);

private:
	//通知界面
	//Notification interface
	void notifyBounder(device_ptr device, bool online);

private:
	deviceManager		m_deviceManager;
	protocol::server	m_server;
	HWND				m_messageWnd;
};

#endif