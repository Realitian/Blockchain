#pragma once
#include <boost/asio.hpp>
#include <vector>

#include "Identite.h"
#include "Transaction.h"
using boost::asio::ip::tcp;
class Serveur
{
public:
	Serveur();
	~Serveur();
	bool receive();
	bool addSocket();
	bool checkSocketAlive();
	bool deleteSocket();
	bool sendListNode();

	Identite getIdentite(std::string, std::string);
	std::vector<Transaction> getListTransaction(const Identite&);
private:
	boost::asio::io_service&		m_io_service; // (4)
	tcp::acceptor			m_acceptor; // (5)
	std::vector<Identite> identites;
	std::vector<Transaction> transactions;
};

