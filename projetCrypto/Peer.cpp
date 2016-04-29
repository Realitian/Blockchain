#include "Peer.h"



Peer::Peer(boost::asio::io_service& io_service, boost::asio::ip::tcp::endpoint& endpoint) :
	base_de_donnee(), blockchain()
{

}


Peer::~Peer()
{
}


//!
//! \brief Is called when the Peer received a new Packet. Distribute the packet to the correct function depending the type of the packet
//!
//! \param : packet The packet to distribute
//! \return :void
//!
void Peer::receivePacket(const Packet& packet)
{
	std::cerr << packet;
	switch (packet.m_type)
	{
		// New transaction received
	case 3:
		receiveTransaction(packet);
		break;

		// New block received
	case 4:
		receiveBlock(packet);
		break;

	default:
		// Wrong packet format. Error !! 
		break;
	}
}



//!
//! \brief Main method when receiving a Packet. Called by receivePacket. Make the relation between the DataBase and the BlockChain
//!
//! \param : packet The packet
//! \return :int
//!
int Peer::receiveBlock(const Packet& packet)
{
	if (blockchain.size() == 0)
	{
		blockchain.push_back(packet.block);
		return Peer::CORRECT_BLOCK_RECEIVED;
	}
	// Check for the validity of the block, not the transaction inside !
	if (!packet.block.isValid())
		return false;
	// TODO or perhaps no, I consider as false, all the block that contains at least one transaction I can't find in my data base,
	// perhaps it is not the best option..., but as the block is build in 10 minutes, I consider normal that the peer should have "heard"
	// about this transaction before the block is received

	try {
		vector<Message> tr_buf;
		for (const auto& tr : packet.block.get_Transactions_List())
		{
			int status = base_de_donnee.get_statusTransaction(tr);

			if (status == DataBase::NOT_FOUND_TRANSACTION)
			{
				// std::cout << "This block has transaction unknown" << endl;
				return Peer::WRONG_BLOCK_WITH_TRANSACTIONS_UNKNOWN;
			}
			if (status == DataBase::VALIDATED_TRANSACTION)
			{
				// std::cout << "This block has transaction already taken" << endl;
				return Peer::WRONG_PACKET_WITH_TRANSACTION_ALREADY_VALIDATED;
			}
			if (status == DataBase::OTHER_SAME_TRANSACTION_ALREADY_VALID)
			{
				return 0;
			}
			tr_buf.push_back(base_de_donnee.get(tr).second.second);
		}
		// I could have done O(nLogn) I know TODO
		for (int i(0); i < tr_buf.size(); i++)
		{
			for (int j(i + 1); j < tr_buf.size(); j++)
			{
				if (tr_buf.at(i).getHashDomainName() == tr_buf.at(j).getHashDomainName())
					return 0;
			}
		}
		if (packet.block.get_Header().get_NumeroBloc() > std::get<0>(blockchain.get_LeadingBlock()))
		{
			// If I was mining, just stop it !
			auto previousLeading = blockchain.get_LeadingBlock();
			int push_code = blockchain.push_back(packet.block);
			if (push_code == BlockChain::INSERT_NEW_BLOCK) {
				updateTransactionList(previousLeading,packet.block);
			}
			else if (push_code == BlockChain::PREVIOUS_BLOCK_UNKNOWN) {
				return Peer::CORRECT_BLOCK_RECEIVED;
			}
			else
				return Peer::WRONG_BLOCK_RECEIVED;
		}
		else
		{
			int push_code = blockchain.push_back(packet.block);
			if (push_code == BlockChain::INSERT_NEW_BLOCK || push_code == BlockChain::PREVIOUS_BLOCK_UNKNOWN) {
				return Peer::CORRECT_BLOCK_RECEIVED;
			}
			else
				return Peer::WRONG_PACKET_RECEIVE;
		}
	}
	catch (std::exception e)
	{
		return Peer::UNKNOWN_ERROR;
	};
	return Peer::CORRECT_BLOCK_RECEIVED;
}


