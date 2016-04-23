
#include <iostream>
#include <cstdlib>
#include <string>
#include <cassert>
#include <ctime>
#include "Transaction.h"

#include <boost/asio.hpp>

#include "Serveur.h"
using std::cout; using std::endl;


// ^(?([^\r\n])\s)*[^\s+?/]+[^\n]*$




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
	system("pause");
	return 0;
}




