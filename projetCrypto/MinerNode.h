#pragma once
#include <vector>
#include <set>
#include "Node.h"
#include "BlockChain.h"
#include "Block.h"
using std::shared_ptr;
using std::vector;

class MinerNode : Node
{
public:
	MinerNode();
	~MinerNode();
	/* Gestion BlockChain*/
	bool isTransactionExist(const Transaction&) const;
	bool startNewBlock() const;
	vector<Transaction> getListTransaction(int8_t);

	/* Gestion Réseau */
	bool sendBlock();
	bool receiveBlock();
	bool addTransaction(const Transaction&);
	void removevectorTransaction(vector<shared_ptr<Transaction>>);
	void addvectorTransaction(vector<shared_ptr<Transaction>>);

private:
	std::shared_ptr<BlockChain> blockChain;
	std::set<Transaction> unconfirmedTransaction;
	

};

