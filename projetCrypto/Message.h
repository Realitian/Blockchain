#pragma once
#include <ctype.h>
#include <memory>
#include "SHA25.h"
#include "KeyPair.h"
using std::string;
class Message
{
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

