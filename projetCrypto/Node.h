#pragma once

#include "Transaction.h"
class Node
{
public:
	Node();
	virtual ~Node();
protected:
	void helloNode();
	void helloServer();
	void getListNode();
	void sendTransaction(const Transaction&);
	void receive();
	
	std::vector<Node> nodes;
};

