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


bool Transaction::isCorrect() const
{
	if (identiteSender.getNom().size() <= 1 && identiteSender.getPrenom().size() <= 1)
		return false;
	
	if ((message.getHashDomainName() != SHA25::sha256(message.getNomDomaine())) ||
		message.getinformation().size() <= 1 ||
		message.getPublicKey().GetPublicExponent() == identiteSender.getPublicKey().GetPublicExponent() ||
		hashTransaction != SHA25::sha256(identiteSender.toString() + message.getHashDomainName() + message.getinformation())
		// TODO Something about the time
	)
		return false;
	 
	return true;
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