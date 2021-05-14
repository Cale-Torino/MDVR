
/*
V 1.0
作者: 黄佳 <13735641@qq.com,13927488810>
日期: 2017年03月20日
描述: 客户端业务类
历史:
1、2017年03月20日 初步创建
使用说明:
*/

#ifndef _clientBusiness_h_
#define _clientBusiness_h_

#pragma once

#include "clientSession.h"
#include <string>

namespace protocol
{
	class clientBusiness : public clientSession
	{
	public:
		clientBusiness(boost::asio::io_service& ioservice);
		virtual ~clientBusiness();

	public:
		//获取连接类型
		//Get link type
		define::linkerCode getLinkerCode();

		//会话标识
		//Session ID
		const char* getSessionID();

	protected:
		//调度消息
		//Dispatch message

		virtual void dispatchMessage(protocol::define::msgHeader* header, char* payload);

		//掉线
		//Offline
		virtual void offline();
	private:
		//媒体数据
		//Media data
		void mediaStream(char* playload_buffer, int payload_length);

		//设备信令注册
		//Device register on command server
		void signalRegister(char* playload_buffer, int payload_length);

		//设备媒体链路注册
		//Device register on media serevr
		void mediaRegister(char* playload_buffer, int payload_length);

		//状态数据
		//Status data
		void statusData(char* playload_buffer, int payload_length);

		//报警数据
		void alarmData(char* playload_buffer, int payload_length);

		//文件信息
		void fileDetail(char* playload_buffer, int payload_length);

		//抓拍
		void snapShot(char* playload_buffer, int payload_length);

	private:
		protocol::define::linkerCode		m_eLinkerCode;	//连接器类型 //Connector type
		std::string							m_deviceID;		//设备编号 //Device ID
		std::string							m_sessionID;	//会话编号  //Session ID
	};

	typedef boost::shared_ptr<clientBusiness> business_ptr;
};

#endif