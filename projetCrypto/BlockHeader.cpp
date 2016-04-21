#include "BlockHeader.h"



//************************************
// Method:    BlockHeader : Basic implementation of a BlockHeader 
//							called when a Block is created
//							The blockHeader is then further fulfill with 
//							its correct value when the Merkle root tree has been build
//							.. and the block has been mined
// FullName:  BlockHeader::BlockHeader
// Access:    public 
// Returns:   
// Qualifier: : numeroBloc(_numeroBloc), merkleRootHash(""), timestamp(), nonce()
// Parameter: int _numeroBloc
//************************************
BlockHeader::BlockHeader(int _numeroBloc) :
	numeroBloc(_numeroBloc), merkleRootHash(""), timestamp(), nonce()
{
}


BlockHeader::~BlockHeader()
{
}

bool BlockHeader::operator==(const BlockHeader& rhs) const
{
	return (merkleRootHash == rhs.merkleRootHash && numeroBloc == rhs.get_NumeroBloc() && timestamp == rhs.get_Time() );
}



void BlockHeader::setHashMerkleRoot(string hash) {
	merkleRootHash = hash;
}


void BlockHeader::setTime(boost::posix_time::ptime time) {
	timestamp = time;
}


int BlockHeader::get_NumeroBloc() const {
	return numeroBloc;
}
void BlockHeader::setNonce(paire nce) {
	nonce = nce;
}
void BlockHeader::setNumero(int nmB) {
	numeroBloc = nmB;
}

boost::posix_time::ptime BlockHeader::get_Time() const {
	return timestamp;
}
string BlockHeader::get_HashMerkleRoot() const {
	return merkleRootHash;
}
