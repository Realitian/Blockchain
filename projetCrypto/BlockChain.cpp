#include "BlockChain.h"
using Cuple = std::tuple<int, string, Block>;


BlockChain::BlockChain() :
	blocks([](const Cuple& x, const Cuple& y)
{
	return std::get<0>(x) < std::get<0>(y);
}),
orphans([](const Cuple& x, const Cuple& y)
{
	return std::get<2>(x).get_Header().get_Time() < std::get<2>(y).get_Header().get_Time();
}),
leadingChain(blocks.begin())
{

}


BlockChain::~BlockChain()
{
}


//************************************
// Method:    addBlock
// FullName:  BlockChain::addBlock
// Access:    public 
// Returns:   int
// Qualifier:
// Parameter: const Block & bloc
//************************************
int BlockChain::addBlock(const Block& bloc)
{
	if (!bloc.isValid())
		return BlockChain::ERROR_BLOCK_INVALID;
	if (bloc.get_BlockHash() == "")
	{
		try {
			orphans.insert(Cuple(bloc.get_Header().get_NumeroBloc(), bloc.get_BlockHash(), bloc));
		}
		catch (const std::exception& e)
		{
			std::cerr << "An incorrect block has failed to be insert into the Orphans chain : " << e.what();
		};
		return	BlockChain::PREVIOUS_BLOCK_UNKNOWN;
	}
	auto beg = blocks.rbegin();
	for (; beg != blocks.rend(); beg++)
	{
		if (std::get<1>(*beg) == bloc.get_PreviousBlockHash())
		{
			try {
				blocks.insert(Cuple(bloc.get_Header().get_NumeroBloc(), bloc.get_BlockHash(), bloc));
				return BlockChain::INSERT_NEW_BLOCK;
			}
			catch (const std::exception& e)
			{
				std::cerr << "An incorrect block has failed to be insert into the Block chain : " << e.what();
			};
		}
	}
	if (beg == blocks.rend())
	{
		try {
			orphans.insert(Cuple(bloc.get_Header().get_NumeroBloc(), bloc.get_BlockHash(), bloc));
		}
		catch (const std::exception& e)
		{
			std::cerr << "An incorrect block has failed to be insert into the Orphans chain : " << e.what();
		};
		return	BlockChain::PREVIOUS_BLOCK_UNKNOWN;
	}
	return BlockChain::UNKNOWN_ERROR_WHILE_ADDIND;
}





//************************************
// Method:    checkTransactionExist
// FullName:  BlockChain::checkTransactionExist
// Access:    public 
// Returns:   bool
// Qualifier:
// Parameter: const Transaction & trans
//************************************
bool BlockChain::checkTransactionExist(const Transaction& trans)
{
	if (std::any_of(blocks.rbegin(), blocks.rend(), [&trans](const Cuple& bloc) {

		if (std::get<2>(bloc).get_PreviousBlockHash() == "FIRSTHASH") // TODO for the first Block
			return false;
		return std::get<2>(bloc).containsTransactions(trans);
	}))
		return true;
	else
		return false;
}

