#include <unordered_map>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cassert>
#include <ctime>
#include <boost/asio.hpp>
#include <fstream>
#include "include/blockchain/Transaction.h"
#include "include/database/DataBase.h"
#include "include/blockchain/BlockChain.h"
// #include "Serveur.h"

#define SIMULATION_COEFF 0.9

using std::cout; using std::endl;



// ^(?([^\r\n])\s)*[^\s+?/]+[^\n]*$


std::string random_string(size_t length)
{
	auto randchar = []() -> char
	{
		const char charset[] =
			"abcdefghijklmnopqrstuvwxyz";
		const size_t max_index = (sizeof(charset) - 1);
		return charset[rand() % max_index];
	};
	std::string str(length, 0);
	std::generate_n(str.begin(), length, randchar);
	vector<string > extension = { ".com",".fr",".us",".bit",".cn" };
	str += extension[rand() % extension.size()];
	return str;
}


void updateTransactionList(std::tuple<int, string, Block> leading, DataBase& base_de_donnee, BlockChain& blockchain, const Block& block)
{
	using Cuple = std::tuple<int, string, Block>;

	Cuple newbloc = Cuple(block.get_Header().get_NumeroBloc(), block.get_BlockHash(), block);
	int num = std::get<0>(leading);
	std::cout << "Update the BlockChain head from number" << std::get<0>(leading) << "to number" << block.get_Header().get_NumeroBloc() << " block" << std::endl;
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

int receiveBlock(DataBase& base_de_donnee, const Block& block, BlockChain& blockchain)
{
	// Check for the validity of the block, not the transaction inside !
	if (blockchain.size() == 0)
	{
		blockchain.push_back(block);
		return true;
	}
	if (!block.isValid())
		return false;
	// TODO or perhaps no, I consider as false, all the block that contains at least one transaction I can't find in my data base,
	// perhaps it is not the best option..., but as the block is build in 10 minutes, I consider normal that the peer should have "heard"
	// about this transaction before the block is received

	try {
		vector<Message> tr_buf;
		for (const auto& tr : block.get_Transactions_List())
		{
			int status = base_de_donnee.get_statusTransaction(tr);
			if (status == DataBase::NOT_FOUND_TRANSACTION)
			{
				std::cout << "This block has transaction unknown" << endl;
				return 0;
			}
			if (status == DataBase::VALIDATED_TRANSACTION)
			{
				std::cout << "This block has transaction already in the main chain" << endl;
				return 0;
			}
			if (status == DataBase::OTHER_SAME_TRANSACTION_ALREADY_VALID)
			{

				return 0;
			}
			tr_buf.push_back(base_de_donnee.get(tr).second.second);
		}
		// std::cerr << block.get_Header().get_NumeroBloc() << endl;

		for (int i(0); i < tr_buf.size(); i++)
		{
			for (int j(i + 1); j < tr_buf.size(); j++)
			{
				if (tr_buf.at(i).getHashDomainName() == tr_buf.at(j).getHashDomainName())
					return 0;
			}
		}
		if (block.get_Header().get_NumeroBloc() > std::get<0>(blockchain.get_LeadingBlock()))
		{
			// If I was mining, just stop it !
			auto previousLeading = blockchain.get_LeadingBlock();

			int push_code = blockchain.push_back(block);
			if (push_code == BlockChain::INSERT_NEW_BLOCK) {
				std::cout << "This block updates the Blockchain :" << block.get_Header().get_NumeroBloc() << endl;
				updateTransactionList(previousLeading, base_de_donnee, blockchain, block);
			}
			else if (push_code == BlockChain::PREVIOUS_BLOCK_UNKNOWN) {
				return 1;
			}
			else
				return 0;
		}
		else
		{
			int push_code = blockchain.push_back(block);
			if (push_code == BlockChain::INSERT_NEW_BLOCK) {
				return 1;
			}
			else if (push_code == BlockChain::PREVIOUS_BLOCK_UNKNOWN) {
				return 1;
			}
			else
				return 0;
		}
	}
	catch (std::exception e)
	{
		return -1;
	};
	return 1;
}




void test_integration_BlockCHain()
{
	// std::freopen("test.out", "w", stdout);
	std::ofstream istr("test.ut");
	// Creation of IDs
	Identite id("Franc", "Jerome");
	Identite id1("CAVA", "ETtoi");
	Identite id2("Hola", "QueTal");
	Identite id3("MuyBien", "YTu");
	Identite id4("Ou", "COmmenet");
	Identite id5("Reviser", "L'espagnol");
	vector<Identite>  ids = { id,id1,id2,id3,id4,id5 };

	// Creation of transaction then random transaction
	Transaction t(id, "facebook.com", "meilleur site internet");
	Transaction t1(id1, "google.com", "la vie privée on y tient");
	Transaction t2(id2, "microsoft.com", "ils ont un bon editeur de texte");
	Transaction t22(id2, "microsoft.fr", "ils sont cools en plus");
	Transaction t3(id3, "apple.com", "f**k le FBI");
	Transaction t4(id4, "codingame", "simply de best");
	Transaction t6(id, "chill.com", "ca existe?");
	Transaction t7(id1, "spion.com", "on s'amuse");
	Transaction t8(id2, "amazon.com", "riche comme cresus");
	Transaction t82(id2, "insa.fr", "hum hum hum");
	Transaction t9(id3, "holahola.com", "hablo espagnol");
	Transaction t10(id4, "darty.com", "LOL");

	vector<Transaction> all_Transaction;
	vector<Transaction> transactions1{ t1,t,t2,t22,t3,t4 };
	vector<Transaction> transactions2{ t6,t8,t82,t7,t9,t10 };
	all_Transaction.insert(all_Transaction.end(), transactions1.begin(), transactions1.end());
	all_Transaction.insert(all_Transaction.end(), transactions2.begin(), transactions2.end());




	istr << "Generating random transaction : " << endl;
	for (int i(0); i < 1000; i++)
	{
		string nom_de_domaine = random_string(3);
		string information = random_string(35);
		all_Transaction.emplace_back(ids.at(rand() % ids.size()), nom_de_domaine, information);
	}


	istr << "Inserting transaction in the database : " << endl;
	istr << "1 = good insertion, 0 = wrong insertion " << endl;

	// Insertion in the database
	DataBase base_de_donnee;
	for (const auto &trs : all_Transaction)
	{
		if (base_de_donnee.push_back(trs) == true)
		{
			istr << "1";
		}
		else
			istr << "0";
	}
	istr << endl;

	istr << "Get an element in the database :" << endl;
	string random = SHA25::sha256("HelloYou");
	istr << "Try to search for an element that is not in the database, code return :" << (base_de_donnee.get(random).second.first == 4 ? "4" : "Error") << std::endl;
	istr << "The two hashes following should be equal :" << endl;
	istr <<
		base_de_donnee.get(all_Transaction.at(5).getHashTransaction()).first << std::endl;
	istr << all_Transaction.at(5).getHashTransaction();





	istr << "---------------------------- Test on the BlockChain ----------------------------" << endl;
	Block genesis(0);
	istr << "Generation of the \"Genesis\" bloc:" << genesis.get_BlockHash() << endl << genesis.get_PreviousBlockHash() << endl;
	std::shared_ptr<Block> ptr0 = std::make_shared<Block>(genesis);

	Block block1(ptr0, transactions1);
	std::shared_ptr<Block> ptr1 = std::make_shared<Block>(block1);
	Block block2(ptr1, transactions2);
	std::vector<Block> all_blocks;


	BlockChain blockchain;


	if (receiveBlock(base_de_donnee, genesis, blockchain) == 1)
	{
		istr << "Adding the Bloc number " << genesis.get_Header().get_NumeroBloc() << endl;
		all_blocks.push_back(genesis);
	}

	istr << "Test on finding a transaction in the BlockChain " << endl;
	istr << "Should all return false" << endl;
	istr << "Try to add a block that has not been mined : Return (1=error,3=added)" << blockchain.push_back(block1) << std::endl;
	istr << (blockchain.find(t1) == true ? "transaction t1 exists" : "t1 doesn't exist") << endl;

	istr << (blockchain.find(t6) == true ? "transaction t6 exists" : "t6 doesn't exist") << endl;
	istr << "Try to add a block that has not been mined : Return (1=error,3=added)" << blockchain.push_back(block2) << std::endl;

	istr << (blockchain.find(t6) == true ? "transaction t6 exists" : "t6 doesn't exist") << endl;


	istr << "---------------------------- Test on the blocs ----------------------------" << endl;
	istr << "try to mine the BlockChain : " << endl;
	istr << "Solving the problem with difficulty of " << Constante::DIFFICULTY_MINING << endl;
	std::pair<unsigned long long, unsigned long long> nonce = block1.solveProofofWork();

	istr << "Hash found : " << SHA25::sha256(string(block1.get_Header().get_HashMerkleRoot() + std::to_string(nonce.first) + std::to_string(nonce.second))) << endl;
	istr << "The two nonce are" << nonce.first << " " << nonce.second << endl;
	istr << "There are effectively " << Constante::DIFFICULTY_MINING << " at the beginning";
	istr << endl;

	// Adding second block into the blockchain
	if (receiveBlock(base_de_donnee, block1, blockchain) == 1)
	{
		istr << "Added " << block1.get_Header().get_NumeroBloc() << endl;
		all_blocks.push_back(block1);
	}

	// Adding third
	block2.solveProofofWork();
	if (receiveBlock(base_de_donnee, block2, blockchain) == 1)
	{
		istr << "Added " << block2.get_Header().get_NumeroBloc() << endl;
		all_blocks.push_back(block2);
	}
	std::shared_ptr<Block> ptrX = std::make_shared<Block>(block2);


	Block blocx(ptrX, transactions2);


	// Try to add more than 2000 block in a not linear way
	for (int i(0); i < 1000; i++)
	{
		// This will be the vector for the transaction of the block
		std::vector<Transaction> transactionX;

		// Pick a random number,
		// If the random number is odd, then try to add into the BlockChain more block than the one add at the end (see end of the loop)
		// We pick a random block already added into the blockchain, and build a new block over it (as its child)
		int random = rand();
		// Trying to add block that should be delete afterwards
		if (random & 1)
		{

			// This will be the number of blocks we are trying to add
			for (int k(0); k < (rand() % 9); k++) {

				// Clear the vector of transactions
				transactionX.clear();

				// Push the vector
				for (int j(0); j < 6; j++)
				{
					transactionX.push_back(all_Transaction.at(rand() % all_Transaction.size()));
				}

				// Pick a random index for the block
				// The higher SIMULATION_COEFF will be, the more competitive the BlockChain will tend to be
				int ptrRandom = rand() % static_cast<int>(all_blocks.size() - static_cast<int>(SIMULATION_COEFF*all_blocks.size())) - 1
					+ SIMULATION_COEFF*all_blocks.size();

				istr << "New random Block created which as parent : " << all_blocks.at(ptrRandom).get_Header().get_NumeroBloc() << endl;
				std::shared_ptr<Block> ptrX1 = std::make_shared<Block>(all_blocks.at(ptrRandom));
				blocx = Block(ptrX1, transactionX);
				blocx.solveProofofWork();
				if (receiveBlock(base_de_donnee, blocx, blockchain) == 1)
				{
					istr << "The block was added" << blocx.get_Header().get_NumeroBloc() << endl;
					all_blocks.push_back(blocx);
				}
				else
					istr << "The block could not be added" << endl;
			}
		}

		// Now we extend our main chain
		transactionX.clear();
		for (int j(0); j < 6; j++)
		{
			transactionX.push_back(all_Transaction.at(rand() % all_Transaction.size()));
		}

		blocx = Block(ptrX, transactionX);
		blocx.solveProofofWork();
		std::shared_ptr<Block> ptrX2 = ptrX;
		ptrX = std::make_shared<Block>(blocx);

		// If the main chain has been extended, add the block
		if (receiveBlock(base_de_donnee, blocx, blockchain) == 1)
		{
			istr << "Added " << blocx.get_Header().get_NumeroBloc() << endl;
			all_blocks.push_back(blocx);
		}
		// If not, go back to the previous block
		else {
			ptrX = ptrX2;
		}
	}
	istr << "---------------------------- Test on the current state of database and blockchain after mining ----------------------------" << endl;
	istr << "Printing the current state of the BlockChain when nothing was clear" << std::endl;
	blockchain.print(istr);

	istr << endl << endl;

	istr << endl << endl;

	// base_de_donnee.print();

	using Cuple = std::tuple<int, string, Block>;
	Cuple leadingBlock = blockchain.get_LeadingBlock();
	std::map<Message, int> validated_Transaction;
	istr << "Size of the BlockChain :" << blockchain.size() << endl;
	// blockchain.clear();
	int nbfinal0(0);

	istr << "Try to find in the main chain, transactions that are marked as not valid in the datase" << std::endl;
	istr << "If not an error should be printed : " << std::endl;
	// Checking if there is not double transaction !!!
	while (leadingBlock != blockchain.get_PreviousBlock(leadingBlock))
	{
		istr << std::get<0>(leadingBlock) << endl;
		for (auto& u : std::get<2>(leadingBlock).get_Transactions_List())
		{
			istr << (base_de_donnee.get_statusTransaction(u) == 2 ? "V" : "NV") << endl;
			if (base_de_donnee.get_statusTransaction(u) != 2)
			{
				istr << " Code " << base_de_donnee.get_statusTransaction(u);
				istr << base_de_donnee.get(u).second.second.getHashDomainName() << std::endl;
				istr << base_de_donnee.get(u).second.second.getNomDomaine();
			}
			if (validated_Transaction.count(base_de_donnee.get(u).second.second) != 0)
			{
				istr << "ERROR" << std::get<0>(leadingBlock) << " " << validated_Transaction.at(base_de_donnee.get(u).second.second) << endl;
			}
			nbfinal0++;
			validated_Transaction.insert(std::pair<Message, int>(base_de_donnee.get(u).second.second, std::get<0>(leadingBlock)));
		}
		leadingBlock = blockchain.get_PreviousBlock(leadingBlock);
	}
	int nbfinal2(0);
	for (auto& u : all_Transaction)
	{
		Message uu = u.getMessage();
		if (base_de_donnee.get_statusTransaction(u.getHashTransaction()) == 1 && validated_Transaction.count(uu) != 0)
			istr << "Transaction not valid but in the main chain " << u.getHashTransaction() << endl;

		if (base_de_donnee.get_statusTransaction(u.getHashTransaction()) == 2 && validated_Transaction.count(uu) == 0)
			istr << "Transaction validated but not in the main chain " << u.getHashTransaction() << endl;
		if (base_de_donnee.get_statusTransaction(u.getHashTransaction()) == 2)
			nbfinal2++;
	}
	istr << "Number of valid Transaction and number of transaction in the main BlockChain :" << nbfinal2 << " " << nbfinal0;
	istr << "Should be equal !!!!!";
	istr << endl << endl;


	istr << "---------------------------- Test on the blocs ----------------------------" << endl;
	istr << "Some random request in the DataBase" << endl;
	for (int i(0); i < 100; i++)
	{
		base_de_donnee.request(all_Transaction.at(rand() % all_Transaction.size()).getMessage().getNomDomaine(), istr);
	}



	istr << endl << endl;

	// Check for transactions doubloons
	// std::sort(all_Transaction.begin(), all_Transaction.end(), [](const auto& a, const auto& b) {
	// 	return a.getHashTransaction() < b.getHashTransaction();
	// });
	// for (int i(0); i < all_Transaction.size() - 1; i++)
	// {
	// 	if (all_Transaction.at(i) == all_Transaction.at(i + 1))
	// 		std::cerr << "Same transaction";
	// }

	istr << endl << endl;
	istr << "---------------------------- Clear the BlockChain ----------------------------" << endl;
	istr << "Clear the BlockChain";
	blockchain.clear(istr);

	istr << endl << endl;
	istr << "---------------------------- Print the new updated and clear BlockChain ----------------------------" << endl;

	blockchain.print(istr);
	istr << "END OF THE TESTS ON THE BLOCKCHAIN";
	istr.close();
	system("cls");
	cout << "fin de l'auto generation de la base de donnee " << endl;
	cout << "ligne de commande" << endl;
	while (true)
	{
	DEBUT:
		cout << "1. Afficher le dernier bloc : \n 2. Effectuer une requete dans la base de donnée \n 3. Taille de la BDD \n 4. Taille de la blockChain" << endl;
		string c;
		std::cin >> c;
		if (c.size() > 1)
			goto DEBUT;
		switch (c[0])
		{
		case '2':
		{
			cout << "Nom de domaine que vous cherchez" << endl;
			string nom;
			std::cin >> nom;
			base_de_donnee.request(nom);
		}
		break;
		case '1':
		{
			auto last_bloc = blockchain.get_LeadingBlock();
			cout << std::get<2>(last_bloc) << endl;
		}
		break;
		case '3':
			cout << "Taille de la base de donnee : " << base_de_donnee.size() << endl;
			break;
		case '4':
			cout << "Taille de la BlockChain : " << blockchain.size() << endl;
			break;
		default:
			cout << "Erreur dans la saisie";
			goto DEBUT;
			break;
		}
	}

}

int main()
{
	srand(time(NULL));

	test_integration_BlockCHain();
	system("pause");
	return 0;

}




/*
/*
boost::asio::io_service io_service;
tcp::endpoint endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 7171);


std::shared_ptr<Peer> p = std::make_shared<Peer>(io_service, endpoint);
std::shared_ptr<Client> client = Client::create(io_service, endpoint, p);
p->addClient(client);
p->connexion();


//Serveur  t(io_service, endpoint);

io_service.run();
*/