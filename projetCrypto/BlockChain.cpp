#include "BlockChain.h"
using Cuple = std::tuple<int, string, Block>;
BlockChain::BlockChain() :
	blocks([](const Cuple& x, const Cuple& y)
{
	if ((std::get<0>(x) > std::get<0>(y)))
		return true;
	if (std::get<0>(x) == std::get<0>(y))
	{
		return (std::get<1>(x) > std::get<1>(y));
	}
	return false;
}),
orphans([](const Cuple& x, const Cuple& y)
{
	return (std::get<0>(x) < std::get<0>(y) && std::get<2>(x).get_Header().get_Time() < std::get<2>(y).get_Header().get_Time());
}),
leadingBlock(blocks.begin())
{

}


BlockChain::~BlockChain()
{
}



/*!
 * 
 * \brief Try to add to the blockchain a new block. Update the internal structure of the blockchain by switching to the main branch if necessary
 *
 * \param : bloc : the bloc to add. As the BlockChain is not connected to the database, there is no check if all the transactions in the block are correct, all the transactions should have been verified before
 * \return :int : return a code corresponding to the status of the add
*/
int BlockChain::push_back(const Block& bloc)
{

	// If the block is not valid
	if (!bloc.isValid())
		return BlockChain::ERROR_BLOCK_INVALID;

	if (blocks.size() == 0)
	{
		try {
			blocks.insert(Cuple(bloc.get_Header().get_NumeroBloc(), bloc.get_BlockHash(), bloc));
			leadingBlock = blocks.begin();
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
	auto block_ite = blocks.begin();
	for (; block_ite != blocks.end(); block_ite++)
	{
		// If we find the parent
		if (std::get<1>(*block_ite) == bloc.get_PreviousBlockHash())
		{
			try {
				Cuple newBloc = Cuple(bloc.get_Header().get_NumeroBloc(), bloc.get_BlockHash(), bloc);
				// inserting into the BlockChain
				blocks.insert(newBloc);

				// modify the leadingBlock if necessary
				if ( bloc.get_Header().get_NumeroBloc() > std::get<2>(*leadingBlock).get_Header().get_NumeroBloc() ) {
					for (std::set<Cuple>::iterator x = blocks.begin(); x != blocks.end(); x++)
					{
						if (std::get<2>(*x) == std::get<2>(newBloc))
						{
							leadingBlock = x;
							break;
						}
					}
				}
				return BlockChain::INSERT_NEW_BLOCK;
			}
			catch (const std::exception& e)
			{
				std::cerr << "An incorrect block has failed to be insert into the Block chain : " << e.what();
				return BlockChain::UNKNOWN_ERROR_WHILE_ADDIND;
			};
		}
	}
	/*!< If a parent has not been found. */
	if (!(block_ite != blocks.end()))
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






//!
//! \brief Print the Blockchain
//!
//! \return :void
//!
void BlockChain::print() const
{
	for (const auto& exp : blocks)
	{
		std::cout << std::get<0>(exp) << " " << std::get<1>(exp) << std::endl
			<< std::endl;
	}
}



//!
//! \brief Find if a transaction is in the BlockChain
//! \deprecated As Database and Blockchain should be connected, you should check if the transaction is valid directly in the DataBase with
//! \param : trans 
//! \return :bool : Return a bool if the transaction is in the BlockChain
//!
bool BlockChain::find(const Transaction& trans) const
{
	if (std::any_of(blocks.rbegin(), blocks.rend(), [&trans](const Cuple& bloc) {

		if (std::get<2>(bloc).get_BlockHash() == Constante::FIRST_BLOCK_HASH) // TODO for the first Block
			return false;
		return std::get<2>(bloc).containsTransactions(trans);
	}))
		return true;
	else
		return false;
}





//!
//! \brief Clear the blockchain by keeping only the node that are in the main chain. 
//!		    Keep all block that are close to the leading Block. The number of Block to keep can be set in Constante.h
//!			
//! \return :void
//!
void BlockChain::clear()
{
	// Deleting ancient orphans that are no more useful
	while (orphans.size() > Constante::MAX_SIZE_ORPHANS)
	{

		auto it = orphans.begin();
		push_back(std::get<2>(*it)); // Try a last time...
		orphans.erase(it);
	}

	// If the blockChain is too small, no need to continue
	if (std::get<2>(*blocks.begin()).get_Header().get_NumeroBloc() < Constante::DEPTH_DELETION)
		return;


	auto  block_ite = leadingBlock;

	// The Hash of the previous Block
	string previous_Block_Hash = std::get<2>(*leadingBlock).get_PreviousBlockHash();
	std::cerr << "Last hash : " << previous_Block_Hash << std::endl;
	while (block_ite != blocks.end())
	{
		// If it is to early to delete the bloc
		if (std::get<2>(*block_ite).get_Header().get_NumeroBloc() > std::get<2>(*leadingBlock).get_Header().get_NumeroBloc() - Constante::DEPTH_DELETION) {
		
			 std::cout << "To early to delete " << std::get<0>(*block_ite) << std::endl;
			
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
				std::cout << "No deletion : " << std::get<0>(*block_ite) << std::endl;

				previous_Block_Hash = std::get<2>(*block_ite).get_PreviousBlockHash();
				block_ite++;
			}
			// else delete it
			else
			{
				std::cout << "No too early but deletion : " << std::get<0>(*block_ite) << std::endl;
				block_ite = blocks.erase(block_ite);
			}
		}
	}
}


/*!
 * 
 * \brief Return the size of the blockchain
 *
 * \return :size_t : The size of the BlockChain
*/
size_t BlockChain::size() const
{
	return blocks.size() + orphans.size();
}



/*!
 * 
 * \brief return a const reference to the "Block" (actually the tuple) at the head of the main chain
 *
 * \return :const Cuple : return the Block at the top of the BlockChain, the one that has higher number.
*/
const Cuple BlockChain::get_LeadingBlock() const
{
	return *leadingBlock;
}



/*!
 * 
 * \brief  Given a Block b, it gives back the previous Block in the BlockChain referenced in the header of b as his previous
 *
 * \param : cuple : A tuples composed of the block, his hash and his number 
 * \return :Cuple : A tuples composed of the block, his hash and his number for the previous node
*/
Cuple BlockChain::get_PreviousBlock(const Cuple& cuple) const
{
	// Get the previous hash
	string PreviousHash = std::get<2>(cuple).get_PreviousBlockHash();
	if (PreviousHash == "")
		return cuple;
	std::set<Cuple>::iterator iter = blocks.find(cuple);
	while (iter != blocks.end() && std::get<1>(*iter) != PreviousHash)
	{		
		iter++;
	}
	return *iter;
}