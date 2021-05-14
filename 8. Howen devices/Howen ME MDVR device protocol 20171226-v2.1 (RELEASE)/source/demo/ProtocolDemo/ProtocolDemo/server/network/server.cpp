
#include "stdafx.h"
#include "server.h"
#include "listener.h"

protocol::server::server()
{
	m_thread = NULL;
	m_port = 0;
}

protocol::server::~server()
{

}

//启动工作
//Start work
bool protocol::server::startWork(unsigned port)
{
	if (NULL != m_thread)
		return true;

	m_port = port;
	m_thread = new boost::thread(boost::bind(&protocol::server::dispatching, this));
	
	return true;
}

//停止工作
//Stop work
void protocol::server::stopWork()
{
	if (NULL == m_thread)
		return;

	m_io_service.stop();
	m_thread->join();

	delete m_thread;
	m_thread = NULL;
}

//调度中
//In dispatch
void protocol::server::dispatching()
{
	listener l(m_io_service, m_port);
	m_io_service.run();
}