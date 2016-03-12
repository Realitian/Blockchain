#include <iostream>
#include <cstdlib>
#include <cassert>
#include "BigInteger.h"
#include "RSAInterface.h"
#include "BigIntegerUtils.h"
#include "MathCrypto.h"


int main()
{
  srand(time(NULL));
  BigInteger x(4918615616);
  BigInteger y(4918615616);
  x.pow(3);
  y.pow(4);
  BigInteger a,b;
  std::cout << math_crypto::Extended_Euclid_GCD(x,y,a,b) << " " << a << " " << b << std::endl;
  std::cout << math_crypto::Euclid_GCD(x,y)<<std::endl;
  std::cout << x*a+y*b;
  //assert(x*a + y*b = math_crypto::Euclid_GCD(x,y));
}


