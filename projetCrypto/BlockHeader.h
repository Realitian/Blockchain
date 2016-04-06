#pragma once
#include <ctype.h>
#include <boost\date_time\posix_time\posix_time.hpp>
class BlockHeader
{
public:
	BlockHeader();
	~BlockHeader();
	void setNonce();
	void setNumero();
	void getTime();
private:
	int8_t merkleRootTreeHash[32];
	int16_t numeroBloc;
	int64_t nonce;
	boost::posix_time::ptime timestamp;
};

