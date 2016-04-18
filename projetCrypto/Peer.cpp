#include "Peer.h"



Peer::Peer(boost::asio::io_service& io_service, boost::asio::ip::tcp::endpoint& endpoint) 
{
	client = Client::create(io_service, endpoint);
	createNewIdentity();
}


Peer::~Peer()
{
}


void Peer::showBanner()
{
	clean_screen();
	print(MessageIHM::introMessage);
}




void Peer::createNewIdentity()
{
	string n, pn, key;
	print(MessageIHM::formulation_demande_identite);
	print(MessageIHM::formulation_demande_nom);
	std::cin >> n;
	print(MessageIHM::formulation_demande_prenom);
	std::cin >> n;
	RSA::PrivateKey pvkey;
	RSA::PublicKey pbkey;
	KeyPair cle;
	bool achieve;
DEMANDE_CLE:
	print(MessageIHM::formulation_demande_possession_cle);
	std::cin >> key;
	if (key.size() > 1)
		goto DEMANDE_CLE;
	switch (key.at(0))
	{
	case 'y':
		print(MessageIHM::formulation_demande_location_cle_publique);
		std::cin >> key;
		achieve = KeyPair::loadPublicKey(key, pbkey);
		if (!achieve)
			goto DEMANDE_CLE;
		print(MessageIHM::formulation_demande_location_cle_privee);
		std::cin >> key;
		achieve = KeyPair::loadPrivateKey(key, pvkey);
		if (!achieve)
			goto DEMANDE_CLE;
		break;
	case 'n':
		print(MessageIHM::information_generation_cle);
		sauvegarderCle(pvkey, pbkey);
		break;
	default:
		goto DEMANDE_CLE;
		break;
	}
	cle = KeyPair(pbkey, pvkey);
	identite = std::make_shared<Identite>(n, pn, cle);

}


void Peer::sauvegarderCle(const RSA::PrivateKey& pvkey,const RSA::PublicKey& pbkey)
{
SAUVEGARDE_CLE:
	print(MessageIHM::formulation_sauvegarde_cle);
	string ok;
	std::cin >> ok;
	if (ok.size() > 1)
		goto SAUVEGARDE_CLE;
	switch (ok.at(0))
	{
	case 'y':
		KeyPair::savePrivateKey("cleprivee.key", pvkey);
		KeyPair::savePublicKey("clepublique.key", pbkey);
		print(MessageIHM::infomation_cle_sauvegarde);
		break;
	case 'n':
		
		break;
	default:
		goto SAUVEGARDE_CLE;
		break;
	}
}

inline void Peer::print(const string& m)  {
	std::cout << m << std::endl;
}

void Peer::clean_screen()
{
	system("clear");
}