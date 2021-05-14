
#include "stdafx.h"
#include "controller.h"
#include "network/clientBusiness.h"

//设备注册
//Device register
void device_register(const char* deviceID, protocol::business_ptr session)
{
	controller::getInstance()->onoffline(deviceID, session, true);
}

//设备离线
//Device offline
void device_offline(const char* deviceID, protocol::business_ptr session)
{
	controller::getInstance()->onoffline(deviceID, session, false);
}

controller* controller::getInstance()
{
	static controller* gInstance = NULL;
	if (NULL == gInstance)
		gInstance = new controller();
	return gInstance;
}

controller::controller()
{
	m_messageWnd = NULL;
}

controller::~controller()
{

}

deviceManager& controller::getDeviceManager()
{
	return m_deviceManager;
}

//启动工作
// Start work
bool controller::startWork(HWND msgWnd, unsigned port)
{
	m_messageWnd = msgWnd;
	return m_server.startWork(port);
}

//停止工作
//Stop work
void controller::stopWork()
{
	m_server.stopWork();
	m_deviceManager.reset();

	//等待所有业务结束
	//Waiting for all businesses ended
	Sleep(5000);
}

//设备上下线
//Device online and offline
void controller::onoffline(const char* deviceID, protocol::business_ptr session,bool online)
{
	if (session->getLinkerCode() == protocol::define::linkerCode::linkerCodeSignal)
	{//信令链路
     //Command link
		if (online)
		{
			device_ptr newDevice = m_deviceManager.createDevice(deviceID);
			if (NULL != newDevice)
			{
				newDevice->setDeviceID(deviceID);
				newDevice->setConnector(session);
				notifyBounder(newDevice,true);
			}
		}
		else
		{
			device_ptr device = m_deviceManager.getDevice(deviceID);
			if (NULL != device)
				notifyBounder(device, false);

			m_deviceManager.destroyDevice(deviceID);
		}
	}
	else
	{//媒体链路 
     //Media link
		device_ptr device = m_deviceManager.getDevice(deviceID);
		if (NULL == device)
			return;

		if (online)
			device->setConnector(session);
		else
			device->resetConnector(session);
	}

}

//通知界面
//Notification interface
void controller::notifyBounder(device_ptr device,bool online)
{
	if (NULL == m_messageWnd)
		return;

	LPARAM lparam = 0;
	if (online)
		lparam = 1;
	::PostMessage(m_messageWnd, WM_USER + 0x1001,(WPARAM)device.get(), lparam);
}