//!
//! \brief Update the Database entries when a new correct Block is received. Is called if the new Block has a number higher than the current leading Block in the BlockChain
//!
//! \param : leading The previous leading Block
//! \param : block The Block received
//! \return :void
//!
void Peer::updateTransactionList(Cuple leading, const Block& block)
{
	using Cuple = std::tuple<int, string, Block>;

	Cuple newbloc = Cuple(block.get_Header().get_NumeroBloc(), block.get_BlockHash(), block);
	int num = std::get<0>(leading);
	while (num < std::get<0>(newbloc))
	{

		base_de_donnee.update(std::get<2>(newbloc), DataBase::VALIDATED_TRANSACTION);
		newbloc = blockchain.get_PreviousBlock(newbloc);
	}
	do
	{

		base_de_donnee.update(std::get<2>(leading), DataBase::NOT_VALIDATED_TRANSACTION);
		base_de_donnee.update(std::get<2>(newbloc), DataBase::VALIDATED_TRANSACTION);

		newbloc = blockchain.get_PreviousBlock(newbloc);
		leading = blockchain.get_PreviousBlock(leading);
	} while (leading != newbloc);
}

//!
//! \brief Update the database when a new Transaction is received. Is called by receivePacket
//!
//! \param : packet The packet received
//! \return :int A Code corresponding to the status of the adding
//!
int Peer::receiveTransaction(const Packet& packet)
{
	if (!packet.transaction.isCorrect())
		return Peer::WRONG_PACKET_RECEIVE;
	try {
		base_de_donnee.push_back(packet.transaction);
	}
	catch (...)
	{
		return Peer::UNKNOWN_ERROR;
	};
	return Peer::CORRECT_TRANSACTION_ADDED;
}

void Peer::addClient(std::shared_ptr<Client> nvuClient)
{
	client = nvuClient;
}

//!
//! \brief Print a banner in the IHM
//!
//! \return :void
//!
void Peer::showBanner()
{
	clean_screen();
	print(MessageIHM::introMessage);
	if (!(identite == nullptr))
		print("You are connected as : " + identite->getPrenom() + " " + identite->getNom());
}




//!
//! \brief IHM Function. Menu for the Connection
//!
//! \return :void
//!
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
	// std::cout << "Cle publique apres generation:  " << cle.getClePublique().GetPublicExponent() << " " << cle.getClePublique().GetModulus() << std::endl;
	identite = std::make_shared<Identite>(n, pn, cle);
	showBanner();
	displayMenu();
}


//!
//! \brief IHM Function. Menu for saving a pair of Key
//!
//! \param : pvkey A Public Key
//! \param : pbkey A Private Key
//! \return :void
//!
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


//!
//! \brief IHM Function
//!
//! \param : m 
//! \return :void
//!
inline void Peer::print(const string& m) {
	std::cout << m << std::endl;
}

void Peer::clean_screen()
{
	//system("cls");
}

void Peer::startMining()
{

}


//!
//! \brief IHM Function. Display the main Menu of the IHM
//!
//! \return :void
//!
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
		std::shared_ptr<Transaction> ptrT = createTransaction(); 
		if (ptrT == nullptr) {
			print(MessageIHM::error_while_creating_transaction);
			break;
		}
		Packet p; p.m_type = Packet::NEW_TRANSACTION; p.transaction = *ptrT;
		std::cerr << p;
		client->write(boost::system::error_code(), p);

		break;
	}
	case '2':
	{
		// start mining
		break;
	}
	case '3':
		connexion(); // return to the first menu
		break;
	default:
		goto DISPLAY_MENU;
		break;
	}
}

//!
//! \brief IHM Function. Menu for creating a new Transaction
//!
//! \return :std::shared_ptr<Transaction>  A pointer to the created new Transaction
//!
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

		std::shared_ptr<Transaction> ptrT = std::make_shared<Transaction>(*identite, domaineName, informationNameDomain);
		if (!ptrT->isCorrect())
			return false;
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
