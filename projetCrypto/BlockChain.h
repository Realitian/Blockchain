#pragma once
#include <set>
#include <algorithm>
#include <tuple>
#include "Block.h"
#include "Constante.h"

//!
//! \class BlockChain
//!
//! \brief This is the main class class of the project. It is my own implementation of the BlockChain
//!		   	
//! \author Louis Henri Franc
//!
class BlockChain
{
												  // there is a redundancy in this tuples, but it help for handling the blockchain 
public:
	using Cuple = std::tuple<int, string, Block>; // the number of the Block, the hash of the block and the Block itself

	BlockChain();
	~BlockChain();
	int  push_back(const Block&);
	bool find(const Transaction&) const;
	size_t size() const;
	void clear();
	

	void print() const;

	const Cuple  get_LeadingBlock() const;
	Cuple		 get_PreviousBlock(const Cuple& cuple) const;

	enum {
		FIRS_BLOCK_ADDED = 0,
		ERROR_BLOCK_INVALID = 1,
		PREVIOUS_BLOCK_UNKNOWN = 2,
		INSERT_NEW_BLOCK = 3,
		UNKNOWN_ERROR_WHILE_ADDIND = 4
	};
private:
	std::set<Cuple, std::function<bool(Cuple, Cuple)> > blocks; // La blockChain
	std::set<Cuple, std::function<bool(Cuple, Cuple)> > orphans; // Block that don't have previous Block in the chain
	std::set<Cuple>::iterator leadingBlock;


	
};

