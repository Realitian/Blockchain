#pragma once
#include <map>
#include "Transaction.h"


class Base_Donnee
{
	using int_trans = std::pair<int8_t, Transaction>;
public:
	Base_Donnee();
	~Base_Donnee();

	int_trans get(string)		 const;
	int8_t    get_status(string) const;


	bool      push_back(const Transaction&);


	enum {
		NOT_FOUND = 0,
		NOT_VALIDATED = 1,
		VALIDATED = 2
	};

private:
	std::map<string, int_trans> data_;
};

