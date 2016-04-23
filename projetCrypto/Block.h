#pragma once
#include <memory>
#include <vector>
#include <boost/serialization/vector.hpp>
#include "Transaction.h"
#include "BlockHeader.h"
#ifndef FIRST_BLOCK_HASH
#define FIRST_BLOCK_HASH "e037f671bf37164c071d526e8960fd9122383d5d73ef3b60f1bc9f330a15c1e1"
#endif
#define DIFFICULTY_MINING 2
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
	void	BuildMerkleRoot();
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
};

