#ifndef RSAINTERFACE_H
#define RSAINTERFACE_H
#include <iostream>
#include <cmath>

#include "BigInteger.h"
#include "BigIntegerUtils.h"
#include "MathCrypto.h"

#define ACCURACY_MRABIN 10
#define CLE_SIZE_BITS 1024


namespace rsa{
	
	/* Obtenir un nombre premier */
    BigInteger Get_Prime(const int taille = CLE_SIZE_BITS, const int Trial = ACCURACY_MRABIN);

    void generation(int taille= CLE_SIZE_BITS);



}


#endif // RSAINTERFACE_H
