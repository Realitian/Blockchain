#pragma once
#include <vector>
#include <boost/serialization/vector.hpp>
#include <string>


class Packet
{
public:
	Packet(int i) 
	{

	}
	void reset()
	{
		m_list_string.clear();
	}

	int m_type; // (1) Type d'événement : NEW_MSG, etc.

				// Generic datas
	std::vector<std::string>	m_list_string; // (4)
											   // Transaction t;
											   // Block b;
											   // int numeroBloc

	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar & m_type & m_list_string;
	}

	enum {
		NEW_MSG = 0, // Nouveau message
		PERSON_LEFT = 1, // Information : personne ayant quittée la room
		PERSON_CONNECTED = 2, // Information : nouvelle personne connectée à la room
		NEW_TRANSACTION = 3, // Envoi d'un nouvelle transaction
		NEW_BLOCK = 4,  // Envoi d'un nouveau bloc
		ASK_BLOCK_CHAIN, // Demander à récuperer la blockchain
		EXIST_TRANSACTION // Demander si la transaction existe
	};
};