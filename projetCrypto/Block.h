#pragma once
#include <memory>
#include <vector>

#include "Transaction.h"
#include "BlockHeader.h"
#define DIFFICULTY_MINING 2
using std::vector;
class Block
{
	using ptr_Block = std::shared_ptr<Block>;

public:
	Block(int); // jste pour le premier bloc 
	Block(ptr_Block,const vector<Transaction>&);
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


private:
	ptr_Block previousBlock; // mis dans block pour éviter inclusion circulaire
	int nombreTransaction;

	BlockHeader header; // c'est un std::shared_ptr<>
	int tailleBlock;
	vector<string> transactions; // Ce n'est pas les transactions, mais les hashs
};

