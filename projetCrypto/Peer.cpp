#include "Peer.h"



Peer::Peer(boost::asio::io_service& io_service, boost::asio::ip::tcp::endpoint& endpoint)
{

}


Peer::~Peer()
{
}


void Peer::receivePacket(Packet packet)
{
	std::cerr <<
		std::endl << "PACKET RECU  dans PEER" << std::endl;
	std::cerr << "Type packet : " << packet.m_type << std::endl <<
		"Hash Transaction " << packet.transaction.getHashTransaction() << std::endl <<
		"Information message " << packet.transaction.getMessage().getinformation() << std::endl <<
		"Nom de domaine " << packet.transaction.getMessage().getNomDomaine() << std::endl <<
		"Cle publique modulus : " << packet.transaction.getMessage().getPublicKey().GetModulus() << std::endl <<
		"Cle publique exponent : " << packet.transaction.getMessage().getPublicKey().GetPublicExponent() <<
		std::endl <<
		std::endl;

}

void Peer::addClient(std::shared_ptr<Client> nvuClient)
{
	client = nvuClient;
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
	std::cin >> pn;
	n = "franc"; pn = "denis";
	RSA::PrivateKey pvkey;
	RSA::PublicKey pbkey;
	KeyPair cle;
	bool achieve;
DEMANDE_CLE:
	print(MessageIHM::formulation_demande_possession_cle);
	std::cin >> key;
	key = "n";
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
		cle = KeyPair(pbkey, pvkey);
		break;
	case 'n':
		print(MessageIHM::information_generation_cle);
		sauvegarderCle(pvkey, pbkey);
		break;
	default:
		goto DEMANDE_CLE;
		break;
	}
	std::cout << "Cle publique apres generation:  " << cle.getClePublique().GetPublicExponent() << " " << cle.getClePublique().GetModulus() << std::endl;
	identite = std::make_shared<Identite>(n, pn, cle);
	showBanner();
	displayMenu();
}


void Peer::sauvegarderCle(const RSA::PrivateKey& pvkey, const RSA::PublicKey& pbkey)
{
	showBanner();
SAUVEGARDE_CLE:
	print(MessageIHM::formulation_sauvegarde_cle);
	string ok;
	std::cin >> ok;
	ok = "n";
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
		// ok
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
	//system("cls");
}


void Peer::displayMenu() {
DISPLAY_MENU:
	print(MessageIHM::affichage_menu_principal);
	string choix;
	std::cin >> choix;
	choix = "1";
	if (choix.size() != 1)
		goto DISPLAY_MENU;
	switch (choix.at(0))
	{
	case '1':
	{
		std::shared_ptr<Transaction> ptrT = createTransaction(); // TODO verifier comment eviter que le switch m'emmerde
		Packet p; p.m_type = Packet::NEW_TRANSACTION; p.transaction = *ptrT;
		std::cout << std::endl << "Avant envoi1, la transaction est de type : " <<
			"Hash Transaction " << p.transaction.getHashTransaction() << std::endl <<
			"Information message " << p.transaction.getMessage().getinformation() << std::endl <<
			"Nom de domaine " << p.transaction.getMessage().getNomDomaine() << std::endl <<
			"Cle publique modulus : " << p.transaction.getMessage().getPublicKey().GetModulus() << std::endl <<
			"Cle publique exponent : " << p.transaction.getMessage().getPublicKey().GetPublicExponent() <<
			std::endl << std::endl;
		client->write(boost::system::error_code(), p);

		break;
	}
	case '2':
	{
		// start mining
		break;
	}
	case '3':
		connexion(); // retourner a la connection
		break;
	default:
		goto DISPLAY_MENU;
		break;
	}
}

std::shared_ptr<Transaction> Peer::createTransaction()
{
	clean_screen();
	string choix;
	string domaineName, informationNameDomain;
CREATE_TRANSACTION:
	string msg = MessageIHM::formulation_demande_creation_transaction_sous_idenite + identite->getPrenom() + " " + identite->getNom() + MessageIHM::y_or_n;
	print(msg);
	std::cin >> choix;
	choix = "y";
	if (choix.size() != 1)
		goto CREATE_TRANSACTION;
	switch (choix.at(0))
	{
	case 'y':
	{
		print(MessageIHM::formulation_demande_nom_de_domaine);
		std::cin >> domaineName;
		print(MessageIHM::formulation_demande_information);
		std::cin >> informationNameDomain;
		domaineName = "facebook.com";
		informationNameDomain = "hello world";
		// TODO verifier si la transaction est correcte
		std::shared_ptr<Transaction> ptrT = std::make_shared<Transaction>(*identite, domaineName, informationNameDomain);
		std::cout << std::endl << "Avant envoi1, la transaction est de type : " <<
			"Hash Transaction " << ptrT->getHashTransaction() << std::endl <<
			"Information message " << ptrT->getMessage().getinformation() << std::endl <<
			"Nom de domaine " << ptrT->getMessage().getNomDomaine() << std::endl <<
			"Cle publique modulus : " << ptrT->getMessage().getPublicKey().GetModulus() << std::endl <<
			"Cle publique exponent : " << ptrT->getMessage().getPublicKey().GetPublicExponent() <<
			std::endl <<
			std::endl;
		return ptrT;
		break;
	}
	case 'n':
		displayMenu();
		return nullptr;
		break;
	}
	return nullptr;
}
