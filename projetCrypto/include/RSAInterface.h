#ifndef RSAINTERFACE_H
#define RSAINTERFACE_H
#include <iostream>
#include <cmath>

#include "BigInteger.h"
#include "BigIntegerUtils.h"
#include "MathCrypto.h"

#define ACCURACY_MRABIN 5
#define CLE_SIZE_BITS 320


namespace rsa{
	
	/* Obtenir un nombre premier */
    BigInteger Get_Prime(const int taille = CLE_SIZE_BITS, const int Trial = ACCURACY_MRABIN);

    void generation(int taille= CLE_SIZE_BITS);



}


#endif // RSAINTERFACE_H
