#pragma once
#include <boost\asio.hpp>
#include <boost\weak_ptr.hpp>
#include <boost\enable_shared_from_this.hpp>

#include "Packet.h"
#include "Connection.h"
#include "Room.h"
class Room;
using boost::asio::ip::tcp;

class Session : public boost::enable_shared_from_this<Session>
{
public:
	~Session();

	static boost::shared_ptr<Session> create(boost::shared_ptr<Connection> Connection, boost::shared_ptr<Room> room) // (1)
	{
		boost::shared_ptr<Session> session(new Session(Connection, room));
		session->wait_for_data();
		return session;
	}

	void	deliver(Packet msg); // (2)

private:
	Session(boost::shared_ptr<Connection> Connection, boost::shared_ptr<Room> room);
	void	wait_for_data();

	void	handle_write(const boost::system::error_code& error);
	void	handle_read(const boost::system::error_code& error);

	boost::shared_ptr<Connection> m_Connection;
	boost::weak_ptr<Room> m_room; // (3)
	Packet			m_message;

	bool				is_leaving;
};

