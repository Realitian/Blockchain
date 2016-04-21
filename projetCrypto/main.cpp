
#include <iostream>
#include <cstdlib>
#include <string>
#include <cassert>
#include <ctime>
#include "Transaction.h"

#include <boost/asio.hpp>

#include "Serveur.h"
using std::cout; using std::endl;





int main()
{
	boost::asio::io_service io_service;
	tcp::endpoint endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 7171);

	/*
	std::shared_ptr<Peer> p = std::make_shared<Peer>(io_service, endpoint);
	std::shared_ptr<Client> client = Client::create(io_service, endpoint, p);
	p->addClient(client);
	p->connexion();
	*/
	
	//Serveur  t(io_service, endpoint);
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

	io_service.run();
	system("pause");
	return 0;
}
