#pragma once
#include <ctype.h>
#include <ctime>
#include <boost\date_time\posix_time\posix_time.hpp>
#include "Identite.h"
#include "Message.h"

class Transaction
{
public:
	Transaction(const Identite&,const string&,const string&) ;
	~Transaction();
	string toString() const ;
	std::shared_ptr<Message> getMessage();
	boost::posix_time::ptime getTime();
	string getHashTransaction();
private:
	Identite identiteSender;
	std::shared_ptr<Message> message;
	string hashTransaction;
	boost::posix_time::ptime timestamp;
};

