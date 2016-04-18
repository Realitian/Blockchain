
#include <iostream>
#include <cstdlib>
#include <string>
#include <cassert>
#include <ctime>
#include "Transaction.h"
#include "BlockChain.h"
#include <boost/asio.hpp>
#include "Serveur.h"
using std::cout; using std::endl;

// Serveur::Serveur(boost::asio::io_service& io_service, const tcp::endpoint& endpoint)




int main()
{
	boost::asio::io_service io_service;
	tcp::endpoint endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 7171);

	Serveur sev(io_service, endpoint);

	io_service.run();
	system("pause");
	return 0;
}
