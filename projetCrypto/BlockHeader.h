#pragma once
#include <stdint.h>
#include <string>

#include <boost\date_time\posix_time\posix_time.hpp>

using std::string;

class BlockHeader
{
public:
	BlockHeader(int);
	~BlockHeader();
	bool operator==(const BlockHeader&) const;

	void setNonce(long int);
	void setNumero(int);
	void setHashMerkleRoot(string);

	boost::posix_time::ptime getTime() const;
	string getHashMerkleRoot() const;
	int getNumeroBloc() const;
private:
	int numeroBloc;
	boost::posix_time::ptime timestamp;
	long int nonce;
	string merkleRootHash;
};

