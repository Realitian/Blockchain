#pragma once
#include <string>
#include "KeyPair.h"
class Payload
{
public:
	Payload();
	~Payload();
	std::string getNomDeDomaine() const;

	void signInformation(const KeyPair&);
private:
	std::string nom_de_domaine; // A modifier, ce ne sera sans doute pas des string
	std::string information;
	std::string signature;
};

