#pragma once
#include <boost\asio.hpp>
#include <boost\shared_ptr.hpp>
#include <set>
#include "Session.h"
#include "Serveur.h"
#include "Identite.h"
#include "Transaction.h"
#include "BlockChain.h"
class Session;
class Serveur;


class Room
{
public:
	Room(Serveur& server); // (1)

	void	join(boost::shared_ptr<Session> participant); // (1)
	void	leave(boost::shared_ptr<Session> participant); // (2)
	void	deliver(const Packet& msg); // (3)

	bool	addBlock(const Block&);
	bool    addTransaction(const Transaction&);
	bool    addIdentite(const Identite&);
private:
	std::set<boost::shared_ptr<Session>>	m_participants; // (4)
	Serveur&				m_server;

	std::vector<Identite> identites;
	std::vector<Transaction> transactions;
	BlockChain b;
};

typedef std::shared_ptr<Room>	Room_ptr;
typedef std::weak_ptr<Room>		Room_wptr;
