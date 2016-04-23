#include "Base_Donnee.h"
using int_trans = std::pair<int8_t, Transaction>;



Base_Donnee::Base_Donnee()
{
}


Base_Donnee::~Base_Donnee()
{
}


bool Base_Donnee::push_back(const Transaction& tr)
{
	if (get_status(tr.getHashTransaction()) != Base_Donnee::NOT_FOUND)
		return false;
	try {
		data_.insert(std::pair<string, int_trans>(tr.getHashTransaction(), int_trans(Base_Donnee::NOT_VALIDATED, tr)));
		//data_[tr.getHashTransaction()] = int_trans(Base_Donnee::NOT_VALIDATED, tr);
	}
	catch (std::exception e)
	{
		// TODO maybe more !!
		return false;
	};
	return true;
}
int8_t Base_Donnee::get_status(const string& transaction_hash) const
{
	if (data_.find(transaction_hash) != data_.end())
		return data_.at(transaction_hash).first;
	else 
		return Base_Donnee::NOT_FOUND;
}

int_trans Base_Donnee::get(string transaction_hash) const
{
	if (get_status(transaction_hash) == Base_Donnee::NOT_FOUND)
	{
		Transaction transaction(Identite("", ""), "", "");
		return int_trans(Base_Donnee::NOT_FOUND, transaction);
	}
	else return data_.at(transaction_hash);
}

void Base_Donnee::update(const Block& block, int8_t code)
{
	for (const auto tr : block.get_Transactions_List())
	{
		if (get_status(tr) != Base_Donnee::NOT_FOUND)
		{
			update(tr, code);
		}
		else
		{
			std::cerr << "This is really strange";
		}
	}
}


void Base_Donnee::update(const string& tr, int8_t code)
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


void  Base_Donnee::print() const
{
	for (const auto& p : data_)
	{
		std::cout << p.first << " : " <<
			(p.second.first == Base_Donnee::NOT_VALIDATED ? "NV" : "V") << std::endl;
		if (p.second.first == Base_Donnee::NOT_FOUND)
			std::cout << "BIG MISTAKE ";
	}
}