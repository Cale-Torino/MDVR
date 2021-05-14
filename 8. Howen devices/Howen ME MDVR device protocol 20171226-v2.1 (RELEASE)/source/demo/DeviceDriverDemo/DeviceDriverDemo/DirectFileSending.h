
/*
版权所有 (c) 2017-2018  深圳市浩文安通科技股份有限公司
V 1.0
作者: 黄佳 <13735641@qq.com,13927488810>
日期: 2017年05月20日
描述: 文件发送（直接传输到设备模式）
历史:
1、2017年05月20日 初步创建
使用说明:
*/

/*
copy right (c) 2017-2018  Howen technologies Co.,Ltd 
V 1.0
developer: Justin <info@howentech.com>
Date:20170520
Description: direct send file to device
History:
1, 20170520: initial establish 
instruction:
*/


#ifndef  _Direct_File_Sending_h__
#define  _Direct_File_Sending_h__

#pragma once

#include <string>
#include <boost/thread.hpp>

class DirectFileSending
{
private:
	typedef boost::shared_ptr<boost::thread> thread_ptr;

public:
	DirectFileSending();
	virtual ~DirectFileSending();

public:
	//设置参数
	//set information
	void setParameter(const char* deviceID, const char* sessionID, const char* fileName);

	//设置文件偏移位置
	//set file offset
	void setOffset(int offset);

	//启动工作
	//start work
	void startWork();

	//停止工作
	//stop work
	void stopWork();

public:
	//是否工作中
	//working status
	bool isWorking();

	//是否为当前回话
	//is current session
	bool isCurrentSession(const char* session);

private:
	//发送业务
	//sending business
	void sendingBussiness();

private:
	//发送线程
	//sending thread
	thread_ptr			m_thread;
	bool				m_running;

	std::string			m_deviceID;
	std::string			m_sessionID;
	std::string			m_fileName;
	int					m_offset;

public:
	static DirectFileSending*	_cur;
};

#endif 
