
/*
V 1.0
作者: 黄佳 <13735641@qq.com,13927488810>
日期: 2017年03月20日
描述: 用于数据收发的代理缓冲区
历史:
1、2017年03月20日 初步创建
使用说明:
*/

#ifndef _proxyBuffer_h_
#define _proxyBuffer_h_

#pragma once

#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

class proxyBuffer : public boost::enable_shared_from_this<proxyBuffer>
{
public:
	#define one_socket_buffer_length 1472

public:
	proxyBuffer();
	virtual ~proxyBuffer();

public:
	//获取缓冲区地址
	//Get buffer address
	char* getBuffer();

	//使用长度
	//Occupied buffer length
	int& getOccupyLength();

	//分配长度
	//Allocated buffer length
	int& getAllocLength();

	//剩余长度
	//Free buffer length
	int getFreeLength();

	//复位
	//Reset
	void reset();

	//压入数据
	//Push data
	int pushData(char* p_buffer, int length);
private:
	char		m_buffer[one_socket_buffer_length];	//缓冲区 //buffer
	int			m_occupyLength;						//使用长度 //occupied length
	int			m_allocLength;						//分配长度 //allocated length
};

typedef boost::shared_ptr<proxyBuffer>		proxyBufferPtr;

#endif
