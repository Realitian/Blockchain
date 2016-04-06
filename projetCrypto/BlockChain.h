#pragma once
#include <vector>
#include "Block.h"

class BlockChain
{
public:
	BlockChain();
	~BlockChain();
	bool addBlock(const Block&);
	bool checkTransactionExist(const Transaction&);
private:
	std::vector<Block> blocks;
};

