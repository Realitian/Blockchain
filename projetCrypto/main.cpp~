#include <iostream>
#include "BigInteger.h"
#include "RSAInterface.h"
#include "BigIntegerUtils.h"

int bgg(int base,int exp,int m)
{
    int res =1;
    while(exp > 0)
    {
        if(exp & 1 > 0) res = (res*base) % m;
        exp >>=1;
        base=(base*base)%m;
    }
    return res;
}

int main()
{

    srand(time(NULL));
    std::string s("1000000000000000000000000000000000000");
    BigInteger a = stringToBigInteger(s);
    s="20000000000000000000000000000000000089954354";
    BigInteger b = stringToBigInteger(s);
    RSAInterface RSA;

    bool isPrime=RSA.Miller(21,5);
    std::cout << ((isPrime == true) ? "oui" : "non");
    std::cout << " " << bgg(6,5,21);
    // std::cout << d;
}


