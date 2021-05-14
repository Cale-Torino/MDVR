
/*
V 1.0
作者: 黄佳 <13735641@qq.com,13927488810>
日期: 2017年03月20日
描述: 消息数据缓冲区
历史:
1、2017年03月20日 初步创建
使用说明:
*/

#ifndef _messageBuffer_h_
#define _messageBuffer_h_

#pragma once
#include <boost/thread.hpp>

class messageBuffer
{
public:
	typedef struct bufferList
	{
		const char*		buffer;
		int				length;
	}bufferList;

public:
	messageBuffer();
	virtual ~messageBuffer();

public:
	//初始化
	//Initialization
	void initialize(int ui_buffer_length);
	void uninitialize();

public:
	//清空（分配的空间依然保留）
	//Clear(Allocated space will be reserved)
	void empty();

	//是否数据为空
	//whether data is null
	bool isEmpty();

	//缓冲区地址
	//buffer address
	char* getBuffer();

	//缓冲区未使用开始地址
	//free buffer start address
	char* getFreeBuffer();

	//已经使用长度
	//occupied buffer length
	int getOccupyLength();

	//剩余长度
	//free buffer length
	int getFreeLength();

	//减少数据
	//Reduce data
	void decreaseBuffer(int ui_length);
	
	//增加数据(已经操作数据)
	//Increase data(have operated data)
	void increaseBuffer(int ui_length);

	//增加数据
	//Increase data
	bool increaseBuffer(const char* buffer, int length);
	bool increaseBuffer(bufferList buffer[],int number);

private:
	boost::shared_mutex		m_lock;

	char*					m_buffer;		//缓冲区 //Buffer
	int						m_totalLength;	//总长度 //total length
	int						m_occupyLength;	//已经使用长度 //occupied length
	int						m_allocLength; // 分配的长度 //allocated length
};

#endif
