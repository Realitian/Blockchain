#ifndef RSAINTERFACE_H
#define RSAINTERFACE_H
#include <iostream>
#include <cmath>
#include <cassert>
#include <tuple>
#include "BigInteger.h"
#include "BigIntegerUtils.h"
#include "MathCrypto.h"

#define ACCURACY_MRABIN 12
#define CLE_SIZE_BITS 600


namespace rsa{
    typedef std::pair<BigInteger,BigInteger> Pair; 

    /* Obtenir un nombre premier */
    BigInteger Get_Prime(const int taille = CLE_SIZE_BITS, const int Trial = ACCURACY_MRABIN);

    /* Generation des clés publiques et privées */
    std::tuple<Pair,Pair> generation(int taille= CLE_SIZE_BITS);

    /* Simple Encryption of a number */
    BigInteger simple_encryption(const BigInteger&,const Pair&);

    /* Simple Decryption of a number */
    BigInteger simple_decryption(const BigInteger&,const Pair&);
}


#endif // RSAINTERFACE_H
