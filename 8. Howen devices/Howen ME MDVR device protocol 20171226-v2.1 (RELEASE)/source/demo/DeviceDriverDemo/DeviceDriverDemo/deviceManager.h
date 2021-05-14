
/*
版权所有 (c) 2017-2018  深圳市浩文安通科技股份有限公司
V 1.0
作者: 黄佳 <justin.huang@howentech.com>
日期: 2017年06月23日
描述: 设备管理类
历史:
1、2017年06月23日 初步创建
使用说明:
*/

/*
copy right (c) 2017-2018  Howen technologies Co.,Ltd 
V 1.0
developer: Justin <justin.huang@howentech.com>
Date:20170623
Description: device manager
History:
1, 20170623: initial establish 
instruction:
*/

#ifndef _device_Manager_h_
#define _device_Manager_h_

#pragma once

#include <string>
#include <map>
#include <boost/thread.hpp>

class deviceManager
{
private:
	typedef struct device
	{
		int				nListItem;
		int				status;			//在线状态	0：在线，1：掉线
		std::string		deviceID;
	}device;

	typedef std::map<std::string, device>		deviceObjects;
	typedef deviceObjects::iterator				deviceObjects_iter;

public:
	typedef boost::function<void (const char* deviceID,int status,int& nListItem)> func;

public:
	deviceManager();
	virtual ~deviceManager();

public:
	//更新设备
	//update device
	void	updateDevice(const char* deviceID, bool online);

	//遍历
	//traverse
	void	traverse(func _func);

private:
	deviceObjects			m_devices;
	boost::shared_mutex		m_lock;

public:
	static deviceManager* _cur;
};

#endif

