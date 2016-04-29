#include "Transaction.h"


//!
//! \brief Default Constructor for a Transaction. 
//! \brief A Transaction correspond is created under the name of an Identite and contains some informations added into a Message. The message will be composed of a domain name and some further informations. 
//! \brief This informations will be added into a Database and verified by a BlockChain
//! \param : ident The identity behind the creation of a new Transaction
//! \param : _domaineName The domain name chosen 
//! \param : _information  Some further information that Peer will be able to look up into the DataBase
//! \return :
//!
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


//!
//! \brief Check if a Transaction is correct. The identity name and surname should be enough long.
//!
//! \return :bool True if the transaction is correct
//!
bool Transaction::isCorrect() const
{
	if (identiteSender.getNom().size() <= 1 && identiteSender.getPrenom().size() <= 1)
		return false;
	
	if ((message.getHashDomainName() != SHA25::sha256(message.getNomDomaine())) ||
		message.getinformation().size() <= 1 ||
		// message.getNomDomaine().size() <= 2  ||
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