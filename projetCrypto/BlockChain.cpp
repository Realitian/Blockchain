#include "BlockChain.h"
using Cuple = std::tuple<int, string, Block>;


BlockChain::BlockChain() :
	blocks([](const Cuple& x, const Cuple& y)
{
	if ((std::get<0>(x) < std::get<0>(y)))
		return true;
	if (std::get<0>(x) == std::get<0>(y))
	{
		return (std::get<1>(x) < std::get<1>(y));
	}
	return false;
}),
orphans([](const Cuple& x, const Cuple& y)
{
	return (std::get<0>(x) < std::get<0>(y) && std::get<2>(x).get_Header().get_Time() < std::get<2>(y).get_Header().get_Time());
}),
leadingBlock(blocks.rbegin())
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
int BlockChain::push_back(const Block& bloc)
{
	// If the block is not valid
	if (!bloc.isValid())
		return BlockChain::ERROR_BLOCK_INVALID;

	if (blocks.size() == 0)
	{
		try {
			blocks.insert(Cuple(bloc.get_Header().get_NumeroBloc(), bloc.get_BlockHash(), bloc));
			leadingBlock = blocks.rbegin();
		}
		catch (const std::exception& e)
		{
			std::cerr << "An incorrect block has failed to be insert into the BlockChain chain : " << e.what();
		};
		return	BlockChain::FIRS_BLOCK_ADDED;
	}

	// If the block is not fully compose !
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

	// Pointer to the last element
	auto block_ite = blocks.rbegin();
	// avoid to be constructed multiple times
	auto end = blocks.rend();
	for (; block_ite != end; block_ite++)
	{
		// If I find the parent
		if (std::get<1>(*block_ite) == bloc.get_PreviousBlockHash())
		{
			try {
				Cuple newBloc = Cuple(bloc.get_Header().get_NumeroBloc(), bloc.get_BlockHash(), bloc);
				// inserting into the BlockChain
				blocks.insert(newBloc);

				// modify the leadingBlock if necessary
				if ( bloc.get_Header().get_NumeroBloc() > std::get<2>(*leadingBlock).get_Header().get_NumeroBloc() ) {
					for (std::set<Cuple>::reverse_iterator x = blocks.rbegin(); x != blocks.rend(); x++)
					{
						if (std::get<2>(*x) == std::get<2>(newBloc))
						{
							leadingBlock = x;
							break;
						}
					}
				}
				/*
				for (auto &tr : bloc.getTransaction())
				{
					if
				}
				*/
				return BlockChain::INSERT_NEW_BLOCK;
			}
			catch (const std::exception& e)
			{
				std::cerr << "An incorrect block has failed to be insert into the Block chain : " << e.what();
				return BlockChain::UNKNOWN_ERROR_WHILE_ADDIND;
			};
		}
	}

	// If a parent has not been found
	if (block_ite == blocks.rend())
	{
		// add it the orphans set !
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
// Method:    print
// FullName:  BlockChain::print
// Access:    public 
// Returns:   void
// Qualifier: const
//************************************
void BlockChain::print() const
{
	for (const auto& exp : blocks)
	{
		std::cout << std::get<0>(exp) << " " << std::get<1>(exp) << std::endl
			<< std::endl;
	}
}


//************************************
// Method:    find
// FullName:  BlockChain::find
// Access:    public 
// Returns:   bool
// Qualifier:
// Parameter: const Transaction & trans
//************************************
bool BlockChain::find(const Transaction& trans) const
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


#ifndef MAX_SIZE_ORPHANS
#define MAX_SIZE_ORPHANS 50
#endif
#ifndef DEPTH_DELETION
#define DEPTH_DELETION 10
#endif
//************************************
// Method:    clear
// FullName:  BlockChain::clear
// Access:    public 
// Returns:   void
// Qualifier:
//************************************
void BlockChain::clear()
{
	// Deleting ancient orphans that are no more useful
	while (orphans.size() > MAX_SIZE_ORPHANS)
	{

		auto it = orphans.begin();
		push_back(std::get<2>(*it)); // Try a last time...
		orphans.erase(it);
	}

	// If the blockChain is too small, no need to continue
	if (std::get<2>(*blocks.rbegin()).get_Header().get_NumeroBloc() < DEPTH_DELETION)
		return;


	auto  block_ite = blocks.rbegin();
	auto end = blocks.rend();

	// The Hash of the previous Block
	string previous_Block_Hash = std::get<2>(*leadingBlock).get_PreviousBlockHash();
	std::cout << "Last hash : " << previous_Block_Hash << std::endl;
	while (block_ite != end)
	{
		// If it is to early to delete the bloc
		if (std::get<2>(*block_ite).get_Header().get_NumeroBloc() > std::get<2>(*leadingBlock).get_Header().get_NumeroBloc() - DEPTH_DELETION) {
		
			std::cerr << "To early to delete " << std::get<0>(*block_ite) << std::endl;
			
			// If the block is in the main chain, update the local variable previous_Block_Hash
			if (std::get<2>(*block_ite).get_BlockHash() == previous_Block_Hash)
			{
				previous_Block_Hash = std::get<2>(*block_ite).get_PreviousBlockHash();
			}
			block_ite++;
		}

		// If the block are really far, and there should only be the main BlockChain with confirmed Block
		else
		{
			// If it is in the main chain
			if (std::get<2>(*block_ite).get_BlockHash() == previous_Block_Hash)
			{
				std::cerr << "No deletion : " << std::get<0>(*block_ite) << std::endl;

				previous_Block_Hash = std::get<2>(*block_ite).get_PreviousBlockHash();
				block_ite++;
			}
			// else delete it
			else
			{
				std::cerr << "No too early but deletion : " << std::get<0>(*block_ite) << std::endl;
				blocks.erase(*block_ite);
				block_ite++;
			}
		}
	}
}

size_t BlockChain::size() const
{
	return blocks.size() + orphans.size();
}