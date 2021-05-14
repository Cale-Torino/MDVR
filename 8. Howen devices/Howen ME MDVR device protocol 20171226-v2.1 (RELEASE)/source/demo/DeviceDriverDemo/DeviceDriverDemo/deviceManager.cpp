
#include "stdafx.h"
#include "deviceManager.h"

deviceManager* deviceManager::_cur = NULL;

deviceManager::deviceManager()
{
	deviceManager::_cur = this;
}

deviceManager::~deviceManager()
{

}

//更新设备
//update device
void deviceManager::updateDevice(const char* deviceID,bool online)
{
	boost::unique_lock<boost::shared_mutex> lock(m_lock);

	deviceObjects_iter it = m_devices.find(deviceID);
	deviceObjects_iter itEnd = m_devices.end();

	if (online)
	{
		if (it == itEnd)
		{
			device _device;
			_device.deviceID = deviceID;
			_device.nListItem = -1;
			_device.status = 1;
			m_devices.insert(deviceObjects::value_type(deviceID, _device));
		}
		else
		{
			device& _device = it->second;
			_device.status = 1;
		}
	}
	else
	{
		if (it != itEnd)
		{
			device& _device = it->second;
			_device.status = 0;
		}
	}
}

//遍历
//traverse
void deviceManager::traverse(func _func)
{
	//移除界面中不显示的掉线设备
	//remove offline not display on bounder
	boost::unique_lock<boost::shared_mutex> lockWriter(m_lock);
	deviceObjects_iter it = m_devices.begin();
	deviceObjects_iter itEnd = m_devices.end();

	for (; it != itEnd; )
	{
		device& _device = it->second;

		if (_device.status == 0 && _device.nListItem == -1)
		{
			deviceObjects_iter temp = it;
			++it;
			m_devices.erase(temp);
		}
		else
			++it;
	}

	lockWriter.unlock();

	int processNumber = 0;

	//处理显示
	//process for display
	boost::shared_lock<boost::shared_mutex> lock(m_lock);
	it = m_devices.begin();
	itEnd = m_devices.end();

	for (; it != itEnd; ++it)
	{
		device& _device = it->second;

		if (_device.status == 0)
		{
			if (_device.nListItem != -1)
			{
				//从上线到掉线，并且界面已经显示，则需要移除
				//if device had display in the bounder and from online to offline,we need to remove it
				_func(_device.deviceID.c_str(), _device.status, _device.nListItem);
				_device.nListItem = -1;

				++processNumber;

				//一次处理100个，避免资源开销大，界面卡死
				//only process 100 times,avoid cpu too cost must
				if (processNumber >= 100)
					break;
			}
		}
		else if(_device.nListItem == -1)
		{
			//上线，并且界面没显示，则显示
			//if device online and not displaying in the bounder,we need to display it
			_func(_device.deviceID.c_str(), _device.status, _device.nListItem);
		}
	}
}