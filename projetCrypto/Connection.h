#pragma once
#include <boost\asio.hpp>
#include <boost\tuple\tuple.hpp>
#include <iostream>
#include <iomanip>      // std::setw
#include <boost\bind.hpp>
#include <boost\archive\text_oarchive.hpp>
#include <boost\asio\io_service.hpp>
#include <boost\archive\text_iarchive.hpp>
#include <boost\serialization\list.hpp>

//!
//! \class Connection
//!
//! \brief Abstraction of a TCP connection that implements method to send and receive object into a socket
//!
//! \author Louis Henri Franc
//!
class Connection
{
public:
	Connection(boost::asio::io_service& io_service)
		: m_socket(io_service)
	{

	}

	boost::asio::ip::tcp::socket& socket()
	{
		return m_socket;
	}

	// Ecriture asynchrone sur le socket
	template <typename T, typename Handler>
	void async_write(const T& t, Handler handler) // (3)
	{
		// On s�rialise. (4)
		std::ostringstream archive_stream;
		boost::archive::text_oarchive archive(archive_stream);
		archive << t;
		m_outbound_data = archive_stream.str();

		// On �crit un header. // (5)
		std::ostringstream header_stream;
		header_stream << std::setw(header_length)
			<< std::hex << m_outbound_data.size();
		if (!header_stream || header_stream.str().size() != header_length)
		{
			// En cas de probl�me, on informe l'appelant.
			boost::system::error_code error(boost::asio::error::invalid_argument);
			m_socket.get_io_service().post(boost::bind(handler, error));
			return;
		}

		m_outbound_header = header_stream.str();

		// On �crit les donn�es s�rialis�es dans le socket. (6)
		std::vector<boost::asio::const_buffer> buffers;
		buffers.push_back(boost::asio::buffer(m_outbound_header));
		buffers.push_back(boost::asio::buffer(m_outbound_data));
		boost::asio::async_write(m_socket, buffers, handler); // (7)
	}

	// Lecture asynchrone de donn�es depuis le socket
	template <typename T, typename Handler>
	void async_read(T& t, Handler handler)
	{
		// On r�cup�re le header (10)
		void (Connection::*f)(const boost::system::error_code&, T&, boost::tuple<Handler>)
			= &Connection::handle_read_header<T, Handler>;
		boost::asio::async_read(m_socket, boost::asio::buffer(m_inbound_header),
			boost::bind(f,
				this, boost::asio::placeholders::error, boost::ref(t),
				boost::make_tuple(handler)));
	}

	//Interpr�tation du header
	template <typename T, typename Handler>
	void handle_read_header(const boost::system::error_code& e,
		T& t, boost::tuple<Handler> handler)
	{
		if (e)
		{
			boost::get<0>(handler)(e);
		}
		else
		{
			// D�termine la longueur du vrai message (11)
			std::istringstream is(std::string(m_inbound_header, header_length));
			std::size_t m_inbound_datasize = 0;
			if (!(is >> std::hex >> m_inbound_datasize))
			{
				// Header non valide, on informe la fonction appelante
				boost::system::error_code error(boost::asio::error::invalid_argument);
				boost::get<0>(handler)(error);
				return;
			}

			// On r�cup�re les donn�es (12)
			m_inbound_data.resize(m_inbound_datasize);
			void (Connection::*f)(const boost::system::error_code&, T&, boost::tuple<Handler>)
				= &Connection::handle_read_data<T, Handler>;

			boost::asio::async_read(m_socket, boost::asio::buffer(m_inbound_data),
				boost::bind(f, this,
					boost::asio::placeholders::error, boost::ref(t), handler));
		}
	}

	// Les donn�es re�ues, on les d�s�rialise (13)
	template <typename T, typename Handler>
	void handle_read_data(const boost::system::error_code& e,
		T& t, boost::tuple<Handler> handler)
	{
		if (e)
		{
			boost::get<0>(handler)(e);
		}
		else
		{
			// On extrait (14)
			try
			{
				std::string archive_data(&m_inbound_data[0], m_inbound_data.size());
				std::istringstream archive_stream(archive_data);
				boost::archive::text_iarchive archive(archive_stream);
				archive >> t;
			}
			catch (...)
			{
				// En cas d'�chec
				boost::system::error_code error(boost::asio::error::invalid_argument);	// verifier les e
				boost::get<0>(handler)(error);
				return;
			}

			// On informe l'appelant que tout s'est bien pass�. (15)
			boost::get<0>(handler)(e);
		}
	}

private:
	// le socket membre sous jacent.
	boost::asio::ip::tcp::socket m_socket; // (1)

										   // Taille de l'header.
	enum { header_length = 8 }; // (2)

	std::string m_outbound_header;
	std::string m_outbound_data;
	char m_inbound_header[header_length];
	std::vector<char> m_inbound_data;
};



