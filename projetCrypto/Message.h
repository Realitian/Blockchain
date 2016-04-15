#pragma once
#include <ctype.h>
#include <memory>
#include "Payload.h"
using std::string;
class Message
{
	using ptr_Payload = std::shared_ptr<Payload>;
public:
	Message(string);
	~Message();
private:
	string hashNomDomaine;
	__int32 longueurMessage;
	ptr_Payload payload;

};

