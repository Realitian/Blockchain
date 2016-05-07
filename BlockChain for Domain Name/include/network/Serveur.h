#pragma once
#include <vector>
#include <functional>
#include <iostream>

#include <boost/asio.hpp>

#include "Room.h"

class Room;
using boost::asio::ip::tcp;
class Serveur
{
public:
	Serveur(boost::asio::io_service& io_service, const tcp::endpoint& endpoint);
	~Serveur();

	void	wait_for_connection();
private:
	void	handle_accept(const boost::system::error_code& error, boost::shared_ptr<Connection>);

	boost::asio::io_service&		m_io_service;
	tcp::acceptor					m_acceptor;
	boost::shared_ptr<Room>			m_room;

};

