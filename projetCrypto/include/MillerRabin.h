#ifndef INC_MILLERRABIN_H
#define INC_MILLERRABIN_H
#include <stdint.h> 
#include "BigInteger.h"
static const int DEFAULT_ACCURACY = 5;


/**
	Retourne si le nombre n est premier en utilisant l'algorithme de MillerRabin
	@n :
**/
bool isprime(BigInteger n, int32_t accuracy = DEFAULT_ACCURACY);

/*
	Effectuer l'opération d'exponentiation modulaire
**/
BigInteger pow_modulo(BigInteger,BigInteger,const BigInteger&);


#endif // INC_MILLER_RABIN_H