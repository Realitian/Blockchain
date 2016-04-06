#pragma once
#include "Identite.h"
#include "Node.h"
#include <memory>
class Peer
{
public:
	Peer();
	~Peer();
	Identite getIdentity() const;
private:
	std::shared_ptr<Identite> identite;
	Node noeud;
};

