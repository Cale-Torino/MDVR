
#include "stdafx.h"
#include "deviceManager.h"

deviceManager::deviceManager()
{

}

deviceManager::~deviceManager()
{

}

//创建设备
//Create device
device_ptr deviceManager::createDevice(const char* deviceID)
{
	device_ptr ptr = getDevice(deviceID);
	if (NULL != ptr)
		return ptr;

	boost::unique_lock<boost::shared_mutex> lock(m_lock);
	device_ptr newDevice(new device());
	m_deviceList.insert(deviceList::value_type(deviceID,newDevice));
	return newDevice;
}

//销毁设备
//Destroy device
void	deviceManager::destroyDevice(const char* deviceID)
{
	device_ptr ptr = getDevice(deviceID);
	if (NULL == ptr)
		return ;

	ptr->resetVariant();

	boost::unique_lock<boost::shared_mutex> lock(m_lock);
	m_deviceList.erase(deviceID);
}

//查找设备
//Search device
device_ptr	deviceManager::getDevice(const char* deviceID)
{
	boost::shared_lock<boost::shared_mutex> lock(m_lock);

	deviceList_iter itFind = m_deviceList.find(deviceID);
	if (m_deviceList.end() == itFind)
		return device_ptr();

	return itFind->second;
}


device_ptr	deviceManager::getDevice(long long memoryAddress)
{
	boost::shared_lock<boost::shared_mutex> lock(m_lock);

	deviceList_iter it = m_deviceList.begin();
	deviceList_iter it_end = m_deviceList.end();
	for (; it != it_end; ++it)
	{
		device_ptr device = it->second;
		long long deviceAddress = (long long)device.get();
		if (deviceAddress == memoryAddress)
			return device;
	}

	return device_ptr();
}

//复位
//Restart device
void deviceManager::reset()
{
	boost::shared_lock<boost::shared_mutex> lock(m_lock);
	m_deviceList.clear();
}