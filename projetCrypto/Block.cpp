#include "Block.h"
#ifndef FIRST_BLOCK_HASH
#define FIRST_BLOCK_HASH "e037f671bf37164c071d526e8960fd9122383d5d73ef3b60f1bc9f330a15c1e1"
#endif

//************************************
// Method:    Block : construct a fully correct Block with a reference to a previous one
// FullName:  Block::Block
// Access:    public 
// Returns:   
// Qualifier:
// Parameter: ptr_Block : a reference to the previous block
// Parameter: const vector<Transaction> & : A vector of transaction which will be integrated in the block
//************************************
Block::Block(ptr_Block prevBloc, const vector<Transaction>& _transaction) :
	previousBlockHash(prevBloc->previousBlockHash), nombreTransaction(_transaction.size()), header(prevBloc->get_Header().get_NumeroBloc() + 1),
	 transactions(), blockHash()
{

	// Copy the Hash of the Transactions
	for (auto t : _transaction)
	{
		transactions.emplace_back(t.getHashTransaction());
	}
	BuildMerkleRoot();

}

//************************************
// Method:    Block : Construct a Block without no reference to the previous one
// FullName:  Block::Block
// Access:    public 
// Returns:   
// Qualifier: : previousBlockHash(previousBlockHash), nombreTransaction(nbtransaction), tailleBlock(taille), transactions(tr), header(_header),blockHash()
// Parameter: string previousBlockHash
// Parameter: int nbtransaction
// Parameter: vector<string> tr
// Parameter: const BlockHeader _header
//************************************
Block::Block(string previousBlockHash, int nbtransaction,  vector<string> tr, const BlockHeader _header) :
	previousBlockHash(previousBlockHash), nombreTransaction(nbtransaction),
	transactions(tr), header(_header),blockHash()
{
	BuildMerkleRoot();
}

//************************************
// Method:    Block : A BlockChain Block
// FullName:  Block::Block
// Access:    public 
// Returns:   
// Qualifier: Simple Constructor only used for Packet class. This constructs a semi valid Block,
//			  Also used to construct the first Block of the BlockChain
// Parameter: int
//************************************
Block::Block(int p) :

	previousBlockHash(),blockHash(FIRST_BLOCK_HASH), nombreTransaction(0), header(0), transactions()
{
	
}

Block::~Block()
{
}

Block& Block::operator=(Block rhs)
{
	if (rhs == *this)
		return *this;
	header = rhs.header;
	previousBlockHash = rhs.previousBlockHash;
	blockHash = rhs.blockHash;
	nombreTransaction = rhs.nombreTransaction;
	transactions.clear();
	transactions = rhs.transactions;
	return *this;
}

bool Block::operator==(const Block& rhs)
{
	return (header == rhs.get_Header() && transactions == rhs.transactions
		&&   previousBlockHash == rhs.get_PreviousBlockHash() && nombreTransaction == rhs.nombreTransaction);
}


//************************************
// Method:    isValid : Check if the block is valid, all the transaction added to a Block should always be verified ! because at the end
//						the block keep only a hash of the transaction
// FullName:  Block::isValid
// Access:    public 
// Returns:   bool
// Qualifier: const
//************************************
bool Block::isValid() const
{
	if (nombreTransaction != transactions.size())
		return false;
	return true;
}


//************************************
// Method:    BuildMerkleRoot
// FullName:  Block::BuildMerkleRoot
// Access:    public 
// Returns:   void
// Qualifier:
//************************************
void Block::BuildMerkleRoot()
{
	// To get a even number of transactions
	if (transactions.size() & 1) {
		transactions.push_back(transactions.at(transactions.size() - 1)); nombreTransaction++;
	}

	int N = transactions.size();

	vector<string> hashTree;
	hashTree.resize(2 * N - 1);
	for (int i = 0; i < N; i++)
		hashTree.at(2 * N - 2 - i) = transactions.at(i);
	for (int i = N - 2; i > -1; i--)
	{
		hashTree.at(i) = SHA25::sha256(SHA25::sha256(hashTree.at(2 * i + 1) + hashTree.at(2 * i + 2)));
		std::cerr << hashTree.at(i) << std::endl;
	}
	header.setHashMerkleRoot(hashTree.at(0));
	header.setTime(boost::posix_time::second_clock::local_time());
	blockHash = SHA25::sha256(SHA25::sha256(header.get_HashMerkleRoot()));
}



//************************************
// Method:    solveProofofWork
// FullName:  Block::solveProofofWork
// Access:    public 
// Returns:   paire
// Qualifier:
//************************************
paire Block::solveProofofWork()
{
	unsigned long long nonce = 0, incr = 0;
	unsigned long long limit = std::numeric_limits<unsigned long long>::max();

	string sol(DIFFICULTY_MINING, '0');
	while (true) {
		string hash = SHA25::sha256(string(header.get_HashMerkleRoot() + std::to_string(incr) + std::to_string(nonce)));
		if (hash.substr(0, DIFFICULTY_MINING) == sol)
			break;
		else
			++nonce;
		if (limit - 1 == nonce) // Increment the incr when nonce reach unsigned long long int max value
		{
			incr++;
			nonce = 0;
		}
	}
	return paire(incr, nonce);
}


bool Block::containsTransactions(const Transaction& tr) const
{
	// There is an actually improvement possible with the Merkle Root but it isn't implemented yet
	return (std::find(transactions.begin(), transactions.end(), tr.getHashTransaction()) != transactions.end());
}



const BlockHeader& Block::get_Header() const
{
	return header;
}


string Block::get_PreviousBlockHash() const
{
	return previousBlockHash;
}
string Block::get_BlockHash() const
{
	return blockHash;
}




