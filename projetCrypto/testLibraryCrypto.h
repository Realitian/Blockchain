#pragma once
#include "include\MathCrypto.h"
#include "include\RSAInterface.h"
#include <vector>
#include <iostream>

#include "Transaction.h"
#include "BlockChain.h"
using std::cout; using std::endl;
using std::vector;

void testKeystaticFunction()
{
	AutoSeededRandomPool rnd;
	RSA::PrivateKey pkey;
	RSA::PrivateKey key1, key2;
	key1.GenerateRandomWithKeySize(rnd, 1024);
	KeyPair::savePrivateKey("cle.key", key1);
	cout << key1.GetModulus() << endl << key1.GetPrivateExponent();

	RSA::PrivateKey key2;
	KeyPair::loadPrivateKey("cle.key", key2);
	cout << key2.GetModulus() << " " << key2.GetPrivateExponent();
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

	Block genesis(0);
	std::shared_ptr<Block> ptr0 = std::make_shared<Block>(genesis);

	Block block1(ptr0, transactions1);
	std::shared_ptr<Block> ptr1 = std::make_shared<Block>(block1);

	Block block2(ptr1, transactions2);

	cout << "---------------------------- Test sur la BlockChain ----------------------------" << endl;
	BlockChain blockchain;
	blockchain.addBlock(genesis);
	blockchain.addBlock(block1);
	cout << (blockchain.checkTransactionExist(t1) == true ? "la transaction t1 existe" : "t1 n'existe pas") << endl;

	cout << (blockchain.checkTransactionExist(t6) == true ? "la transaction t6 existe" : "t6 n'existe pas") << endl;
	blockchain.addBlock(block2);
	cout << (blockchain.checkTransactionExist(t6) == true ? "la transaction t6 existe" : "t6 n'existe pas") << endl;

	cout << (block2.getParent()->containsTransactions(t6) == true ? "la transaction t6 existe" : "t6 n'existe pas") << endl;

	cout << "---------------------------- Test sur les blocs ----------------------------" << endl;
	cout << "Construction de l'arbre de Merkle" << endl;
	block2.BuildMerkleRoot();
	cout << "Resolution du probleme" << endl;
	std::pair<unsigned long long, unsigned long long> nonce = block1.solveProofofWork();

	cout << "Hash trouvé : " << SHA25::sha256(string(block1.getHeader().getHashMerkleRoot() + std::to_string(nonce.first) + std::to_string(nonce.second))) << endl;
	cout << "Les 2 nonces sont" << nonce.first << " " << nonce.second << endl;
	cout << endl;
	cout << "Test copie bloc" << endl;
	Block b3 = block2;
	cout << b3.getHeader().getHashMerkleRoot() << " " << b3.getHeader().getNumeroBloc() << b3.getHeader().getTime() << endl;
	cout << block2.getHeader().getHashMerkleRoot() << " " << block2.getHeader().getNumeroBloc() << block2.getHeader().getTime() << endl;

	cout << endl << endl;

}

void testPacketPrinter()
{
	Identite id("Franc", "Jerome");
	string nomDeDomaine = "facebook.com";
	string information = "retrouvez moi sur ounoenvoirnior.fr";
	Transaction t(id, nomDeDomaine, information);

	Packet p;
	p.m_type = Packet::NEW_TRANSACTION;
	p.transaction = t;
	std::cout << p;
	p = Packet();
	p.m_type = Packet::PERSON_CONNECTED;
	std::cout << p;

	p = Packet();
	p.m_type = Packet::PERSON_LEFT;
	std::cout << p;

}

void testTransaction()
{
	Identite id("Franc", "Jerome");
	cout << "--------------------------Test identite --------------------------";
	cout << id.getNom() << " " << id.getPrenom() << endl;
	cout << "Affichage de la clé :" << endl;
	KeyPair p = id.getKeyPair();
	cout << "Cle publique : " << p.getClePublique().GetPublicExponent() << " " << p.getClePublique().GetModulus() << endl;
	cout << "ClePrivee :" << p.getPrivateKey().GetPrivateExponent() << endl;

	string nomDeDomaine = "facebook.com";
	string information = "retrouvez moi sur ounoenvoirnior.fr";
	Transaction t(id, nomDeDomaine, information);
	cout << "-------------------------- Test Transaction -------------------------- " << endl;
	cout << t.toString() << endl;
	std::shared_ptr<Message> message(t.getMessage());
	cout << t.getHashTransaction() << endl;

	cout << "--------------------------Test message --------------------------";
	cout << message->getHashDomainName() << " " << message->getinformation() << message->getNomDomaine() << endl;

	bool v = message->verifier();
	if (v) cout << "Message verifier";
	else cout << "Erreur dans la verification";
}

