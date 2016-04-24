#pragma once
#include <map>
#include <fstream>

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
	using data_cuple = std::pair<string, std::pair<int,Message> >;
	
public:
	DataBase();
	~DataBase();

	void	   request(const string&) const;
	data_cuple get(string)	const;
	int		   get_statusTransaction(const string&) const;
	int		   get_statusMessage(const string&,const string&) const;
	void	   save(const string&) const;

	void	  update(const Block&, int);
	void	  update(const string&, int);
	void	  print() const;
	bool      push_back(const Transaction&);


	enum {
		NOT_FOUND_TRANSACTION = 0,
		NOT_VALIDATED_TRANSACTION = 1,
		VALIDATED_TRANSACTION = 2,
		OTHER_SAME_TRANSACTION_ALREADY_VALID = 3
	};

private:
	std::map<string, string> hashTransaction_to_hashMessage;
	std::multimap<string, data_cuple> hashMessage_to_Message;
};

