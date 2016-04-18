#pragma once
#include <ctype.h>
#include <ctime>
#include <boost\date_time\posix_time\posix_time.hpp>
#include <boost/serialization/vector.hpp>
#include <boost\serialization\shared_ptr.hpp>
#include "Identite.h"
#include "Message.h"

class Transaction
{
public:
	Transaction(const Identite&, const string&, const string&);
	~Transaction();
	string toString() const;
	std::shared_ptr<Message> getMessage() const;
	boost::posix_time::ptime getTime() const;
	string getHashTransaction() const;

	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar & message & identiteSender &   hashTransaction; // shared_ptr !!!!!
	}

private:
	Identite identiteSender;
	std::shared_ptr<Message> message;
	string hashTransaction;
	boost::posix_time::ptime timestamp;
};

