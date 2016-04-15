
#include <iostream>
#include <cstdlib>
#include <string>
#include <cassert>
#include <ctime>
#include "Transaction.h"
#include "BlockChain.h"
using std::cout; using std::endl;
int fonctionTest();

int main()
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
	std::pair<unsigned long long,unsigned long long> nonce = block1.solveProofofWork();
	
	cout << "Hash trouvé : " << SHA25::sha256(string(block1.getHeader().getHashMerkleRoot() + std::to_string(nonce.first) + std::to_string(nonce.second)))<< endl;
	cout << "Les 2 nonces sont" << nonce.first << " " << nonce.second << endl;
	cout << endl;
	cout << "Test copie bloc" << endl;
	Block b3 = block2;
	cout << b3.getHeader().getHashMerkleRoot() << " " << b3.getHeader().getNumeroBloc() << b3.getHeader().getTime() << endl;
	cout << block2.getHeader().getHashMerkleRoot() << " " << block2.getHeader().getNumeroBloc() << block2.getHeader().getTime() << endl;
	
	cout << endl << endl;

	system("pause");
}
