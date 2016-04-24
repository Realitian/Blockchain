#pragma once
#include <stdint.h>
#include <string>
#include <boost\date_time\posix_time\posix_time.hpp>
#include <boost\date_time\posix_time\time_serialize.hpp>
#include <boost\serialization\utility.hpp>
using std::string;
using paire = std::pair<unsigned long long, unsigned long long>;

//!
//! \class BlockHeader
//!
//! \brief The Header of a Block. Contains all the informations that will identify uniquely a Block
//!
//! \author Louis Henri Franc
//!
class BlockHeader
{
public:
	explicit BlockHeader(int);

	BlockHeader() = delete;
	~BlockHeader();

	bool operator==(const BlockHeader&) const;

	void setNonce(paire);
	void setNumero(int);
	void setHashMerkleRoot(string);
	void setTime(boost::posix_time::ptime);

	boost::posix_time::ptime get_Time() const;
	string					 get_HashMerkleRoot() const;
	int						 get_NumeroBloc() const;
	paire					 get_Nonce()	const;
	template<class Archive>
	void save(Archive & ar, const unsigned int version) const
	{
		ar & numeroBloc;
		ar & timestamp;
		ar & nonce.first & nonce.second;
		ar & merkleRootHash;
	}

	template<class Archive>
	void load(Archive & ar, const unsigned int version)
	{
		ar & numeroBloc;
		ar & timestamp;
		unsigned long long a, b;
		ar & a & b;
		nonce = paire(a, b);
		ar & merkleRootHash;
	}

	BOOST_SERIALIZATION_SPLIT_MEMBER()

private:
	int numeroBloc;
	boost::posix_time::ptime timestamp;
	paire nonce;
	string merkleRootHash;
};

