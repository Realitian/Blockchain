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
		block(0) 
	{

	}

	friend std::ostream& operator<<(std::ostream& os,const Packet& p) 
	{
		os << std::endl;
		os << "***************************************************************************" << std::endl;
		os << "**_______________________________________________________________________**" << std::endl;
		os << "**|                                                                     |**" << std::endl;
		switch (p.m_type)
		{
		case 1:
			os << "**|                                                                     |**" << std::endl;
			os << "**|                                                                     |**" << std::endl;
			os << "**|" << "     " << "Packet type : " << std::setw(45) << p.m_type   << "     |**" << std::endl;
			os << "**|" << "     " << "Information : " << std::setw(45) << "a person has disconnected" << "     |**" << std::endl;
			os << "**|                                                                     |**" << std::endl;
			os << "**|                                                                     |**" << std::endl;
			os << "**|                                                                     |**" << std::endl;

			break;
		case 2:
			os << "**|                                                                     |**" << std::endl;
			os << "**|                                                                     |**" << std::endl;
			os << "**|" << "     " << "Packet type : " << std::setw(45) << p.m_type << "     |**" << std::endl;
			os << "**|" << "     " << "Information : " << std::setw(45) << "a person has just join the network" << "     |**" << std::endl;
			os << "**|                                                                     |**" << std::endl;
			os << "**|                                                                     |**" << std::endl;
			os << "**|                                                                     |**" << std::endl;

			break;
		case 3:
			os << "**|                                                                     |**" << std::endl;
			os << "**|      Hash Transaction : " << std::setw(38) << p.transaction.getHashTransaction().substr(0,38) << "...   |**" << std::endl;
			os << "**|      Message          : " << std::setw(40) << p.transaction.getMessage().getNomDomaine().substr(0, 40) << "    |**" << std::endl;
			os << "**|      Information      : " << std::setw(43) << p.transaction.getMessage().getinformation().substr(0, 40) << " |**" << std::endl;
			os << "**|      Module clePub    : " << std::setw(43) << boost::lexical_cast<std::string>(p.transaction.getMessage().getPublicKey().GetModulus()).substr(0, 43) << " |**" << std::endl;
			os << "**|      Exponent clePub  : " << std::setw(43) << boost::lexical_cast<std::string>(p.transaction.getMessage().getPublicKey().GetPublicExponent()).substr(0, 43) << " |**" << std::endl;
			os << "**|                                                                     |**" << std::endl;
			break;
		case 4:
			break;
		}
		os << "**|_____________________________________________________________________|**" << std::endl;
		os << "***************************************************************************" << std::endl;
		os << "***************************************************************************"<< std::endl;
		os << std::endl;
		return os;
	}

	int			m_type; 
	Transaction transaction;
	Block		block;

	template<class Archive>
	void save(Archive & ar, const unsigned int version) const
	{
		ar & m_type;
		ar & transaction;
		ar & block;
	}

	template<class Archive>
	void load(Archive & ar, const unsigned int version)
	{
		ar & m_type;
		ar & transaction;
		ar & block;
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