#pragma once
#include <memory>
#include <vector>
#include <boost/serialization/vector.hpp>
#include "Transaction.h"
#include "BlockHeader.h"
#define DIFFICULTY_MINING 2
using std::vector;
class Block
{
	using ptr_Block = std::shared_ptr<Block>;

public:


	explicit Block(int);
	Block(ptr_Block, const vector<Transaction>&);
	Block(ptr_Block, int, int, vector<string>, const BlockHeader);
	Block() = delete;


	~Block();

	Block& operator=(Block);
	bool operator==(const Block&);

	ptr_Block		   getParent() const;
	const BlockHeader& getHeader() const;

	void	setLastBlock(ptr_Block);
	void	setSize(int);
	bool	isValid() const;
	bool	containsTransactions(const Transaction&) const;
	void	BuildMerkleRoot();
	paire	solveProofofWork();

	
	template<class Archive>
	void save(Archive & ar, const unsigned int version) const
	{
		ar & nombreTransaction;
		ar & header;
		ar & tailleBlock;
		ar & transactions;
		//ar & previousBlock->getHeader().getHashMerkleRoot();  // TODO send the hash of the previous block
	}

	template<class Archive>
	void load(Archive & ar, const unsigned int version)
	{
		ar & nombreTransaction;
		ar & header;
		ar & tailleBlock;
		ar & transactions;
		string hashPreviousMerkleTreeBlock;
		//ar & hashPreviousMerkleTreeBlock;
		//previousBlock = std::make_shared<Block>(0); // create a partial previous Block
		// previousBlock->header.setHashMerkleRoot(hashPreviousMerkleTreeBlock);
	}

	BOOST_SERIALIZATION_SPLIT_MEMBER()


private:
	ptr_Block previousBlock;
	int nombreTransaction;
	BlockHeader header;
	int tailleBlock;
	vector<string> transactions;
};

