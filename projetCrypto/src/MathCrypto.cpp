#include "MathCrypto.h"
#include <cstdlib>
#include <iostream> // for debug
#include <random>
#include <functional>
#include <climits>
namespace math_crypto
{

int Rand()
{
  std::random_device rd;
  std::mt19937 gen(rd());

  std::uniform_int_distribution<int> dist(0,INT_MAX);
  std::function<int()> f =std::bind(dist, std::ref(gen));
  return f();
}


/**
Calculer de manière rapide a ^ x mod n
**/
BigInteger Modular_Exponentiation(BigInteger a,BigInteger x,const BigInteger& n)
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
bool Is_Prime(BigInteger n,int32_t k)
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
    
    for (int32_t i = 0; i < k; ++i )
    {
        // on prend d pour obtenir un nombre premier, on aurait pu en prendre un autre
        BigInteger a = d.randBigInteger(2,n-2);     
        BigInteger x = Modular_Exponentiation(a,d,n);
        if ( x == 1 || x == n-1 )
            continue;

        for ( BigInteger r = 1; r <= s-1; ++r )
        {
            x = Modular_Exponentiation(x, 2, n);
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




BigInteger Euclid_GCD(const BigInteger &A, const BigInteger &B)
{
  return (B.getSign() == 0) ? A : Euclid_GCD(B, A % B);
}



BigInteger Extended_Euclid_GCD(const BigInteger &A, const BigInteger &B, BigInteger &X, BigInteger &Y)
{
  // Si B = 0
  if (B.getSign() == 0)
  {
    X = 1, Y = 0;
    return A;
  }
  // Sinon
  else
  {
    // Variable intérmédiaire, permet de ne pas perdre les variables précédentes
    BigInteger XX, YY;
    BigInteger D = Extended_Euclid_GCD(B, A % B, XX, YY);
    X = YY;
    Y = XX - (A / B) * YY;
    return D;
  }
  
}

}

