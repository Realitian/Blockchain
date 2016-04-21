#include "Transaction.h"


Transaction::Transaction(const Identite& ident, const string& _domaineName, const string& _information)
	: identiteSender(ident)
{
	message = Message(_domaineName, _information, ident.getKeyPair());
	hashTransaction = SHA25::sha256(identiteSender.toString() + message.getHashDomainName() + message.getinformation());
	timestamp = boost::posix_time::second_clock::local_time();

}



Transaction::~Transaction()
{
}


string Transaction::toString() const {
	string os;
	os += identiteSender.toString() + message.getNomDomaine() + message.getinformation();
	return os;
}

Message Transaction::getMessage() const {
	return message;
}
boost::posix_time::ptime Transaction::getTime() const {
	return timestamp;
}
string Transaction::getHashTransaction() const {
	return hashTransaction;
}

Identite Transaction::getIdentite() const
{
	return identiteSender;
}