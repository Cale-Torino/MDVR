

#include "stdafx.h"
#include "clientSession.h"

protocol::clientSession::clientSession(boost::asio::io_service& ioservice) :
	m_io_service(ioservice), m_socket(ioservice), m_sending_lock(false)
{
	m_recv_buffer.initialize(1024 * 800);
	m_send_buffer.initialize(1024 * 800);
}

protocol::clientSession::~clientSession()
{

}

boost::asio::ip::tcp::socket& protocol::clientSession::socket()
{
	return m_socket;
}

void protocol::clientSession::start()
{
	actionRead();
}

void protocol::clientSession::stop()
{
	if (!m_socket.is_open())
		return;

	m_socket.close();
}

//执行读动作
//handle read
void protocol::clientSession::actionRead()
{
	processReceiveData();

	proxyBufferPtr ptr(new proxyBuffer());

	m_socket.async_read_some(boost::asio::buffer(ptr->getBuffer(), ptr->getAllocLength()),
		boost::bind(&clientSession::handle_read, shared_from_this(), ptr,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

//读取结果回调
//Call returned value of read
void protocol::clientSession::handle_read(proxyBufferPtr ptr, const boost::system::error_code& error, size_t bytes_transferred)
{
	if (!error)
	{
		m_recv_buffer.increaseBuffer(ptr->getBuffer(),(int)bytes_transferred);
		actionRead();
	}
	else
	{
		m_socket.close();
		m_io_service.post(boost::bind(&protocol::clientSession::handle_close, shared_from_this()));
	}
}

//执行写动作
//handle write
void protocol::clientSession::actionWrite()
{
	if (!m_socket.is_open())
		return;

	bool expectedValue = false;
	if (!m_sending_lock.compare_exchange_strong(expectedValue, true))
		return;

	int length = m_send_buffer.getOccupyLength();
	char* buffer = m_send_buffer.getBuffer();
	if (0 == length)
	{
		m_sending_lock = false;
		return;
	}

	proxyBufferPtr ptr(new proxyBuffer());
	length = ptr->pushData(buffer, length);
	m_send_buffer.decreaseBuffer(length);

	boost::asio::async_write(m_socket,
		boost::asio::buffer(ptr->getBuffer(),ptr->getOccupyLength()),
		boost::bind(&clientSession::handle_write, shared_from_this(),ptr,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

//写入结果回调
//Call returned value of write
void protocol::clientSession::handle_write(proxyBufferPtr ptr, const boost::system::error_code& error, size_t bytes_transferred)
{
	m_sending_lock = false;

	if (!error)
	{
		actionWrite();
	}
	else
	{
		m_socket.close();
		m_io_service.post(boost::bind(&protocol::clientSession::handle_close, shared_from_this()));
	}

}

//关闭
//Close
void protocol::clientSession::handle_close()
{
	offline();
}

//处理数据
//process data
void protocol::clientSession::processReceiveData()
{
	for (;;)
	{
		char* buffer = m_recv_buffer.getBuffer();
		unsigned int buffer_length = m_recv_buffer.getOccupyLength();

		if (buffer_length < protocol::define::msgHeaderLength)
			break;

		protocol::define::msgHeader* header = (protocol::define::msgHeader*)buffer;
		unsigned int onePackLength = header->payloadLength + protocol::define::msgHeaderLength;
		if (buffer_length < onePackLength)
			break;

		char* payload_buffer = buffer + protocol::define::msgHeaderLength;
		this->dispatchMessage(header, payload_buffer);

		m_recv_buffer.decreaseBuffer(onePackLength);
	}
}

bool protocol::clientSession::writeAndFlush(unsigned short msg,const char* payload_buffer, int payload_length)
{
	messageBuffer::bufferList buffer;
	buffer.buffer = payload_buffer;
	buffer.length = payload_length;

	return writeAndFlush2(msg, &buffer, 1);
}

bool protocol::clientSession::writeAndFlush2(unsigned short msg, messageBuffer::bufferList buffers[],int count)
{
	protocol::define::msgHeader header = { 0 };
	header.flag = protocol::define::msgHeaderFlag;
	header.versionn = protocol::define::msgHeaderVersion;
	header.code = msg;

	messageBuffer::bufferList buffer[16];
	buffer[0].buffer = (char*)&header;
	buffer[0].length = protocol::define::msgHeaderLength;

	int total_length = 0;
	for (int i = 0; i < count; ++i)
	{
		buffer[1+i].buffer = buffers[i].buffer;
		buffer[1+i].length = buffers[i].length;
		total_length += buffers[i].length;
	}

	header.payloadLength = total_length;

	if (!m_send_buffer.increaseBuffer(buffer, count+1))
		return false;

	actionWrite();

	return true;
}