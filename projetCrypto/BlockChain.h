#pragma once
#include <set>
#include <algorithm>
#include <tuple>
#include "Block.h"
class BlockChain
{
	using Cuple = std::tuple<int, string, Block>; // the number of the Block, the hash of the block and the Block itself
												  // there is a redundancy in this tuples, but it help for handling the blockchain 
public:
	BlockChain();
	~BlockChain();
	int  push_back(const Block&);
	bool find(const Transaction&) const;
	size_t size() const;
	void clear();
	void print() const;
private:
	std::set<Cuple, std::function<bool(Cuple, Cuple)> > blocks; // La blockChain
	std::set<Cuple, std::function<bool(Cuple, Cuple)> > orphans; // Block that don't have previous Block in the chain
	std::set<Cuple>::reverse_iterator leadingBlock;


	enum {
		FIRS_BLOCK_ADDED = 0,
		ERROR_BLOCK_INVALID = 1,
		PREVIOUS_BLOCK_UNKNOWN = 2,
		INSERT_NEW_BLOCK = 3,
		UNKNOWN_ERROR_WHILE_ADDIND = 4
	};
};

