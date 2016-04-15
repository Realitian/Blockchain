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
	const std::string nom_de_domaine;
	const std::string information;
	const string hashDomainName;
	RSA::PublicKey publicKey;
	const __int64 longueurMessage;
	const SecByteBlock signature;

	SecByteBlock sign(RSA::PrivateKey&);


};

