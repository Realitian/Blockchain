#pragma once
#include <string>
#include <vector>
#include "KeyPair.h"
#include "../../libs/cryptocpp/cryptopp/rsa.h"
using CryptoPP::RSA;
//!
//! \class Identite
//!
//! \brief Represent a Human
//!
//! \author Louis Henri Franc
//!
class Identite
{
public:
	Identite(std::string, std::string);
	Identite(std::string, std::string, const KeyPair &cle);

	~Identite() {};

	std::string		getNom() const;
	std::string		getPrenom() const;
	RSA::PublicKey  getPublicKey() const;
	RSA::PrivateKey getPrivateKey() const;
	KeyPair			getKeyPair() const;

	string			toString() const;
	std::ostream& operator<<(std::ostream& os);


	template<class Archive>
	void save(Archive & ar, const unsigned int version) const
	{
		ar  & nom;
		ar  & prenom;
		ar & cle;
	}

	template<class Archive>
	void load(Archive & ar, const unsigned int version)
	{
		ar & nom;
		ar & prenom;
		ar & cle;
	}

	template<class Archive>
	void serialize(
		Archive & ar,
		const unsigned int file_version
	) {
		boost::serialization::split_member(ar, *this, file_version);
	}


private:
	std::string nom;
	std::string prenom;
	KeyPair		cle;
};

