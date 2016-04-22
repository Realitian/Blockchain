#pragma once
#include <memory>

#include <boost\asio.hpp>
#include <boost\enable_shared_from_this.hpp>

#include "Client.h"
#include "Identite.h"
#include "PeerMessage.h"
#include "Transaction.h"
#include "Packet.h"
#include "Connection.h"
#include "Base_Donnee.h"
class Client;
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

	std::shared_ptr<Transaction> createTransaction();
	void						 connexion();
	void						 sauvegarderCle(const RSA::PrivateKey&, const RSA::PublicKey&);
	void						 print(const string&);
	void						 displayMenu();
	void						 receivePacket(const Packet&);
	void						 addClient(std::shared_ptr<Client>);
	void						 startMining();
	int8_t						 receiveTransaction(const Packet&);
	int8_t						 receiveBlock(const Packet&);

	enum 
	{
		WRONG_PACKET_RECEIVE = 0,
		WRONG_BLOCK_WITH_TRANSACTIONS_UNKNOWN = 2,
		UNKNOWN_ERROR = 1,
		CORRECT_BLOCK_RECEIVED = 4
	};
private:
	ptr_Identite		    identite;
	std::shared_ptr<Client> client;
	Base_Donnee				base_de_donnee;
	void clean_screen();
	void showBanner();
};




class Client : public std::enable_shared_from_this<Client>
{
public:
	static std::shared_ptr<Client> create(boost::asio::io_service& ios, tcp::endpoint& endpoint, std::shared_ptr<Peer> peer)
	{
		return std::shared_ptr<Client>(new Client(ios, endpoint, peer));
	}
	void write(const boost::system::error_code& error, const Packet& packet)
	{
		if (!error)
		{
			new_connection->async_write(packet,
				boost::bind(&Client::handle_write, shared_from_this(),
					boost::asio::placeholders::error)
			);
		}
	}
private:
	Client(boost::asio::io_service& io_service, tcp::endpoint& endpoint, std::shared_ptr<Peer> peer)
		:m_io_service(io_service), packet(), peerConnecte(peer)
	{
		connect(endpoint);
	}

	void connect(tcp::endpoint& endpoint)
	{
		new_connection = boost::make_shared<Connection>(m_io_service); // (2)
		tcp::socket& socket = new_connection->socket();
		socket.async_connect(endpoint, // (3)
			boost::bind(&Client::handle_connect, this,
				boost::asio::placeholders::error)
		);
	}

	void handle_connect(const boost::system::error_code& error) // (4)
	{

		if (!error)
		{
			//read(error);
		}
	}
	void read(const boost::system::error_code& error)
	{
		if (!error)
		{
			packet = Packet();
			new_connection->async_read(packet, boost::bind(&Client::handle_read, shared_from_this(),
				boost::asio::placeholders::error));
		}
	}



	void handle_read(const boost::system::error_code& e)
	{
		std::shared_ptr<Peer> m_peer = peerConnecte.lock();

		if (!e)
		{
			m_peer->receivePacket(packet);
			read(e);
		}
		else
		{
			std::cerr << "Error in handle_read " << e.message() << std::endl;
		}
	}

	void handle_write(const boost::system::error_code& e)
	{
		if (!e)
		{
			read(e);
		}

		else
		{

			std::cerr << "Error in handle_write " << e.message() << std::endl;
		}
	}


	boost::shared_ptr<Connection> new_connection;
	Packet						  packet;
	boost::asio::io_service&	  m_io_service;
	std::weak_ptr<Peer>			  peerConnecte;
};