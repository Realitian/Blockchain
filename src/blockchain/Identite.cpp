#include "../../include/blockchain/Identite.h"

//!
//! \brief Default constructor. Create a pair of Key
//!
//! \param : _nom A name
//! \param : _prenom A surname
//! \return :
//!
Identite::Identite(std::string _nom, std::string _prenom) :
	nom(_nom),
	prenom(_prenom)
{
	cle = KeyPair();
}

//!
//! \brief Construct an Identite with an already creating pair of Key
//!
//! \param : _nom A name
//! \param : _prenom A surname
//! \param : cles A KeyPair
//! \return :
//!
Identite::Identite(std::string _nom, std::string _prenom, const  KeyPair& cles) :
	nom(_nom),
	prenom(_prenom),
	cle(cles)
{

}



//!
//! \brief 
//!
//! \param : os 
//! \return :std::ostream&
//!
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

KeyPair Identite::getKeyPair() const {
	return cle;

}


RSA::PrivateKey Identite::getPrivateKey() const {
	return cle.getPrivateKey();
}

string Identite::toString() const
{
	return getNom() + getPrenom();
}
