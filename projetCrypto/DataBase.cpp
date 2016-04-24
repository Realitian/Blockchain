#include "DataBase.h"
using int_trans = std::pair<int, Transaction>;



DataBase::DataBase()
{
}


DataBase::~DataBase()
{
}


//!
//! \brief Push a new Transaction into the DataBase
//!
//! \param : tr 
//! \return :bool : Return True if the transactions was added, False else
//!
bool DataBase::push_back(const Transaction& tr)
{
	if (get_status(tr.getHashTransaction()) != DataBase::NOT_FOUND)
		return false;
	try {
		data_.insert(std::pair<string, int_trans>(tr.getHashTransaction(), int_trans(DataBase::NOT_VALIDATED, tr)));
		//data_[tr.getHashTransaction()] = int_trans(DataBase::NOT_VALIDATED, tr);
	}
	catch (std::exception e)
	{
		// TODO maybe more !!
		return false;
	};
	return true;
}
//!
//! \brief Get the status of transaction_hash
//!
//! \param : transaction_hash 
//! \return :int : Return on of the Code for the DataBase entries
//!
int DataBase::get_status(const string& transaction_hash) const
{
	if (data_.find(transaction_hash) != data_.end())
		return data_.at(transaction_hash).first;
	else 
		return DataBase::NOT_FOUND;
}

//!
//! \brief Get an element in the database given a Hash Transaction
//!
//! \param : transaction_hash The hash of the transaction
//! \return :pair<int,Transaction> Return the status of the Transaction and the transaction
//!
int_trans DataBase::get(string transaction_hash) const
{
	if (get_status(transaction_hash) == DataBase::NOT_FOUND)
	{
		Transaction transaction(Identite("", ""), "", "");
		return int_trans(DataBase::NOT_FOUND, transaction);
	}
	else return data_.at(transaction_hash);
}

//!
//! \brief Update all the element in the block in the DataBase
//!
//! \param : block : the block that contains the transactions that will be updated in the DataBase
//! \param : code : The code that will be link with the transactions
//! \return :void
//!
void DataBase::update(const Block& block, int code)
{
	for (const auto tr : block.get_Transactions_List())
	{
		if (get_status(tr) != DataBase::NOT_FOUND)
		{
			update(tr, code);
		}
		else
		{
			std::cerr << "This is really strange";
		}
	}
}


//!
//! \brief Update the entry tr with the code code
//!
//! \param : tr 
//! \param : code 
//! \return :void
//!
void DataBase::update(const string& tr, int code)
{
	try
	{
		data_.at(tr) = int_trans(code, data_.at(tr).second);
	}
	catch (const std::exception&)
	{
		std::cerr << "Error while updating the database !" << std::endl;
	}
}


//!
//! \brief Print all the entries in the Database 
//!  First print the Hash of an entry and his Status
//! \return :void
//!
void  DataBase::print() const
{
	for (const auto& p : data_)
	{
		std::cout << p.first << " : " <<
			(p.second.first == DataBase::NOT_VALIDATED ? "NV" : "V") << std::endl;
		if (p.second.first == DataBase::NOT_FOUND)
			std::cout << "BIG MISTAKE ";
	}
}