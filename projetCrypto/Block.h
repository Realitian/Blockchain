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
	Block(int); // jste pour le premier bloc 

	Block(ptr_Block, const vector<Transaction>&);
	Block(ptr_Block, int, int, vector<string>, const BlockHeader);
	~Block();
	Block& operator=(Block);
	bool operator==(const Block&);

	void setLastBlock(ptr_Block);
	void setSize(int);

	ptr_Block getParent() const;
	const BlockHeader& getHeader() const;

	bool isValid() const;
	bool containsTransactions(const Transaction&) const;
	void BuildMerkleRoot();
	paire solveProofofWork();
	template<class Archive>
	void save(Archive & ar, const unsigned int version) const
	{
		ar & nombreTransaction;
		ar & header;
		ar & tailleBlock;
		ar & transactions;
		//	ar & previousBlock->getHeader() & previousBlock->nombreTransaction & previousBlock->tailleBlock;
		//	ar & previousBlock->transactions;
		std::cerr << "correct save";
	}

	template<class Archive>
	void load(Archive & ar, const unsigned int version)
	{
		ar & nombreTransaction;
		// ar & header;
		ar & tailleBlock;

		ar & transactions;
		//BlockHeader h(0); int nb; int tb; vector<string> tr;
		//ar & h & nb & tb & tr;
		previousBlock = std::make_shared<Block>(nullptr, 0, 0, vector<string>(),BlockHeader(0));
		std::cerr << "correct load" << std::endl;
	}

	template<class Archive>
	void serialize(
		Archive & ar,
		const unsigned int file_version
	) {
		boost::serialization::split_member(ar, *this, file_version);
	}

private:
	ptr_Block previousBlock; // mis dans block pour éviter inclusion circulaire
	int nombreTransaction;

	BlockHeader header;
	int tailleBlock;
	vector<string> transactions; // Ce n'est pas les transactions, mais les hashs
};

