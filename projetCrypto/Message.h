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
		std::cout << "Dans save Message : " << std::endl;
		ar & nom_de_domaine & information & longueurMessage;
		string aa = boost::lexical_cast<std::string>(publicKey.GetPublicExponent());
		string bb = boost::lexical_cast<std::string>(publicKey.GetModulus());
		std::cout << "Exponent : " << aa << std::endl << "Module : " << bb << std::endl;
		ar & aa & bb;
		std::string token = std::string(reinterpret_cast<const char*>(signature.data()), signature.size());
		std::cout << " " << token << std::endl;
		ar & token;
	}

	template<class Archive>
	void load(Archive & ar, const unsigned int version)
	{
		std::cout << "Dans Load Message : " << std::endl;

		string d, e, f;
		ar & nom_de_domaine & information & longueurMessage;
		ar & d & e;
		std::cout << "Exponent : " << d << std::endl << "Module : " << e << std::endl;

		publicKey.SetPublicExponent(CryptoPP::Integer(d.c_str()));
		publicKey.SetModulus(CryptoPP::Integer(e.c_str()));
		ar & f;
		signature = SecByteBlock(reinterpret_cast<const byte*>(f.data()), f.size());
	}

	BOOST_SERIALIZATION_SPLIT_MEMBER()


	string getNomDomaine() const;
	string getinformation() const;
	string getHashDomainName() const;
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

