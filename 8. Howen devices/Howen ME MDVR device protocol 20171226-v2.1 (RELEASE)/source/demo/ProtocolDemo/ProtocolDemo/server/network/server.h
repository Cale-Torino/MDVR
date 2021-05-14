
/*
V 1.0
作者: 黄佳 <13735641@qq.com,13927488810>
日期: 2017年03月20日
描述: 服务器类
历史:
1、2017年03月20日 初步创建
使用说明:
*/

#ifndef _server_h_
#define _server_h_

#pragma once

#include <boost/asio.hpp>
#include <boost/thread.hpp>

namespace protocol
{
	class server 
	{
	public:
		server();
		virtual ~server();

	public:
		//启动工作
		//Start work
		bool startWork(unsigned port);
		
		//停止工作
		//Stop work
		void stopWork();

	private:
		//调度中
		//In dispatch
		void dispatching();

	private:
		boost::asio::io_service							m_io_service;

		unsigned short									m_port;

		boost::thread*									m_thread;
	};

};

#endif