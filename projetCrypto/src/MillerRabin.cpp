#include "MillerRabin.h"
#include <cstdlib>

/**
  Calculer de manière rapide a ^ x mod n
**/
BigInteger pow_modulo(BigInteger a,BigInteger x,const BigInteger& n)
{
	BigInteger r = 1;
	while( x > 0)
	{

		if(!(x % BigInteger(2) == 0))
		{
			r = r * a % n;
		}
		x/=2;
		a = a*a % n;
	}

	return r;
}


/**
	Retourne true si le nombre @h est pair
	Implementation du test de Miller Rabin
**/
bool isprime(BigInteger n,int32_t k)
{
  // Cas particulier
  if ( n == 2 || n == 3 ) return true;
  // Si le nombre est negatif ou qu'il est pair
  if ( n<=1 || (n % BigInteger(2) == 0) ) return false;

  BigInteger s = 0;
  // On ecrit n-1 = (d*2)^s
  for ( BigInteger m = n-1; (m % BigInteger(2) == 0); ++s, m /= 2 ); 
  BigInteger buff = s*2;
  BigInteger d = (n-1) / (buff);

  for (int32_t i = 0; i < k; ++i ) {
    BigInteger a = n.getRandBI(2,n-2);			/// </>  Attention , a corriger </>
    BigInteger x = pow_modulo(a,d,n);

    if ( x == 1 || x == n-1 )
      continue;

    for ( BigInteger r = 1; r <= s-1; ++r ) {
      x = pow_modulo(x, 2, n);
      if ( x == 1 ) return false;
      if ( x == n - 1 ) goto LOOP;
    }

    return false;
LOOP:
    continue;
  }
  // n is *probably* prime
  return true;
}
