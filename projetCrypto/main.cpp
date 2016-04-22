
#include <iostream>
#include <cstdlib>
#include <string>
#include <cassert>
#include <ctime>
#include "Transaction.h"

#include <boost/asio.hpp>

#include "Serveur.h"
using std::cout; using std::endl;




void testBlock();

int main()
{
	srand(time(NULL));
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
	testBlock();
	system("pause");
	return 0;
}




void testBlock()
{
	Identite id("Franc", "Jerome");
	Identite id1("CAVA", "ETtoi");
	Identite id2("Hola", "QueTal");
	Identite id3("MuyBien", "YTu");
	Identite id4("Ou", "COmmenet");
	Identite id5("Reviser", "L'espagnol");

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

	vector<Transaction> transactions1{ t1,t,t2,t22,t3,t4 };
	vector<Transaction> transactions2{ t6,t8,t82,t7,t9,t10 };
	vector<Transaction> all_Transaction;
	all_Transaction.insert(all_Transaction.end(), transactions1.begin(), transactions1.end());
	all_Transaction.insert(all_Transaction.end(), transactions2.begin(), transactions2.end());
	Block genesis(0);
	std::shared_ptr<Block> ptr0 = std::make_shared<Block>(genesis);

	Block block1(ptr0, transactions1);
	std::shared_ptr<Block> ptr1 = std::make_shared<Block>(block1);
	Block block2(ptr1, transactions2);

	cout << "---------------------------- Test sur la BlockChain ----------------------------" << endl;
	BlockChain blockchain;
	std::cout << blockchain.push_back(genesis) << std::endl;

	std::cout << blockchain.push_back(block1) << std::endl;
	cout << (blockchain.find(t1) == true ? "la transaction t1 existe" : "t1 n'existe pas") << endl;

	cout << (blockchain.find(t6) == true ? "la transaction t6 existe" : "t6 n'existe pas") << endl;
	std::cout << blockchain.push_back(block2) << std::endl;

	cout << (blockchain.find(t6) == true ? "la transaction t6 existe" : "t6 n'existe pas") << endl;

	Block block3(5);
	block3.set_Hash_Merkle_Root(SHA25::sha256("Hello world"));



	cout << blockchain.push_back(block3) << endl;
	cout << "---------------------------- Test on the blocs ----------------------------" << endl;
	cout << "Solving the problem" << endl;
	std::pair<unsigned long long, unsigned long long> nonce = block1.solveProofofWork();

	cout << "Hash found : " << SHA25::sha256(string(block1.get_Header().get_HashMerkleRoot() + std::to_string(nonce.first) + std::to_string(nonce.second))) << endl;
	cout << "The two nonce are" << nonce.first << " " << nonce.second << endl;
	cout << endl;
	cout << blockchain.push_back(block1);
	block2.solveProofofWork();
	cout << blockchain.push_back(block2);
	cout << " Size : " << blockchain.size() << endl;
	std::shared_ptr<Block> ptrX = std::make_shared<Block>(block2);

	Block blocx(ptrX, transactions2);
	for (int i(0);i < 20; i++)
	{
		std::vector<Transaction> transactionX;
		for (int j(0); j < 6; j++)
		{
			transactionX.push_back(all_Transaction.at(rand() % all_Transaction.size()));
		}
		int random = rand();
		// Trying to add block that should be delete afterwards
		 if (random & 1)
		 {
		 	blocx = Block(ptr1, transactionX);
		 	blocx.solveProofofWork();
		 	std::cout << "Adding " << i << "* : " << blockchain.push_back(blocx) << " " << std::endl;
		 
		 }

		blocx = Block(ptrX, transactionX);
		blocx.solveProofofWork();
		ptrX = std::make_shared<Block>(blocx);
		std::cout << "Size of the BlockChain : " << blockchain.size() << std::endl;
		std::cout << "Adding " << i << " : " << blockchain.push_back(blocx) << " " << std::endl;
	}

	blockchain.print();

	cout << endl << endl;
	blockchain.clear();
}