#pragma once
#include <string>
#include "KeyPair.h"
class Identite
{
public:
	Identite(std::string,std::string);
	Identite(std::string ,std::string ,KeyPair);
	~Identite();

	std::ostream& operator<<(std::ostream& os);
	std::string getNom() const;
	std::string getPrenom() const;
	std::vector<unsigned char> getPublicKey() const;
private:
	std::vector<unsigned char> getPrivateKey();
	std::string nom;
	std::string prenom;
	KeyPair cle;
};

