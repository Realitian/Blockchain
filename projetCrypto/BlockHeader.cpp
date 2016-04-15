#include "BlockHeader.h"



BlockHeader::BlockHeader(int _numeroBloc) :
	numeroBloc(_numeroBloc)
{
}


BlockHeader::~BlockHeader()
{
}

bool BlockHeader::operator==(const BlockHeader& rhs) const
{
	return (merkleRootHash == rhs.merkleRootHash && numeroBloc == rhs.getNumeroBloc() && timestamp == rhs.getTime() );
}



void BlockHeader::setHashMerkleRoot(string hash) {
	merkleRootHash = hash;
}


void BlockHeader::setTime(boost::posix_time::ptime time) {
	timestamp = time;
}


int BlockHeader::getNumeroBloc() const {
	return numeroBloc;
}
void BlockHeader::setNonce(paire nce) {
	nonce = nce;
}
void BlockHeader::setNumero(int nmB) {
	numeroBloc = nmB;
}

boost::posix_time::ptime BlockHeader::getTime() const {
	return timestamp;
}
string BlockHeader::getHashMerkleRoot() const {
	return merkleRootHash;
}
