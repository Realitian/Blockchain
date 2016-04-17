#pragma once
#include "Identite.h"
#include "Node.h"
#include <memory>
using ptr_Identite = std::shared_ptr<Identite>;
class Peer
{
public:
	Peer(ptr_Identite);
	~Peer();
private:
	ptr_Identite identite;
	Node noeud;
};

