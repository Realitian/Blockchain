#pragma once
#include <memory>

#include <vector>
#include <boost/serialization/vector.hpp>
#include "Transaction.h"
#include "BlockHeader.h"
#include "../other/Constante.h"

//!
//! \class Block
//!
//! \brief A Block of the BlockChain. Contains a list of Transactions. 
//!
//! \author Louis Henri Franc
//!
using std::vector;
class Block
{
	using ptr_Block = std::shared_ptr<Block>;
public:


	explicit Block(int);
	Block(const ptr_Block, const vector<Transaction>&);
	Block(string, int, vector<string>, const BlockHeader);
	Block() = delete;

	void set_Hash_Merkle_Root(string);

	~Block();

	Block& operator=(Block);
	bool operator==(const Block&) const;

	const vector<string> get_Transactions_List() const;
	const BlockHeader&   get_Header() const;
	string			     get_PreviousBlockHash() const;
	string			     get_BlockHash() const;


	bool	isValid() const;
	bool	containsTransactions(const Transaction&) const;
	paire	solveProofofWork();


	template<class Archive>
	void save(Archive & ar, const unsigned int version) const
	{
		ar & nombreTransaction;
		ar & header;
		ar & transactions;
		ar & previousBlockHash;
		ar & blockHash;
	}

	template<class Archive>
	void load(Archive & ar, const unsigned int version)
	{
		ar & nombreTransaction;
		ar & header;
		ar & transactions;
		ar & previousBlockHash;
		ar & blockHash;
	}

	BOOST_SERIALIZATION_SPLIT_MEMBER()


private:
	string previousBlockHash; // SHA256(SHA256(previousblock.header.merkleroothash))
	string blockHash;		  // Hash of the Block

	int nombreTransaction;
	BlockHeader header;

	vector<string> transactions;
	void	BuildMerkleRoot();

};