void functionTestLibrairieCrypto()
{
	/*
	srand(time(NULL));
	// Puissance
	unsigned long g(4918615616), h(4918615616);
	std::cout << "------------------- Test Puissance -------------------" << std::endl;
	BigInteger x(g);
	BigInteger y(h);
	x.pow(2);
	y.pow(4);
	x.pow(2);
	assert(x == y);
	std::cout << x << " == " << y << std::endl;
	std::cout << std::endl;

	std::cout << "------------------- Test Primité Nombre -------------------" << std::endl;
	y=239179141;
	std::cout << " 239179141 is a prime :" << (math_crypto::Is_Prime(y) ? "oui" : "non") << std::endl;
	y=16153143;
	std::cout << " 994616153143 is a prime :" << (math_crypto::Is_Prime(y) ? "oui" : "non") << std::endl;
	y++;
	std::cout << " 994616153144 is a prime :" << (math_crypto::Is_Prime(y) ? "oui" : "non") << std::endl;
	std::cout << CORRECT << std::endl;
	std::cout << std::endl;
	std::cout << "------------------- Test Euclide Etendu & Euclide -------------------" << std::endl;
	x=1191981919;
	y=2918615616;
	x.pow(3);
	y.pow(4);
	BigInteger a, b;
	std::cout << " Algorithme de Euclide Etendu : " << std::endl;
	std::cout << "* Pgcd de " << x << " et " << y << "  vaut " << math_crypto::Extended_Euclid_GCD(x, y, a, b) << std::endl;
	std::cout << " Coefficient de Beziers sont " << a << " " << b << std::endl;
	std::cout << " Algorithme de Euclide Simple : " << std::endl;
	assert(x*a + y*b == math_crypto::Euclid_GCD(x, y));

	std::cout << "* Pgcd : " << math_crypto::Euclid_GCD(x, y) << std::endl;
	std::cout << CORRECT << std::endl;

	std::cout << std::endl;


	std::cout << "------------------- Test nombre Random -------------------" << std::endl;
	int NB = 10;
	std::cout << "Generation de nombre entre 0 et " << BigInteger(2).pow(NB) << std::endl;
	for (int i = 0; i < 200; i++)
	{
	assert(a.randBigInteger(NB) <= BigInteger(2).pow(NB));
	}
	std::cout << CORRECT << std::endl;
	NB = 30;
	std::cout << "Generation de nombre entre 0 et " << BigInteger(2).pow(NB) << std::endl;
	for (int i = 0; i < 200; i++)
	{
	assert(a.randBigInteger(NB) <= BigInteger(2).pow(NB));
	}
	std::cout << CORRECT << std::endl;
	BigInteger mini = BigInteger(2).pow(10);
	BigInteger maxi = BigInteger(2).pow(100);

	std::cout << "Generation de nombre entre " << mini << " et " << maxi << std::endl;
	for (int i = 0; i < 200; i++)
	{
	assert(a.randBigInteger(mini, maxi) <= maxi);
	assert(a.randBigInteger(mini, maxi) >= mini);
	}
	std::cout << CORRECT << std::endl;

	std::cout << "------------------- Test RSA -------------------" << std::endl;
	auto R = rsa::generation();
	std::cout << CORRECT << std::endl;
	std::cout << "Encryption & Decryptage:" << std::endl;
	BigInteger msg(BigInteger(h)*BigInteger(g));
	auto cipher = rsa::simple_encryption(msg, std::get<1>(R));
	auto res = rsa::simple_decryption(cipher, std::get<0>(R));
	// assert(res == msg);
	// std::cout << "FONCTIONS CORRECTEMENT IMPLEMENTE" << std::endl;
	*/
}