#include "Block.h"

// bool setLastBlock(ptr_Block);
// bool isValid() const;
// bool containsTransactions(const Transaction&) const;
// void setSize();
// void BuildMerkleRoot();
// void solveProofofWork();
// ptr_Block getParent();
// private:
// 	ptr_Block header; // c'est un std::shared_ptr<>
// 	ptr_Block previousBlock; // mis dans block pour éviter inclusion circulaire
// 	__int8 nombreTransaction;
// 	__int8 tailleBlock;
// 	vector<Transaction> transactions; // Ce n'est pas les transactions, mais les hashs

Block::Block(ptr_Block prevBloc, const vector<Transaction>& _transaction) :
	previousBlock(prevBloc), nombreTransaction(_transaction.size()), header(prevBloc->getHeader().getNumeroBloc()+1),
	tailleBlock(), transactions()
{
	
	// Copie les transactions par leur HASH
	for (auto t : _transaction)
	{
		transactions.emplace_back(t.getHashTransaction());
	}

}
Block::Block(int p) :
	previousBlock(nullptr), nombreTransaction(0), header(NULL),tailleBlock(0),transactions()
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

bool Block::isValid() const
{
	return true;
}


void Block::BuildMerkleRoot()
{
	// Avoir un nombre pair de transactions
	if (transactions.size() & 1) {
		transactions.push_back(transactions.at(transactions.size() - 1)); nombreTransaction++;
	}

	int N = transactions.size();

	vector<string> hashTree;
	hashTree.resize(2*N-1);
	for (int i = 0; i < N; i++)
		hashTree.at(2*N-2 - i) = transactions.at(i);
	for (int i = N - 2; i > -1; i--)
	{
		hashTree.at(i) = SHA25::sha256(hashTree.at(2 * i + 1) + hashTree.at(2*i+2) );
		std::cerr << hashTree.at(i) << std::endl;
	}
	header.setHashMerkleRoot(hashTree.at(0));
	header.setTime(boost::posix_time::second_clock::local_time());
}


paire Block::solveProofofWork()
{
	unsigned long long nonce = 0,incr = 0;
	unsigned long long limit = std::numeric_limits<unsigned long long>::max();

	string sol(DIFFICULTY_MINING, '0');
	while (true) {
		string hash = SHA25::sha256(string(header.getHashMerkleRoot() + std::to_string(incr) + std::to_string(nonce)));
		// std::cerr << hash << std::endl;
		if (hash.substr(0,DIFFICULTY_MINING) == sol)
			break;
		else
			++nonce;
		if (limit - 1 == nonce)
		{
			incr++;
			nonce = 0;
		}
	}
	return paire(incr,nonce);
}


bool Block::containsTransactions(const Transaction& tr) const
{
	return (std::find(transactions.begin(), transactions.end(), tr.getHashTransaction()) != transactions.end());
}



const BlockHeader& Block::getHeader() const
{
	return header;
}


std::shared_ptr<Block> Block::getParent() const
{
	return previousBlock;
}


void Block::setLastBlock(std::shared_ptr<Block> prvBlock) {
	previousBlock =prvBlock;
}
void Block::setSize(int size) {
	tailleBlock = size;
}


