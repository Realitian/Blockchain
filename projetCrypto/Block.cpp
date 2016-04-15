#include "Block.h"

// bool setLastBlock(ptr_Block);
// bool isValid() const;
// bool containsTransactions(const Transaction&) const;
// void setSize();
// void BuildMerkleRoot();
// void solveProofofWork();
// ptr_Block getParent();
// private:
// 	ptr_Block header; // c'est un std::shared_ptr<>
// 	ptr_Block previousBlock; // mis dans block pour éviter inclusion circulaire
// 	__int8 nombreTransaction;
// 	__int8 tailleBlock;
// 	vector<Transaction> transactions; // Ce n'est pas les transactions, mais les hashs

Block::Block()
{
}


Block::~Block()
{
}

