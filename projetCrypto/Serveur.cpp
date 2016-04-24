#include "Serveur.h"
#include "Session.h"

//!
//! \brief A server that handle relations between all the Client
//!
//! \param : io_service 
//! \param : endpoint 
//! \return :
//!
Serveur::Serveur(boost::asio::io_service& io_service, const tcp::endpoint& endpoint)
	:m_io_service(io_service),
	m_acceptor(io_service, endpoint),
	m_room(new Room(*this))
{
	std::cout << "Creation d'un serveur " << std::endl;
	wait_for_connection(); // (1)
}

Serveur::~Serveur()
{

}

//!
//! \brief A acceptation function that wait for new connection. Called handle_connect when a new Peer connected to the Server
//!
//! \return :void
//!
void Serveur::wait_for_connection()
{
	boost::shared_ptr<Connection> new_connection(new Connection(m_io_service)); 

																						// Waiting for a new Connection
	m_acceptor.async_accept(new_connection->socket(),
		boost::bind(&Serveur::handle_accept, this,
			boost::asio::placeholders::error,
			new_connection)
	);
}


//!
//! \brief Handle the new Connection created
//!
//! \param : error 
//! \param : new_connection 
//! \return :void
//!
void Serveur::handle_accept(const boost::system::error_code& error, boost::shared_ptr<Connection> new_connection) 
{
	if (!error)
	{
		boost::shared_ptr<Session> session = Session::create(new_connection, m_room); 
		m_room->join(session); 
		wait_for_connection(); 
	}
	else {
		std::cerr << "Connection refused" << std::endl;
	}
}
