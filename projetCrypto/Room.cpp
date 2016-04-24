#include "Room.h"

//!
//! \brief Implementing a Room for connection in the Server Side
//!
//! \param : server 
//! \return :
//!
Room::Room(Serveur& server)
	:m_server(server),
	blockchain(), bdd()
{
	std::cout << "New room" << std::endl;
}

//!
//! \brief Add a new participant
//!
//! \param : participant A shared_ptr to the new Session
//! \return :void
//!
void Room::join(boost::shared_ptr<Session> participant)
{
	m_participants.insert(participant);
	Packet e;
	e.m_type = Packet::PERSON_CONNECTED;
	deliver(e);
}

//!
//! \brief Deleted a Session
//!
//! \param : participant The session to delete
//! \return :void
//!
void Room::leave(boost::shared_ptr<Session> participant)
{
	Packet e;
	e.m_type = Packet::PERSON_LEFT;
	deliver(e);

	m_participants.erase(participant);
}



//!
//! \brief Deliver a message to all the Session
//!
//! \param : msg The packet to deliver
//! \return :void
//!
void Room::deliver(const Packet msg)
{
	switch (msg.m_type)
	{
	case Packet::PERSON_CONNECTED:
		break;
	case Packet::PERSON_LEFT:
		break;
	case Packet::EXIST_TRANSACTION:
		std::cerr << "This is not implemented : ask for the existence of a transaction";
		break;
	case Packet::ASK_BLOCK_CHAIN:
		{
			int num = msg.numeroBloc;
		}
		break;
	case Packet::NEW_BLOCK:
		{
			Block b = msg.block;
			if (!b.isValid())
			{

			}
		}
		break;
	case Packet::NEW_TRANSACTION:
		break;
	default:
		break;
	}
	std::for_each(m_participants.begin(), m_participants.end(),
		boost::bind(&Session::deliver, _1, boost::ref(msg)));
}
