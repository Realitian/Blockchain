#include <iostream>
#include <cstdlib>
#include <cassert>
#include "BigInteger.h"
#include "RSAInterface.h"
#include "BigIntegerUtils.h"
#include "MathCrypto.h"

int fonctionTest();

int main()
{
  srand(time(NULL));
  fonctionTest();
}




int fonctionTest()
{

  // Puissance
  std::cout << "------------------- Test Puissance -------------------" <<std::endl;
  BigInteger x(4918615616);
  BigInteger y(4918615616);
  x.pow(2);
  y.pow(4);  
  x.pow(2);
  assert(x == y);
  std::cout << x << " == " << y << std::endl;
  std::cout << std::endl;

  std::cout << "------------------- Test Primité Nombre -------------------"<<std::endl;
  y=239179141;
  std::cout << " 239179141 is a prime :" << (math_crypto::Is_Prime(y)  ? "oui" : "non")<<std::endl;
  y=994616153143;
  std::cout << " 994616153143 is a prime :" << (math_crypto::Is_Prime(y)  ? "oui" : "non")<<std::endl;
  y++;
  std::cout << " 994616153144 is a prime :" << (math_crypto::Is_Prime(y)  ? "oui" : "non")<<std::endl;
  std::cout << std::endl;
  std::cout << "------------------- Test Euclide Etendu & Euclide -------------------"<<std::endl;
  x=4918615616;
  y=4918615616;
  x.pow(3);
  y.pow(4);
  BigInteger a,b;
  std::cout << " Algorithme de Euclide Etendu : "<<std::endl;
  std::cout << "* Pgcd de " << x << " et " << y << "  vaut " <<  math_crypto::Extended_Euclid_GCD(x,y,a,b) << std::endl;
  std::cout << " Coefficient de Beziers sont " << a << " " << b << std::endl;
  std::cout << " Algorithme de Euclide Simple : " <<std::endl;
  assert(x*a + y*b == math_crypto::Euclid_GCD(x,y));
  std::cout << "* Pgcd : " << math_crypto::Euclid_GCD(x,y)<<std::endl;
  std::cout << std::endl;

  // Fin 
  std::cout << "FONCTION CORRECTEMENT IMPLEMENTE" << std::endl;
  return 0;
}