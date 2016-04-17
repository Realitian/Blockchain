#pragma once
#include <boost/asio.hpp>
#include <vector>
#include <functional>
#include <iostream>
#include "Room.h"
#include "Identite.h"
#include "Transaction.h"
using boost::asio::ip::tcp;
class Serveur
{
public:
	Serveur(boost::asio::io_service& io_service, const tcp::endpoint& endpoint); // (1)
	~Serveur();
	bool receive();
	bool addSocket();
	bool checkSocketAlive();
	bool deleteSocket();
	bool sendListNode();
	void	wait_for_connection(); 

	Identite getIdentite(std::string, std::string);
	std::vector<Transaction> getListTransaction(const Identite&);
private:
	void	handle_accept(const boost::system::error_code& error, boost::shared_ptr<Connection>); // (3)

	boost::asio::io_service&		m_io_service; // (4)
	tcp::acceptor			m_acceptor; // (5)
	boost::shared_ptr<Room>			m_room; // (6)

	std::vector<Identite> identites;
	std::vector<Transaction> transactions;
};

