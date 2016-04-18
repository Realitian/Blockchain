#pragma once
#include <ctype.h>
#include <memory>
#include "SHA25.h"
#include "KeyPair.h"
using std::string;
class Message
{
public:
	Message() : nom_de_domaine(), information(), hashDomainName(),publicKey(), longueurMessage(), signature() {};

	Message(string, string, const KeyPair&);
	~Message();

	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar & nom_de_domaine & information & hashDomainName; // CLE RSA !!!
	}

	string getNomDomaine();
	string getinformation();
	string getHashDomainName();
	bool verifier() const;
	SecByteBlock sign(RSA::PrivateKey&);

private:
	std::string nom_de_domaine;
	std::string information;
	string hashDomainName;
	RSA::PublicKey publicKey;
	__int64 longueurMessage;
	SecByteBlock signature;
	// j'ai supprime les const pour la serialization


};

