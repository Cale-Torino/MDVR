
/*
V 1.0
作者: 黄佳 <13735641@qq.com,13927488810>
日期: 2017年03月20日
描述: 客户端会话类
历史:
1、2017年03月20日 初步创建
使用说明:
*/

#ifndef _clientSession_h_
#define _clientSession_h_

#pragma once

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "messageBuffer.h"
#include "proxyBuffer.h"
#include "declare.h"
#include <boost/atomic.hpp>

namespace protocol
{
	class clientSession : public boost::enable_shared_from_this<clientSession>
	{
	public:
		clientSession(boost::asio::io_service& ioservice);
		virtual ~clientSession();

	public:
		//启动工作
		//Start work
		void start();

		//停止工作
		//Stop work
		void stop();

		boost::asio::ip::tcp::socket& socket();

		//写入和发送数据
		//Write and send data
		bool writeAndFlush(unsigned short msg, const char* payload_buffer, int payload_length);
		bool writeAndFlush2(unsigned short msg, messageBuffer::bufferList buffers[], int count);

	protected:
		//调度消息
		//Dispatch message
		virtual void dispatchMessage(protocol::define::msgHeader* header, char* payload) = 0;

		//掉线
		//Offline
		virtual void offline() = 0;

	private:
		//执行写动作
		//Handle write
		void actionWrite();

		//执行读动作
		//handle read
		void actionRead();

		//写入结果回调
		//call returned value of write
		void handle_write(proxyBufferPtr ptr, const boost::system::error_code& error, size_t bytes_transferred);

		//读取结果回调
		//call returned value of read
		void handle_read(proxyBufferPtr ptr, const boost::system::error_code& error, size_t bytes_transferred);

		//关闭
		//Close
		void	handle_close();

	private:
		//处理数据
		//Process data
		void processReceiveData();

	private:
		boost::asio::io_service&		m_io_service;
		boost::asio::ip::tcp::socket	m_socket;
		messageBuffer					m_recv_buffer;			//接收缓冲区 //Receive buffer area
		messageBuffer					m_send_buffer;			//发送缓冲区 //Send buffer area

		boost::atomic_bool				m_sending_lock;			//发送锁， 避免重复调用发送过程，导致数据错乱 //use this variant to avoid databuffer send error 
	};
};

#endif