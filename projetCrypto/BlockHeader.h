#pragma once
#include <stdint.h>
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
	// merkle root hash aussi
	int16_t numeroBloc;
	int64_t nonce;
	boost::posix_time::ptime timestamp;
};

