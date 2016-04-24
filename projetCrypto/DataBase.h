#pragma once
#include <map>
#include "Transaction.h"
#include "Block.h"
//!
//! \class DataBase
//!
//! \brief The DataBase keeps all the Transaction and their current status of validation by the BlockChain.
//! \brief Implement a File System that will save the DataBase into File if necessary
//! \author Louis Henri Franc
//!
class DataBase
{
	using int_trans = std::pair<int, Transaction>;
public:
	DataBase();
	~DataBase();

	int_trans get(string)		 const;
	int    get_status(const string&) const;
	void	  update(const Block&, int);
	void	  update(const string&, int);
	void	  print() const;
	bool      push_back(const Transaction&);


	enum {
		NOT_FOUND = 0,
		NOT_VALIDATED = 1,
		VALIDATED = 2
	};

private:
	std::map<string, int_trans> data_;
};

