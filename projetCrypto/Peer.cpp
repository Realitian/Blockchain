#include "Peer.h"



Peer::Peer(boost::asio::io_service& io_service, boost::asio::ip::tcp::endpoint& endpoint)
{
	client = Client::create(io_service, endpoint);
	connexion();
}


Peer::~Peer()
{
}


void Peer::showBanner()
{
	clean_screen();
	print(MessageIHM::introMessage);
	if (!(identite == nullptr))
		print("Vous etes connecte en tant que " + identite->getNom() + " " + identite->getPrenom());
}




void Peer::connexion()
{
	showBanner();
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
	if (key.size() != 1)
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
	showBanner();
}


void Peer::sauvegarderCle(const RSA::PrivateKey& pvkey, const RSA::PublicKey& pbkey)
{
	showBanner();
SAUVEGARDE_CLE:
	print(MessageIHM::formulation_sauvegarde_cle);
	string ok;
	std::cin >> ok;
	if (ok.size() != 1)
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

inline void Peer::print(const string& m) {
	std::cout << m << std::endl;
}

void Peer::clean_screen()
{
	system("cls");
}


void Peer::displayMenu() {
DISPLAY_MENU:
	print(MessageIHM::affichage_menu_principal);
	int choix;
	std::cin >> choix;
	switch (choix)
	{
	case '1':
		Transaction t = createTransaction(); // TODO verifier comment eviter que le switch m'emmerde
		break;
	case '2':
			// start mining
		break;
	default:
		goto DISPLAY_MENU;
		break;
	}
}
Transaction Peer::createTransaction()
{
	string choix;
	Transaction t;
CREATE_TRANSACTION:
	print(MessageIHM::formulation_demande_creation_transaction_sous_idenite + identite->getPrenom() = " " + identite->getNom()+MessageIHM::y_or_n);
	std::cin >> choix;
	if (choix.size() != 1)
		goto CREATE_TRANSACTION;
	switch (choix.at(0))
	{
	case 'y':

		break;
	case 'n':

		break;
	}
	return t;
}

/*
Identite identiteSender;
std::shared_ptr<Message> message;
string hashTransaction;
boost::posix_time::ptime timestamp;
*/