#pragma once
#include <ctype.h>
#include <memory>
#include "SHA25.h"
#include "KeyPair.h"
using std::string;

class Message
{
public:
	Message() : nom_de_domaine(), information(), hashDomainName(), publicKey(), longueurMessage(), signature() {
		std::cerr << "Construction d'un nouveau message" << std::endl;
	};

	Message(string, string, const KeyPair&);
	~Message();


	template<class Archive>
	void save(Archive & ar, const unsigned int version) const
	{
		ar & nom_de_domaine & information & longueurMessage;
		string aa = boost::lexical_cast<std::string>(publicKey.GetPublicExponent());
		string bb = boost::lexical_cast<std::string>(publicKey.GetModulus());
		ar & aa & bb;
		std::string token = std::string(reinterpret_cast<const char*>(signature.data()), signature.size());
		//ar & token;

	}

	template<class Archive>
	void load(Archive & ar, const unsigned int version)
	{
		string d, e, f;
		ar & nom_de_domaine & information & longueurMessage;
		ar & d & e;
		publicKey.SetPublicExponent(CryptoPP::Integer(d.c_str()));
		publicKey.SetModulus(CryptoPP::Integer(e.c_str()));
		//ar & f;
		//publicKey = RSA::PublicKey();
		//signature = SecByteBlock(reinterpret_cast<const byte*>(f.data()), f.size());
		//std::cout << " DEF:"<< d << " "<< e << f;
	}


	template<class Archive>
	void serialize(
		Archive & ar,
		const unsigned int file_version
	) {
		boost::serialization::split_member(ar, *this, file_version);
	}

	string getNomDomaine();
	string getinformation();
	string getHashDomainName();
	bool verifier() const;
	SecByteBlock sign(RSA::PrivateKey&);

	RSA::PublicKey getPublicKey() const
	{
		return publicKey;
	}
private:
	std::string nom_de_domaine;
	std::string information;
	string hashDomainName;
	RSA::PublicKey publicKey;
	__int64 longueurMessage;
	SecByteBlock signature;
	// j'ai supprime les const pour la serialization


};

