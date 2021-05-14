
/*
V 1.0
作者: 黄佳 <13735641@qq.com,13927488810>
日期: 2017年03月20日
描述: 服务器类
历史:
1、2017年03月20日 初步创建
使用说明:
*/

#ifndef _listener_h_
#define _listener_h_

#pragma once

#include <boost/asio.hpp>
#include "clientBusiness.h"

namespace protocol
{
	class listener
	{
	public:
		listener(boost::asio::io_service& ioservice,unsigned short port);
		virtual ~listener();

	private:
		//处理客户端接入
		//Process client access
		void handle_accept(const boost::system::error_code& error, business_ptr& session);

		//执行接收动作
		//handle accept action
		void actionAccept();

	private:
		boost::asio::ip::tcp::acceptor						m_acceptor;			//tcp接收器
		//tcp acceptor
		boost::asio::io_service&							m_io_service;
	};

};

#endif