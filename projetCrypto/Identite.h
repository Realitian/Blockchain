#pragma once
#include <string>
#include <vector>
#include "KeyPair.h"
#include "cryptopp\rsa.h"
class Identite
{
public:
	Identite(std::string,std::string);
	Identite(std::string ,std::string ,const KeyPair &cle);
	Identite() {};

	std::ostream& operator<<(std::ostream& os);
	std::string getNom() const;
	std::string getPrenom() const;
	RSA::PublicKey getPublicKey() const;
private:
	RSA::PrivateKey getPrivateKey() const;
	std::string nom;
	std::string prenom;
	KeyPair cle;
};

