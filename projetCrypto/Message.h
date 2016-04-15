#pragma once
#include <ctype.h>
#include <memory>
#include "Payload.h"
#include "SHA25.h"
using std::string;
class Message
{
	using ptr_Payload = std::shared_ptr<Payload>;
public:
	Message(string,string,const KeyPair&);
	~Message();

	string getNomDomaine();
	string getinformation();
	string getHashDomainName();
	bool verifier() const;
private:
	RSA::PublicKey publicKey;
	SecByteBlock sign(RSA::PrivateKey&);
	const string hashDomainName;
	const __int64 longueurMessage;
	const std::string nom_de_domaine;
	const std::string information;
	const SecByteBlock signature;

};

