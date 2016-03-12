#ifndef RSAINTERFACE_H
#define RSAINTERFACE_H
#include <iostream>
#define ACCURACY_MRABIN 5
#define CLE_SIZE_BITS 320

#include "BigInteger.h"
#include "MathCrypto.h"
namespace rsa{
	
	/* Obtenir un nombre premier */
    BigInteger Get_Prime(const int taille = CLE_SIZE_BITS, const int Trial = ACCURACY_MRABIN);

    

}


#endif // RSAINTERFACE_H
