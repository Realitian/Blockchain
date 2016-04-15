#pragma once
#include <stdint.h>
#include <string>

#include <boost\date_time\posix_time\posix_time.hpp>

using std::string;
using paire = std::pair<unsigned long long, unsigned long long>;

class BlockHeader
{
public:
	BlockHeader(int);
	~BlockHeader();
	bool operator==(const BlockHeader&) const;

	void setNonce(paire);
	void setNumero(int);
	void setHashMerkleRoot(string);
	void setTime(boost::posix_time::ptime);

	boost::posix_time::ptime getTime() const;
	string getHashMerkleRoot() const;
	int getNumeroBloc() const;
private:
	int numeroBloc;
	boost::posix_time::ptime timestamp;
	paire nonce;
	string merkleRootHash;
};

