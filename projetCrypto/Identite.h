#pragma once
#include <string>
#include <vector>
#include "KeyPair.h"
#include "cryptopp\rsa.h"
class Identite
{
public:
	/// Nom puis prenom
	Identite(std::string,std::string);
	Identite(std::string ,std::string ,const KeyPair &cle);
	Identite() {};

	std::ostream& operator<<(std::ostream& os);
	std::string getNom() const;
	std::string getPrenom() const;
	RSA::PublicKey& getPublicKey() const;
	RSA::PrivateKey& getPrivateKey() const;
	KeyPair getKeyPair() const;
	string toString() const;
private:
	std::string nom;
	std::string prenom;
	KeyPair cle;
};

