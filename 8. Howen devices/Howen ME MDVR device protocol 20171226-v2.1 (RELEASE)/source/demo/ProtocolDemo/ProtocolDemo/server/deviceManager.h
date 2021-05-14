
/*
V 1.0
作者: 黄佳 <13735641@qq.com,13927488810>
日期: 2017年03月22日
描述: 设备管理类
历史:
1、2017年03月22日 初步创建
使用说明:
*/

#ifndef _deviceManager_h_
#define _deviceManager_h_

#pragma once

#include "device.h"

class deviceManager
{
public:
	typedef std::map<std::string, device_ptr>		deviceList;
	typedef deviceList::iterator					deviceList_iter;

public:
	deviceManager();
	virtual ~deviceManager();

public:
	//创建设备
	//Create device
	device_ptr createDevice(const char* deviceID);

	//销毁设备
	//Destroy device
	void	destroyDevice(const char* deviceID);

	//查找设备
	//Search device
	device_ptr	getDevice(const char* deviceID);
	device_ptr	getDevice(long long memoryAddress);

public:
	//复位
	//Restart device
	void reset();

private:
	boost::shared_mutex		m_lock;
	deviceList				m_deviceList;
};



#endif