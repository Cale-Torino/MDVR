
#include "stdafx.h"
#include "listener.h"


protocol::listener::listener(boost::asio::io_service& ioservice,unsigned short port):
	m_acceptor(ioservice,boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
	m_io_service(ioservice)
{
	actionAccept();
}

protocol::listener::~listener()
{
	m_acceptor.close();
}

//处理客户端接入
//Process client access
void protocol::listener::handle_accept(const boost::system::error_code& error, business_ptr& session)
{
	if (!error)
	{
		//启动客户端业务
		//Start client business

		session->start();
		
		actionAccept();
	}
}

//执行接收动作
//handle accept action
void protocol::listener::actionAccept()
{
	business_ptr new_session(new clientBusiness(m_io_service));
	m_acceptor.async_accept(new_session->socket(),
		boost::bind(&protocol::listener::handle_accept, this, boost::asio::placeholders::error,
			new_session));
}

