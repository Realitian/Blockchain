#ifndef INC_MILLERRABIN_H
#define INC_MILLERRABIN_H
#include <cassert>
#include <stdint.h> 
#include "BigInteger.h"

static constexpr int DEFAULT_ACCURACY = 6;

namespace math_crypto{



    /**
		Retourne un nombre entier aléatoire en se basant sur une loi uniforme
		@return : le nombre entier
    */
    int Rand();

    /**
    	Retourne si le nombre n est premier en utilisant l'algorithme de MillerRabin
    	@n : le nombre a vérifier
    **/
    bool Is_Prime(BigInteger n, int32_t accuracy = DEFAULT_ACCURACY);
    
    /*
    	Effectuer l'opération d'exponentiation modulaire
    **/
    BigInteger Modular_Exponentiation(BigInteger,BigInteger,const BigInteger&);
    

    /**
    	Alorithme d'Euclide pour le calcul du pgcd
    	@A : un nombre A
    	@B : un nombre B
    	@return le pgcd de A et B
    **/
    BigInteger Euclid_GCD(const BigInteger &A, const BigInteger &B);

    /**
    	Algorithme de Euclide étendu
    	@A : un nombre A
    	@B : un nombre B
    	@X : coefficient de Bézout u de l'équation au+bv = pgcd(a,b)
    	@Y : coefficient de Bézout v de l'équation au+bv =  pgcd(a,b)
    	@return : le pgcd de A et B
	**/
    BigInteger Extended_Euclid_GCD(const BigInteger &A, const BigInteger &B, BigInteger &X, BigInteger &Y);

}
#endif // INC_MILLER_RABIN_H
