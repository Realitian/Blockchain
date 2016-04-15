#pragma once
#include <ctype.h>
#include <ctime>
#include <boost\date_time\posix_time\posix_time.hpp>
#include "Identite.h"
#include "Message.h"
#include "SHA25.h"
class Transaction
{
public:
	Transaction(Identite) ;
	~Transaction();
	string getHash() const; // a Modifier
private:
	Identite identiteSender;
	std::shared_ptr<Message> message;
	string hashTransaction;
	boost::posix_time::ptime timestamp;
};

