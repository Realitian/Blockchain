#pragma once
#include <vector>
#include <boost/serialization/vector.hpp>
#include <string>
#include "Block.h"
#include "Transaction.h"

class Packet
{
public:

	// Create simple object, not fully correct, but it is ok as they will be override if necessary
	Packet() :
		m_type(0),
		transaction(Identite("", ""), "", ""),
		block(0), numeroBloc()
	{

	}

	friend std::ostream& operator<<(std::ostream& os, const Packet& p);

	int			m_type; 
	Transaction transaction;
	Block		block;
	int			numeroBloc;
	template<class Archive>
	void save(Archive & ar, const unsigned int version) const
	{
		ar & m_type & transaction & block & numeroBloc;
	}

	template<class Archive>
	void load(Archive & ar, const unsigned int version)
	{
		ar & m_type & transaction & block & numeroBloc;
	}
	BOOST_SERIALIZATION_SPLIT_MEMBER()

		enum {
		NEW_MSG = 0, // Nouveau message
		PERSON_LEFT = 1, // Information : Person has left the room
		PERSON_CONNECTED = 2, // Information : New person connected to the room
		NEW_TRANSACTION = 3, // Send a transaction
		NEW_BLOCK = 4,  // Send a new block
		ASK_BLOCK_CHAIN, // Ask to get the BlockChain
		EXIST_TRANSACTION // Ask for a transaction
	};


};