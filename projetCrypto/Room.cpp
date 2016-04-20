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
	e.m_type = Packet::PERSON_CONNECTED;
	deliver(e);
}

void Room::leave(boost::shared_ptr<Session> participant)
{
	Packet e;
	e.m_type = Packet::PERSON_LEFT;
	deliver(e);

	m_participants.erase(participant);
}

void Room::deliver(const Packet& msg)
{
	std::for_each(m_participants.begin(), m_participants.end(),
		boost::bind(&Session::deliver, _1, boost::ref(msg)));
}
