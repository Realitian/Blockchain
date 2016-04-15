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
	previousBlock(prevBloc), nombreTransaction(_transaction.size()), header(prevBloc->getHeader().getNumeroBloc()),
	tailleBlock(), transactions()
{
	
	// Copie les transactions par leur HASH
	for (auto t : _transaction)
	{
		transactions.emplace_back(SHA25::sha256(t.toString()));
	}

}


Block::~Block()
{
}

Block& Block::operator=(Block rhs)
{
	if (rhs == *this)
		return *this;
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
	hashTree.resize(N);
	for (int i = 0; i < N; i++)
		hashTree.at(N - i + 1) = transactions.at(i);
	for (int i = N - 2; i > -1; i--)
	{
		hashTree.at(i) = SHA25::sha256(hashTree.at(2 * i + 1) + hashTree.at(2*i+2) );
	}
	header.setHashMerkleRoot(hashTree.at(0));
}


long int Block::solveProofofWork()
{
	int nonce = 0;
	string sol(DIFFICULTY_MINING, ' ');
	while (true) {
		string hash = SHA25::sha256(string(header.getHashMerkleRoot() + std::to_string(nonce)));
		if (hash.substr(0, DIFFICULTY_MINING) == sol)
			break;
		else
			++nonce;
	}
	return nonce;
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


