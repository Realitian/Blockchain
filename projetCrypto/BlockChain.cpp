#include "BlockChain.h"



BlockChain::BlockChain()
{

}


BlockChain::~BlockChain()
{
}


bool BlockChain::addBlock(const Block& bloc)
{
	if (std::find(blocks.begin(), blocks.end(),bloc) != blocks.end())
		return false;
	blocks.push_back(bloc);
	return true;
}

bool BlockChain::checkTransactionExist(const Transaction& trans)
{
	if (std::any_of(blocks.rbegin(), blocks.rend(), [&trans](const Block& bloc) {
		if (bloc.getParent() == __nullptr) // pour le premier bloc
			return false;
		return bloc.containsTransactions(trans);
	}))
		return true;
	else
		return false;
}