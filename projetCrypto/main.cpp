#include <unordered_map>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cassert>
#include <ctime>
#include <boost/asio.hpp>
#include <thread>
#include <future>

#include "Transaction.h"
#include "DataBase.h"
#include "BlockChain.h"
#include "Serveur.h"

#define SIMULATION_COEFF 0.9

using std::cout; using std::endl;
Block genesis(0);
bool notified = false;
using paire = std::pair<unsigned long long, unsigned long long>;
// ^(?([^\r\n])\s)*[^\s+?/]+[^\n]*$
void mine(bool& stop, std::vector<Transaction> tr, unsigned long long& nonce, unsigned long long& it, std::promise<paire >& pro)
{
	Block b(std::make_shared<Block>(genesis), tr);
	try {

		b.solveProofofWork(stop);
		auto res = b.get_Header().get_Nonce();
		nonce = res.second; it = res.first;
		pro.set_value(res);
	}
	catch (...)
	{
		pro.set_exception(std::current_exception());
	};
}


int main()
{
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

	vector<Transaction>  vec = { t,t1,t2,t22,t3,t4,t6 };

	std::promise<paire> pro;
	//	std::mutex m; 
	//	std::unique_lock<std::mutex> lock(m);
	//	std::condition_variable cv;
	unsigned long long a, b;
	bool stop = false;
	std::thread thr(mine,std::ref(stop), std::ref(vec), std::ref(a), std::ref(b), std::ref(pro));
	thr.detach();
	cout << "LA";
	//	stop = true;
	std::future<paire> f = pro.get_future();
	f.get();
	cout << "FINI !!!!";
	cout << a << " " << b;
	//Q
	//
	system("pause");
	return 0;
}