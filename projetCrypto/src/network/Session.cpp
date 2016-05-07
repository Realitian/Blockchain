#include "Session.h"

Session::Session(boost::shared_ptr<Connection> Connection, boost::shared_ptr<Room> room)
	: m_Connection(Connection),
	m_room(room),
	m_message()
{
	is_leaving = false;
	std::cout << "New Session ! " << std::endl;
}

Session::~Session()
{
	std::cout << "Deleted session" << std::endl;
}

void Session::wait_for_data() 
{
	std::cout << "Waiting for data " << std::endl;
	// On lance l'écoute d'événements
	m_Connection->async_read(m_message,
		boost::bind(&Session::handle_read, shared_from_this(),
			boost::asio::placeholders::error)
	);
}


void Session::handle_read(const boost::system::error_code &error) // (2)
{
	boost::shared_ptr<Room> room = m_room.lock();
	if (room)
	{
		if (!error)
		{
			room->deliver(m_message);
			std::cout << "---- Reception ----- " << m_message.m_type << " " << std::endl;
			std::cout << m_message << std::endl;
			std::cout << "-------------------- " << std::endl;
			wait_for_data(); 
		}

		else
		{
			if (!is_leaving)
			{
				is_leaving = true;
				room->leave(shared_from_this()); // (5)
			}
		}
	}
}

void Session::deliver(const Packet &msg) // (6)
{

	m_Connection->async_write(msg,
		boost::bind(&Session::handle_write, shared_from_this(),
			boost::asio::placeholders::error)
	);
	std::cout << "message envoye :" << msg.m_type << "  " << std::endl;

}

void Session::handle_write(const boost::system::error_code &error) // (7)
{
	std::cerr << "Message bien envoye !" << std::endl;
	boost::shared_ptr<Room> room = m_room.lock();
	if (room && error && (!is_leaving))
	{
		is_leaving = true;
		room->leave(shared_from_this());
	}
}

