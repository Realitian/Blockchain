#pragma once
#include <ctype.h>
#include <memory>
#include "Payload.h"
class Message
{
public:
	Message();
	~Message();
private:
	uint8_t hashNomDomaine[32];
	__int32 longueurMessage;
	/*std::shared_ptr<*/Payload/*>*/ payload;

};

