
#include "stdafx.h"
#include "proxyBuffer.h"

proxyBuffer::proxyBuffer()
{
	reset();
}

proxyBuffer::~proxyBuffer()
{

}

//获取缓冲区地址
//Get buffer address
char* proxyBuffer::getBuffer()
{
	return m_buffer;
}

//使用长度
//Occupied buffer length
int& proxyBuffer::getOccupyLength()
{
	return m_occupyLength;
}

//分配长度
//Allocated buffer length
int& proxyBuffer::getAllocLength()
{
	return m_allocLength;
}

//剩余长度
//Free buffer length
int proxyBuffer::getFreeLength()
{
	return (m_allocLength - m_occupyLength);
}


//复位
//Reset
void proxyBuffer::reset()
{
	m_allocLength = one_socket_buffer_length;
	m_occupyLength = 0;
	::memset(m_buffer,0, m_allocLength);
}

//压入数据
//Push data
int proxyBuffer::pushData(char* p_buffer, int length)
{
	int freeLength = getFreeLength();
	if (length < freeLength)
		freeLength = length;

	m_occupyLength += freeLength;
	::memcpy(m_buffer, p_buffer, freeLength);

	return freeLength;
}