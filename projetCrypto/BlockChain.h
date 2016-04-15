#pragma once
#include <vector>
#include <algorithm>
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

