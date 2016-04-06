#pragma once
#include <ctype.h>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "Identite.h"
#include "Message.h"
class Transaction
{
public:
	Transaction();
	~Transaction();
	std::string getHash() const; // a Modifier
private:
	Identite identiteSender;
	/*std::shared_ptr<*/Message/*>*/ message;
	uint8_t hashTransaction[32];
	boost::posix_time::ptime timestamp;
};

