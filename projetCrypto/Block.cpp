#include "Block.h"


//************************************
// Method:    Block
// FullName:  Block::Block
// Access:    public 
// Returns:   
// Qualifier:
// Parameter: ptr_Block : a reference to the previous block
// Parameter: const vector<Transaction> & : A vector of transaction which will be integrated in the block
//************************************
Block::Block(ptr_Block prevBloc, const vector<Transaction>& _transaction) :
	previousBlock(prevBloc), nombreTransaction(_transaction.size()), header(prevBloc->getHeader().getNumeroBloc() + 1),
	tailleBlock(), transactions()
{

	// Copy the Hash of the Transactions
	for (auto t : _transaction)
	{
		transactions.emplace_back(t.getHashTransaction());
	}

}

Block::Block(std::shared_ptr<Block> prv, int nbtransaction, int taille, vector<string> tr, const BlockHeader _header) :
	previousBlock(prv), nombreTransaction(nbtransaction), tailleBlock(taille),
	transactions(tr), header(_header)
{

}

//************************************
// Method:    Block : A BlockChain Block
// FullName:  Block::Block
// Access:    public 
// Returns:   
// Qualifier: Simple Constructor only used for Packet class. This constructs a semy valid Block,
//			  Also used to construct the first Block of the BlockChain
// Parameter: int
//************************************
Block::Block(int p) :
	previousBlock(nullptr), nombreTransaction(0), header(0), tailleBlock(0), transactions()
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
	previousBlock = rhs.previousBlock;
	nombreTransaction = rhs.nombreTransaction;
	tailleBlock = rhs.tailleBlock;
	transactions.clear();
	transactions = rhs.transactions;
	return *this;
}

bool Block::operator==(const Block& rhs)
{
	return (header == rhs.getHeader() && transactions == rhs.transactions
		&&   previousBlock == rhs.getParent() && nombreTransaction == rhs.nombreTransaction);
}


//************************************
// Method:    isValid : Check if the block is valid
// FullName:  Block::isValid
// Access:    public 
// Returns:   bool
// Qualifier: const
//************************************
bool Block::isValid() const
{
	return true; // TODO to implement...
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
		hashTree.at(i) = SHA25::sha256(hashTree.at(2 * i + 1) + hashTree.at(2 * i + 2));
		std::cerr << hashTree.at(i) << std::endl;
	}
	header.setHashMerkleRoot(hashTree.at(0));
	header.setTime(boost::posix_time::second_clock::local_time());
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
		string hash = SHA25::sha256(string(header.getHashMerkleRoot() + std::to_string(incr) + std::to_string(nonce)));
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



const BlockHeader& Block::getHeader() const
{
	return header;
}


//************************************
// Method:    getParent : Return a std::shared_ptr from the parent
// FullName:  Block::getParent
// Access:    public 
// Returns:   Block::ptr_Block
// Qualifier: const : 
//************************************
std::shared_ptr<Block> Block::getParent() const
{
	return previousBlock;
}


//************************************
// Method:    setLastBlock : Set the last Block reference of this Block
// FullName:  Block::setLastBlock
// Access:    public 
// Returns:   void 
// Qualifier:
// Parameter: ptr_Block : the pointer to the previous Block
//************************************
void Block::setLastBlock(std::shared_ptr<Block> prvBlock) {
	previousBlock = prvBlock;
}

//************************************
// Method:    setSize : Set the size of the BlockChain
// FullName:  Block::setSize
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: int : the size for this Block
//************************************
void Block::setSize(int size) {
	tailleBlock = size;
}


