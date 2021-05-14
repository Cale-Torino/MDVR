#include "stdafx.h"
#include "DirectFileSending.h"
#include <DeviceDriverSDK/DeviceDriver_API.h>

#pragma warning(disable:4996)

DirectFileSending*	DirectFileSending::_cur = NULL;

DirectFileSending::DirectFileSending()
{
	DirectFileSending::_cur = this;

	m_running = false;
	m_offset = 0;
}

DirectFileSending::~DirectFileSending()
{

}

//是否为当前回话
//is current session
bool DirectFileSending::isCurrentSession(const char* session)
{
	if (m_sessionID.compare(session) == 0)
		return true;

	return false;
}

//设置参数
//set information
void DirectFileSending::setParameter(const char* deviceID, const char* sessionID, const char* fileName)
{
	m_deviceID = deviceID;
	m_sessionID = sessionID;
	m_fileName = fileName;
}

//设置文件偏移位置
//set file offset
void DirectFileSending::setOffset(int offset)
{
	m_offset = offset;
}

//是否工作中
//working status
bool DirectFileSending::isWorking()
{
	if (NULL != m_thread)
		return true;

	return false;
}

//启动工作
//start work
void DirectFileSending::startWork()
{
	//另一线程执行中，不允许操作
	//waiting anther's thread finished.
	if (NULL != m_thread)
		return;
	
	m_running = true;
	m_thread.reset(new boost::thread(boost::bind(&DirectFileSending::sendingBussiness, this)));
}

//停止工作
//stop work
void DirectFileSending::stopWork()
{
	if (NULL == m_thread)
		return;

	m_running = false;
	Sleep(1000);
}

//发送业务
//sending business
void DirectFileSending::sendingBussiness()
{
	FILE* f = fopen(m_fileName.c_str(), "rb");

	//跳转到指定位置，以便断点续传
	//goto the specified position of the file, to continue transfer file from last break point
	fseek(f, m_offset, SEEK_SET);

	static const int oneLength = 1452 * 10;

	char buffer[oneLength] = { 0 };
	int readBytes = 0;

	howenDriver::standards::s_send_media_request req;
	req.data.frameType = howenDriver::enums::e_frame_type_file_data;
	req.data.timestamp = 0;

	bool canReadNext = true;
	int processNumber = 0;

	for (;;)
	{
		if (!m_running)
			break;


		if (canReadNext)
		{
			readBytes = (int)::fread(buffer, 1, oneLength, f);
			if (readBytes <= 0)
				break;

			req.data.frameBuffer = buffer;
			req.data.frameLength = readBytes;
			req.deviceID = m_deviceID.c_str();
			req.sessionID = m_sessionID.c_str();
		}

		if (howenDriver::api::HDeviceDriver_SendFileData2Device(&req) == howenDriver::enums::e_error_code_succeed)
		{
			canReadNext = true;
			++processNumber;
			if (processNumber >= 200)
				Sleep(10);
		}
		else
		{
			processNumber = 0;
			canReadNext = false;
			Sleep(300);
		}


	}

	fclose(f);

	//发送空数据帧，以便设备进行链路关闭
	//send empty media frame,the device can judge and close the link 
	req.data.frameBuffer = NULL;
	req.data.frameLength = 0;
	if (howenDriver::api::HDeviceDriver_SendFileData2Device(&req) == howenDriver::enums::e_error_code_succeed)
	{
		AfxMessageBox(_T("file send finished!"));
	}

	m_thread.reset();
}