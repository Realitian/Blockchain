#pragma once
#include <boost\asio.hpp>
#include <boost\shared_ptr.hpp>
#include <set>
#include "Session.h"
#include "Serveur.h"
#include "Identite.h"
#include "Transaction.h"
#include "BlockChain.h"
#include "Base_Donnee.h"

class Session;
class Serveur;


class Room
{
public:
	Room(Serveur& server); 

	void	join(boost::shared_ptr<Session> participant); 
	void	leave(boost::shared_ptr<Session> participant); 
	void	deliver(const Packet msg); 

	bool	addBlock(const Block&);
	bool    addTransaction(const Transaction&);
	bool    addIdentite(const Identite&);
private:
	std::set<boost::shared_ptr<Session>>	m_participants; 
	Serveur&								m_server;
	std::vector<Identite>					identites;
	std::vector<Transaction>				transactions;
	BlockChain								blockchain;
	Base_Donnee								bdd;
};

typedef std::shared_ptr<Room>	Room_ptr;
typedef std::weak_ptr<Room>		Room_wptr;
