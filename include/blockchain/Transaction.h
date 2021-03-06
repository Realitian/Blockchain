#pragma once
#include <ctype.h>
#include <ctime>

#include <boost\date_time\posix_time\posix_time.hpp>
#include <boost/serialization/vector.hpp>
#include <boost\serialization\shared_ptr.hpp>
#include <boost\date_time\posix_time\time_serialize.hpp>
#include <boost/serialization/split_free.hpp>

#include "Identite.h"
#include "Message.h"
//!
//! \class Transaction
//! \brief A Transaction is created under the name of an Identite and contains some informations added into a Message. The message will be composed of a domain name and some further informations. 
//! \brief This informations will be added into a Database and verified by a BlockChain
//!
//! \author Louis Henri Franc
//!
class Transaction
{
public:
	Transaction(const Identite&, const string&, const string&);

	~Transaction();

	bool operator==(const Transaction& tr) 
	{
		if (tr.timestamp == timestamp &&
			tr.identiteSender.getNom() == identiteSender.getNom() &&
			tr.hashTransaction == hashTransaction &&
			tr.message.getHashDomainName() == message.getHashDomainName() && 
			tr.message.getinformation() == message.getinformation() && 
			tr.message.getNomDomaine() == message.getNomDomaine())
			return true;
		return false;
	}
	bool operator<(const Transaction& tr) const
	{
		if (hashTransaction < tr.getHashTransaction())
			return true;
		else return false;
	}

	boost::posix_time::ptime getTime() const;
	Identite				 getIdentite() const;
	Message					 getMessage() const;
	string					 getHashTransaction() const;
	string					 toString() const;
	bool					 isCorrect() const;

	template<class Archive>
	void save(Archive & ar, const unsigned int version) const
	{
		ar & identiteSender;
		ar & message;
		ar & hashTransaction;
		ar & timestamp;
	}

	template<class Archive>
	void load(Archive & ar, const unsigned int version)
	{
		ar & identiteSender;
		ar & message;
		ar & hashTransaction;
		ar & timestamp;
		message.sign(identiteSender.getKeyPair().getPrivateKey());
	}

	BOOST_SERIALIZATION_SPLIT_MEMBER();
private:
	Identite identiteSender;
	Message message;
	string hashTransaction;
	boost::posix_time::ptime timestamp;
};

