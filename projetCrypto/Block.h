#pragma once
#include <memory>
#include <vector>

#include "Transaction.h"
#include "BlockHeader.h"
class Block
{
	using ptr_Block = std::shared_ptr<Block>;
public:
	Block();
	~Block();
	
	bool setLastBlock(ptr_Block);
	bool isValid() const;
	bool containsTransactions(const Transaction&) const;
	void setSize(); 
	void BuildMerkleRoot();
	void solveProofofWork();
	ptr_Block getParent();
private:
	BlockHeader header; // c'est un std::shared_ptr<>
	ptr_Block previousBlock; // mis dans block pour éviter inclusion circulaire
	__int8 nombreTransaction;
	__int8 tailleBlock;
	std::vector<Transaction> transactions; // Ce n'est pas les transactions, mais les hashs
};

