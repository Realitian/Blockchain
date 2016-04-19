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

class Transaction
{
public:
	Transaction(const Identite&, const string&, const string&);
	~Transaction();
	string toString() const;
	boost::shared_ptr<Message> getMessage() const;
	boost::posix_time::ptime getTime() const;
	string getHashTransaction() const;

	template<class Archive>
	void save(Archive & ar, const unsigned int version) const
	{
		// invoke serialization of the base class 
		ar & identiteSender;
		ar & message;
		ar & hashTransaction;
		ar & timestamp;
	}

	template<class Archive>
	void load(Archive & ar, const unsigned int version)
	{
		// invoke serialization of the base class 
		ar & identiteSender;
		ar & message;
		ar & hashTransaction;
		ar & timestamp;
	}

	template<class Archive>
	void serialize(
		Archive & ar,
		const unsigned int file_version
	) {
		boost::serialization::split_member(ar, *this, file_version);
	}


private:
	Identite identiteSender;
	boost::shared_ptr<Message> message;
	string hashTransaction;
	boost::posix_time::ptime timestamp;
};

