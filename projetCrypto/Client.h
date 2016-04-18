#include "boost\asio.hpp"
#include "Packet.h"
#include "Connection.h"
#include "boost\enable_shared_from_this.hpp"
#include <boost\make_shared.hpp>
#include <vector>
using boost::asio::ip::tcp;



class Client : public boost::enable_shared_from_this<Client>
{
public:
	static boost::shared_ptr<Client> create(boost::asio::io_service& ios, tcp::endpoint& endpoint)
	{
		return boost::shared_ptr<Client>(new Client(ios, endpoint));
	}
	void write(const boost::system::error_code& error)
	{
		cht_msg.m_type = Packet::NEW_MSG;
		std::string mst;
		std::vector<std::string > v;
		getchar();
		if (!error)
		{
			//	std::cerr << "dans write, sans erreur" << std::endl;
			new_connection->async_write(cht_msg,
				boost::bind(&Client::handle_write, shared_from_this(),
					boost::asio::placeholders::error)
			);
		}
	}
private:
	Client(boost::asio::io_service& io_service, tcp::endpoint& endpoint)
		:m_io_service(io_service), cht_msg()
	{
		// On tente de se connecter au serveur // (1)
		connect(endpoint);

	}

	void connect(tcp::endpoint& endpoint)
	{
		new_connection = boost::make_shared<Connection>(m_io_service); // (2)
																		   // std::cerr << "dans connect" << std::endl;
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
			read(error);
		//	write(error);

		}
	}
	void read(const boost::system::error_code& error)
	{
		if (!error)
		{
			// std::cerr << "dans read, sans erreur" << std::endl;
			new_connection->async_read(cht_msg, boost::bind(&Client::handle_read, shared_from_this(),
				boost::asio::placeholders::error));
		}
	}



	void handle_read(const boost::system::error_code& e)
	{
		//std::cerr << "dans handle read" << std::endl;
		if (!e)
		{
			// std::cout << "Nouveau message recu " << cht_msg.m_type <<  " " << cht_msg.m_message << std::endl;
			if (cht_msg.m_type == 0) {
				std::cout << cht_msg.m_type << std::endl;
			}
			// e.clear();
			// write(e);
		}
		else
		{
			std::cerr << e.message() << std::endl;
		}
	}

	void handle_write(const boost::system::error_code& e)
	{
		// std::cerr << "dans handle write" << std::endl;

		if (!e)
		{
			// std::cout << "Message envoye" << std::endl;
			read(e);
		}
		else
		{
			std::cerr << e.message();
		}
	}
	bool donnerecu = false;
	boost::shared_ptr<Connection> new_connection;
	Packet cht_msg;
	boost::asio::io_service&	m_io_service;
};
