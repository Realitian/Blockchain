#include "Transaction.h"


Transaction::Transaction(const Identite& ident,const string& _domaineName,const string& _information)
	 : identiteSender(ident)
{
	std::cerr << "LA";
	 message = boost::make_shared<Message>(_information,_domaineName,ident.getKeyPair());
     hashTransaction = SHA25::sha256(identiteSender.toString() + message->getHashDomainName() + message->getinformation());
	 timestamp = boost::posix_time::second_clock::local_time();

	//  const std::string str_time = to_simple_string(time); pour convertir en string
}



Transaction::~Transaction()
{
}


string Transaction::toString() const{
	string os;
	os += identiteSender.toString()+ message->getNomDomaine() + message->getinformation();
	return os;
}

boost::shared_ptr<Message> Transaction::getMessage() const{
	return message;
}
boost::posix_time::ptime Transaction::getTime() const{
	return timestamp;
}
string Transaction::getHashTransaction() const {
	return hashTransaction;
}