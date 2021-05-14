
#include "stdafx.h"
#include "messageBuffer.h"

messageBuffer::messageBuffer()
{
	m_buffer = NULL;
	m_totalLength = NULL;
	m_occupyLength = 0;
	m_allocLength = 0;
}

messageBuffer::~messageBuffer()
{
	uninitialize();
}


//初始化
//Initialization
void	messageBuffer::initialize(int buffer_length)
{
	if(NULL != m_buffer && m_allocLength < buffer_length)
	{//之前分配缓冲区不足，则需要清理掉，并且重新申请
     //Clear buffer and request again if allocated buffer is not enough
		delete[] m_buffer;
	}

	if(NULL != m_buffer)//已经分配足够缓冲区 //Allocated buffer is enough
		return;

	m_buffer = new char[buffer_length];
	m_occupyLength = 0;
	m_totalLength = buffer_length;
	m_allocLength = buffer_length;
}

void	messageBuffer::uninitialize()
{
	if(NULL != m_buffer)
	{
		delete[] m_buffer;
		m_buffer = NULL;
	}

	m_totalLength = 0;
	m_occupyLength = 0;
	m_allocLength = 0;
}

//清空（分配的空间依然保留）
//Clear(Allocated space will be reserved)
void	messageBuffer::empty()
{
	m_occupyLength = 0;
}

//是否数据为空
//whether data is null
bool	messageBuffer::isEmpty()
{
	if(0 == m_occupyLength)
		return true;

	return false;
}

//缓冲区地址
//buffer address
char*	messageBuffer::getBuffer()
{
	return m_buffer;
}

//缓冲区未使用开始地址
//free buffer start address
char*	messageBuffer::getFreeBuffer()
{
	return m_buffer + m_occupyLength;
}

//已经使用长度
//occupied buffer length
int	messageBuffer::getOccupyLength()
{
	return m_occupyLength;
}

//剩余长度
//free buffer length
int	messageBuffer::getFreeLength()
{
	int freeLength = m_totalLength - m_occupyLength;
	return freeLength;
}

//减少数据
//Reduce data
void	messageBuffer::decreaseBuffer(int length)
{
	boost::unique_lock<boost::shared_mutex> lock(m_lock);

	int moveLength = m_occupyLength - length;

	::memmove(m_buffer,m_buffer + length, moveLength);

	m_occupyLength = moveLength;
}

//增加数据(已经操作数据)
//Increase data(have operated data)
void	messageBuffer::increaseBuffer(int length)
{
	boost::unique_lock<boost::shared_mutex> lock(m_lock);

	m_occupyLength += length;
}

//增加数据
//Increase data
bool	messageBuffer::increaseBuffer(const char* buffer, int length)
{
	bufferList list[1];
	list[0].buffer = buffer;
	list[0].length = length;
	
	return increaseBuffer(list,1);
}

//增加数据
//Increase data
bool	messageBuffer::increaseBuffer(bufferList buffer[], int number)
{
	int totalLength = 0;

	int i = 0;
	for (i = 0; i < number; ++i)
		totalLength += buffer[i].length;

	boost::unique_lock<boost::shared_mutex> lock(m_lock);

	if((totalLength + m_occupyLength) > m_totalLength)
		return false;

	for (i = 0; i < number; ++i)
	{
		if (NULL == buffer[i].buffer || 0 == buffer[i].length)
			break;

		::memcpy(m_buffer + m_occupyLength, buffer[i].buffer, buffer[i].length);
		m_occupyLength += buffer[i].length;
	}
	
	return true;
}