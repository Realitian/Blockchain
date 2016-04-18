#pragma once
#include <memory>
#include <boost\asio.hpp>
#include "Client.h"
#include "Identite.h"
#include "PeerMessage.h"
using ptr_Identite = std::shared_ptr<Identite>;
using boost::asio::ip::tcp;

class Peer
{
public:
	Peer(boost::asio::io_service&, tcp::endpoint&);
	Peer() = delete;
	Peer(const Peer&) = delete;
	Peer& operator=(const Peer&) = delete;
	~Peer();

	void connexion();
	void sauvegarderCle(const RSA::PrivateKey&,const RSA::PublicKey&);
	void print(const string&);
	void displayMenu();
	std::shared_ptr<Transaction> createTransaction();
	
private:
	ptr_Identite identite;
	boost::shared_ptr<Client> client;

	void clean_screen();
	void showBanner();
};

