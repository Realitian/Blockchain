#include "KeyPair.h"
void testKeystaticFunction()
{
	AutoSeededRandomPool rnd;
	RSA::PrivateKey pkey;
	RSA::PrivateKey key1, key2;
	key1.GenerateRandomWithKeySize(rnd, 1024);
	KeyPair::savePrivateKey("cle.key", key1);
	cout << key1.GetModulus() << endl << key1.GetPrivateExponent();

	RSA::PrivateKey key2;
	KeyPair::loadPrivateKey("cle.key", key2);
	cout << key2.GetModulus() << " " << key2.GetPrivateExponent();
}
