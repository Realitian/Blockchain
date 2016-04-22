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
		data_.at(tr.getHashTransaction()) = int_trans(Base_Donnee::NOT_VALIDATED, tr);
	}
	catch (...)
	{
		// TODO maybe more !!
		return false;
	};
	
return	true;

}
int8_t Base_Donnee::get_status(string transaction_hash) const
{
	if (data_.find(transaction_hash) != data_.end())
		return Base_Donnee::NOT_FOUND;
	else return data_.at(transaction_hash).first;
}

int_trans Base_Donnee::get(string transaction_hash) const 
{
	if (get_status(transaction_hash) == Base_Donnee::NOT_FOUND)
	{

	}
	else return data_.at(transaction_hash);
}

