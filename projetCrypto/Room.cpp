#include "Room.h"

Room::Room(Serveur& server)
	:m_server(server),
	b()
{
	std::cout << "New room" << std::endl;
}

void Room::join(boost::shared_ptr<Session> participant)
{
	m_participants.insert(participant);
	Packet e;
	// On informe les sessions de la room // (1)
	e.m_type = Packet::PERSON_CONNECTED;
	deliver(e);
}

void Room::leave(boost::shared_ptr<Session> participant)
{
	// On informe les sessions de la room // (2)
	Packet e;
	e.m_type = Packet::PERSON_LEFT;
	deliver(e);

	m_participants.erase(participant);// puis on le d�truit
}

void Room::deliver(const Packet& msg)
{
	std::cout << "Nouveau message :" << msg.m_type << " " << std::endl;
	std::for_each(m_participants.begin(), m_participants.end(),
		boost::bind(&Session::deliver, _1, boost::ref(msg)));
}
