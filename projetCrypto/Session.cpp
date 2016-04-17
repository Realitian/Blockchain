#include "Session.h"

Session::Session(boost::shared_ptr<Connection> Connection, boost::shared_ptr<Room> room)
	: m_Connection(Connection),
	m_room(room),
	m_message(0)
{
	is_leaving = false;
	std::cout << "New Session ! " << std::endl;
}

Session::~Session()
{
	std::cout << "Session détruite" << std::endl;
}

void Session::wait_for_data() // (1)
{
	std::cout << "en attente de donnée " << std::endl;
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
			switch (m_message.m_type)
			{
			case Packet::PERSON_CONNECTED:
				break;
			case Packet::PERSON_LEFT:
				break;
			case Packet::EXIST_TRANSACTION:
				break;
			case Packet::ASK_BLOCK_CHAIN:
				break;
			case Packet::NEW_BLOCK:
					break;
			case Packet::NEW_TRANSACTION:
				break;
			default:
				break;
			}
			std::cout << "message bien recu : " << m_message.m_type << " " << std::endl;

			// On demande à la room de transmettre le message à tout le monde
			room->deliver(m_message); // (3)
									  // On relance une écoute
			wait_for_data(); // (4)
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

void Session::deliver(const Packet& msg) // (6)
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

