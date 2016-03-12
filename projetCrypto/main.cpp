#include <iostream>
#include <cstdlib>
#include "BigInteger.h"
#include "RSAInterface.h"
#include "BigIntegerUtils.h"
#include "MillerRabin.h"

static BigInteger pi(BigInteger n)
{
  BigInteger r=0, m=2;

  while ( m < n ){
    if ( isprime(m) ) ++r;
    m++;
 }
  return r;
}

int main()
{

 srand(time(NULL));
 int expected[] = {0, 4, 25, 168, 1229, 9592, 78498, 664579};
 std::cout << (isprime(7) == true ? "oui" : "non");
 for ( BigInteger n=1, e=0; n<=10000000; n*=10, ++e ) {
    BigInteger primes = pi(n);
    std::cout << "there are " << primes << "less than " << n <<std::endl;

    if ( primes.toInt() == expected[e.toInt()] ) printf("--ACHIEVE");
    else printf(" --- FAIL");
  }
  //  srand(time(NULL));
  //  std::string s("1000000000000000000000000000000000000");
  //  BigInteger a = stringToBigInteger(s);
  //  s="20000000000000000000000000000000000089954354";
  //  BigInteger b = stringToBigInteger(s);
  //  RSAInterface RSA;
//
//  //  bool isPrime=RSA.Miller(21,5);
//  //  std::cout << ((isPrime == true) ? "oui" : "non");
  //  std::cout << " " << bgg(6,5,21);
    // std::cout << d;
}


