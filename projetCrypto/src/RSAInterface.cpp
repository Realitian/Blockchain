#include "RSAInterface.h"

namespace math
{
// Retourne ( base**exp ) % m
BigInteger ExpoModulaire(BigInteger base,BigInteger exp,BigInteger m)
{
    BigInteger res(1);
    while((exp-1) >= 0)
    {
        BigInteger buff;
        if(!(exp % BigInteger(2) == 0))
        {
            buff = res*base;
            res = buff % m;
        }
        exp/=2;
        buff=base*base;
        base=buff % m;
    }
    return res;
}
}


BigInteger RSAInterface::getRandomBigInt(BigInteger minimum,BigInteger maximum )
{

    BigInteger res(0);
    BigInteger buff(1);
    int nbBits(0);

  //   while( (BigInt::pow(BigInt(2),nbBits) <= maximum)
  //  {
  //     std::cout << BigInt::pow(BigInt(2),nbBits) << " " << nbBits<< " " << std::endl;
  //     nbBits++;
  //  }
    for(int i=0; i<150; i++)
    {
        if(rand() & 1)
        {
            res += buff;
        }
        buff*=2;
    }
    return res;
}


bool RSAInterface::TemoinMiller(BigInteger a,BigInteger n)
{

    if(( n % 2 == 0) || n < 3)
    {
        throw "Wrong input";
        return false;
    }
    BigInteger d(n-1);
    BigInteger s(0);
    while ( d%2 == 0 )
    {
        d = d/2;
        s++;
    }
   std::cout << "d= " << d << " s=" << s <<std::endl;
    BigInteger x = math::ExpoModulaire(a,d,n);
    std::cout << "x= " << x << std::endl;
    if ( x == 1 || x == n-1 )
    {
        return false ;
    }

    while ( s>1)
    {
        x = math::ExpoModulaire(x,2,n);
        if (x == n-1)
        {
            return false;
        }
        s-- ;
    }

    return true;


}
bool RSAInterface::Miller(BigInteger n,BigInteger k)
{

    if((n % 2 == 0) || n < 3 || k < 1)
    {
        throw "Wrong input";
        return false;
    }
    while(k > 0)
    {
	k--;
        std::cout << "LA "<< std::endl;
        BigInteger buff = this->getRandomBigInt(2,n-2);
        if(this->TemoinMiller(buff,n))
        {
            std::cout << "a= " << buff;
            return false;
        }
    }

    return true;
}
