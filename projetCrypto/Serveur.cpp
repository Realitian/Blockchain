#include "Serveur.h"
#include "Session.h"

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

// Attente d'un nouveau client
void Serveur::wait_for_connection()
{
	boost::shared_ptr<Connection> new_connection(new Connection(m_io_service)); // (2)

																						// Attente d'une nouvelle connection
	m_acceptor.async_accept(new_connection->socket(), // (3)
		boost::bind(&Serveur::handle_accept, this,
			boost::asio::placeholders::error,
			new_connection)
	);
}


void Serveur::handle_accept(const boost::system::error_code& error, boost::shared_ptr<Connection> new_connection) // (4)
{
	if (!error)
	{
		std::cout << "Connection acceptée" << std::endl;
		boost::shared_ptr<Session> session = Session::create(new_connection, m_room); // (5)
		m_room->join(session); // (6)
		wait_for_connection(); // (7)
	}
	else {
		std::cerr << "Connection refusee" << std::endl;
	}
}
