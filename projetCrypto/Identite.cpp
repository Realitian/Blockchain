#include "Identite.h"

Identite::Identite(std::string _nom, std::string _prenom) :
	nom(_nom),
	prenom(_prenom)
{
	cle = KeyPair();
}

Identite::Identite(std::string _nom, std::string _prenom,const  KeyPair& cles) :
	nom(_nom),
	prenom(_prenom),
	cle(cles)
{

}


std::ostream& Identite::operator<<(std::ostream& os) {
	os << prenom << " " << nom << std::endl;
	return os;
}
std::string Identite::getNom() const
{
	return nom;
}
std::string Identite::getPrenom() const {
	return prenom;
}
RSA::PublicKey Identite::getPublicKey() const {
	return cle.getClePublique();
}

RSA::PrivateKey Identite::getPrivateKey() const {
	return cle.getPrivateKey();
}