#pragma once
#include <boost\asio.hpp>
#include <boost\shared_ptr.hpp>
#include <set>
#include "Session.h"
#include "Serveur.h"
#include "Identite.h"
#include "Transaction.h"
#include "BlockChain.h"
#include "DataBase.h"

class Session;
class Serveur;

//!
//! \class Room
//!
//! \brief Room for the Session in the Server side
//!
//! \author Louis Henri Franc
//!
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
	DataBase								bdd;
};

typedef std::shared_ptr<Room>	Room_ptr;
typedef std::weak_ptr<Room>		Room_wptr;
