#include "DataBase.h"
using std::pair;
using std::map;
using std::multimap;
using paire_int_Message = std::pair<int, Message>;

DataBase::DataBase() :
	hashTransaction_to_hashMessage(), hashMessage_to_Message()
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
	if (get_statusTransaction(tr.getHashTransaction()) != DataBase::NOT_FOUND_TRANSACTION ||
		get_statusTransaction(tr.getHashTransaction()) == DataBase::OTHER_SAME_TRANSACTION_ALREADY_VALID)
		return false;
	try {

		hashTransaction_to_hashMessage.insert(std::pair<string, string>(tr.getHashTransaction(), tr.getMessage().getHashDomainName()));

		data_cuple new_entry = std::pair<string, std::pair<int, Message>>(tr.getHashTransaction(), paire_int_Message(DataBase::NOT_VALIDATED_TRANSACTION, tr.getMessage()));

		hashMessage_to_Message.insert(std::pair<string, data_cuple>(tr.getMessage().getHashDomainName(), new_entry));


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
int DataBase::get_statusTransaction(const string& transaction_hash) const
{
	if (hashTransaction_to_hashMessage.find(transaction_hash) != hashTransaction_to_hashMessage.end())
		return get_statusMessage(hashTransaction_to_hashMessage.at(transaction_hash), transaction_hash);
	else
		return DataBase::NOT_FOUND_TRANSACTION;
}

int DataBase::get_statusMessage(const string& message_hash, const string& transaction_hash) const
{
	int resCode = DataBase::NOT_FOUND_TRANSACTION;
	auto ppp = hashMessage_to_Message.equal_range(message_hash);
	if (ppp.first == ppp.second)
	{
		std::cerr << "Big Mistake in the Database" << std::endl;
	}

	for (auto it2 = ppp.first;
		it2 != ppp.second;
		++it2)
	{
		if ((it2)->second.first == transaction_hash)
		{
			resCode = (it2)->second.second.first;
		}
		else if(it2->second.second.first == VALIDATED_TRANSACTION){
			return OTHER_SAME_TRANSACTION_ALREADY_VALID;
		}
	}
	return resCode;
}
//!
//! \brief Get an element in the database given a Hash Transaction
//!
//! \param : transaction_hash The hash of the transaction
//! \return :pair<int,Transaction> Return the status of the Transaction and the transaction
//!
std::pair<string, std::pair<int, Message> >   DataBase::get(string transaction_hash) const
{
	if (get_statusTransaction(transaction_hash) == DataBase::NOT_FOUND_TRANSACTION)
	{
		Message message("", "", KeyPair());
		return data_cuple(transaction_hash, paire_int_Message(DataBase::NOT_FOUND_TRANSACTION, message));
	}
	else {
		auto ppp = hashMessage_to_Message.equal_range(hashTransaction_to_hashMessage.at(transaction_hash));
		for (auto it2 = ppp.first;
			it2 != ppp.second;
			++it2)
		{
			if ((it2)->second.first == transaction_hash)
			{
				return (it2->second);
			}
		}

	}
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
		if (get_statusTransaction(tr) != DataBase::NOT_FOUND_TRANSACTION)
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
		auto ppp = hashMessage_to_Message.equal_range(hashTransaction_to_hashMessage.at(tr));
		for (auto it2 = ppp.first;
			it2 != ppp.second;
			++it2)
		{
			if ((it2)->second.first == tr)
			{
				(it2)->second.second.first = code;
				break;
			}
		}
	}
	catch (const std::exception&)
	{
		std::cerr << "Error while updating the database !" << std::endl;
	}
}


//!
//! \brief Query the database for a domain name and print the answer of the DataBase
//!
//! \param : domainName The domain name in question
//! \return :void
//!
void  DataBase::request(const string& domainName) const
{
	std::cout << std::endl;
	std::cout << "***************************************************************************" << std::endl;
	auto ppp = hashMessage_to_Message.equal_range(SHA25::sha256(domainName));
	std::cout << "Request for the domain name : " << domainName << std::endl;
	std::cout << "Hash of the Domain name     : " << SHA25::sha256(domainName) << std::endl;
	std::cout << "Number of message for the DN: " << hashMessage_to_Message.count(SHA25::sha256(domainName)) << std::endl;
	for (auto it2 = ppp.first;
		it2 != ppp.second;
		++it2)
	{
		std::cout << "Message  " << ((*it2).second.second.first == DataBase::VALIDATED_TRANSACTION ? "VALIDATED  " : "NOT VALIDATED ") << std::endl;
		std::cout << "  Information in the Message : " << (*it2).second.second.second.getinformation() << std::endl;
		std::cout << "  Public Exponent Key of the Sender   : " << (*it2).second.second.second.getPublicKey().GetPublicExponent() << std::endl;
		std::cout << "  Modulus Key of the Sender   : " << (*it2).second.second.second.getPublicKey().GetModulus() << std::endl;

		std::cout << "  Validity of the Message  : " << ( (*it2).second.second.second.verifier()  == true ? "correct " : "non correct" )<< std::endl;
		std::cout << std::endl;
		std::cout << std::endl;

	}
	std::cout << "***************************************************************************" << std::endl ;
}

void DataBase::save(const string& fichier) const
{

	std::freopen(fichier.c_str(),"w",stdout);
	for (auto it = hashMessage_to_Message.begin(); it != hashMessage_to_Message.end(); it++)
	{
		request(it->first);
	}
}

