#include "Packet.h"



std::ostream& operator<<(std::ostream& os, const Packet& p)
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
		os << "**|" << "     " << "Packet type : " << std::setw(45) << p.m_type << "     |**" << std::endl;
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
		os << "**|      Hash Transaction : " << std::setw(38) << p.transaction.getHashTransaction().substr(0, 38) << "...   |**" << std::endl;
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
	os << "***************************************************************************" << std::endl;
	os << std::endl;
	return os;
}

/*
enum {
NEW_MSG = 0, // Nouveau message
PERSON_LEFT = 1, // Information : Person has left the room
PERSON_CONNECTED = 2, // Information : New person connected to the room
NEW_TRANSACTION = 3, // Send a transaction
NEW_BLOCK = 4,  // Send a new block
ASK_BLOCK_CHAIN, // Ask to get the BlockChain
EXIST_TRANSACTION // Ask for a transaction
};*/