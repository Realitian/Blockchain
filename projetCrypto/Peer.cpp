#include "Peer.h"



Peer::Peer(ptr_Identite ptrIdentite, boost::asio::io_service& io_service, boost::asio::ip::tcp::endpoint& endpoint) :
	identite(ptrIdentite)
{
	client = Client::create(io_service, endpoint);
}


Peer::~Peer()
{
}


void Peer::showBanner()
{
	Message::clear();
	print(Message::IntroMessage);
}



void Peer::createNewIdentity()
{
	string n, pn, key;
	print(Message::formulation_demande_identite);
	print(Message::formulation_demande_nom);
	std::cin >> n;
	print(Message::formulation_demande_prenom);
	std::cin >> n;
	RSA::PrivateKey pvkey;
	RSA::PublicKey pbkey;
DEMANDE_CLE:
	print(Message::formulation_demande_possession_cle);
	std::cin >> key;
	if (key.size() > 1)
		goto DEMANDE_CLE;
	switch (key.at(0))
	{
	case 'y':
		print(Message::formulation_demande_location_cle_publique);
		std::cin >> key;
		bool achieve = KeyPair::loadPublicKey(key, pbkey);
		if (!achieve)
			goto DEMANDE_CLE;
		print(Message::formulation_demande_location_cle_privee);
		std::cin >> key;
		achieve = KeyPair::loadPrivateKey(key, pvkey);
		if (!achieve)
			goto DEMANDE_CLE;
		break;
	case 'n':
		print(Message::information_generation_cle);
		sauvegarderCle(pvkey, pbkey);
		break;
	default:
		goto DEMANDE_CLE;
		break;
	}
	KeyPair cle(pbkey, pvkey);
	identite = std::make_shared<Identite>(n, pn, cle);
}


void Peer::sauvegarderCle(const RSA::PrivateKey& pvkey,const RSA::PublicKey& pbkey)
{
SAUVEGARDE_CLE:
	print(Message::formulation_sauvegarde_cle);
	string ok;
	if (ok.size() > 1)
		goto SAUVEGARDE_CLE;
	switch (ok.at(0))
	{
	case 'y':
		KeyPair::savePrivateKey("cleprivee.key", pvkey);
		KeyPair::savePublicKey("clepublique.key", pbkey);
		print(Message::infomation_cle_sauvegarde);
	default:
		goto SAUVEGARDE_CLE;
		break;
	}
}

inline void Peer::print(const string& m)  {
	std::cout << m << std::endl;
}