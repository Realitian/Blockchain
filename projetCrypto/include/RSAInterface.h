#ifndef RSAINTERFACE_H
#define RSAINTERFACE_H
#include <iostream>
#include "BigInteger.h"
#include "BigIntegerUtils.h"
class RSAInterface
{
public:
    RSAInterface(){};
    virtual ~RSAInterface(){};
    BigInteger getRandomBigInt(BigInteger,BigInteger);
    BigInteger EulerToTientFunction();
    bool TemoinMiller(BigInteger,BigInteger);
    bool Miller(BigInteger,BigInteger);
private:
    int x;
};

#endif // RSAINTERFACE_H
