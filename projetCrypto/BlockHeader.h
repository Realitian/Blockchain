#pragma once
#include <stdint.h>
#include <string>
#include <boost/serialization/vector.hpp>
#include <boost\date_time\posix_time\posix_time.hpp>
#include <boost\date_time\posix_time\time_serialize.hpp>
#include <boost\serialization\utility.hpp>
using std::string;
using paire = std::pair<unsigned long long, unsigned long long>;

class BlockHeader
{
public:
	explicit BlockHeader(int);
	~BlockHeader();
	bool operator==(const BlockHeader&) const;

	void setNonce(paire);
	void setNumero(int);
	void setHashMerkleRoot(string);
	void setTime(boost::posix_time::ptime);

	template<class Archive>
	void save(Archive & ar, const unsigned int version) const
	{
		ar & numeroBloc;
		ar & timestamp;
		ar & nonce;
		ar & merkleRootHash;
	}

	template<class Archive>
	void load(Archive & ar, const unsigned int version)
	{
		ar & numeroBloc;
		ar & timestamp;
		ar & nonce;
		ar & merkleRootHash;
	}

	template<class Archive>
	void serialize(
		Archive & ar,
		const unsigned int file_version
	) {
		boost::serialization::split_member(ar, *this, file_version);
	}

	boost::posix_time::ptime getTime() const;
	string getHashMerkleRoot() const;
	int getNumeroBloc() const;
private:
	int numeroBloc;
	boost::posix_time::ptime timestamp;
	paire nonce;
	string merkleRootHash;
};

