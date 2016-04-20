#pragma once
#include <vector>
#include <boost/serialization/vector.hpp>
#include <string>
#include "Block.h"
#include "Transaction.h"

class Packet
{
public:

	// Cree les objets, les initialise de leur manière la plus simple
	Packet() :
		//block(0), // Cree un bloc vide
		transaction(Identite("", ""), "", ""),
		m_type(0)
	{

	}
	void reset()
	{
	}

	int m_type; // (1) Type d'événement : NEW_MSG, etc.

				// Block block;
	Transaction transaction;

	template<class Archive>
	void save(Archive & ar, const unsigned int version) const
	{
		ar & m_type;
		ar & transaction;
		//ar & block;
	}

	template<class Archive>
	void load(Archive & ar, const unsigned int version)
	{
		ar & m_type;
		ar & transaction;
		//ar & block;
	}

	template<class Archive>
	void serialize(
		Archive & ar,
		const unsigned int file_version
	) {
		boost::serialization::split_member(ar, *this, file_version);
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