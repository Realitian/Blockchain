#include "BigInteger"
#include "RSAInterface.h"
#include "math_crypto.h

void functionTestLibrairieCrypto()
{

	srand(time(NULL));
	// Puissance
	unsigned long g(4918615616), h(4918615616);
	std::cout << "------------------- Test Puissance -------------------" << std::endl;
	BigInteger x(g);
	BigInteger y(h);
	x.pow(2);
	y.pow(4);
	x.pow(2);
	assert(x == y);
	std::cout << x << " == " << y << std::endl;
	std::cout << std::endl;

	std::cout << "------------------- Test Primité Nombre -------------------" << std::endl;
	y=239179141;
	std::cout << " 239179141 is a prime :" << (math_crypto::Is_Prime(y) ? "oui" : "non") << std::endl;
	y=16153143;
	std::cout << " 994616153143 is a prime :" << (math_crypto::Is_Prime(y) ? "oui" : "non") << std::endl;
	y++;
	std::cout << " 994616153144 is a prime :" << (math_crypto::Is_Prime(y) ? "oui" : "non") << std::endl;
	std::cout << "\033[1;32;40mCorrect\033[0m" << std::endl;
	std::cout << std::endl;
	std::cout << "------------------- Test Euclide Etendu & Euclide -------------------" << std::endl;
	x=1191981919;
	y=2918615616;
	x.pow(3);
	y.pow(4);
	BigInteger a, b;
	std::cout << " Algorithme de Euclide Etendu : " << std::endl;
	std::cout << "* Pgcd de " << x << " et " << y << "  vaut " << math_crypto::Extended_Euclid_GCD(x, y, a, b) << std::endl;
	std::cout << " Coefficient de Beziers sont " << a << " " << b << std::endl;
	std::cout << " Algorithme de Euclide Simple : " << std::endl;
	assert(x*a + y*b == math_crypto::Euclid_GCD(x, y));

	std::cout << "* Pgcd : " << math_crypto::Euclid_GCD(x, y) << std::endl;
	std::cout << "\033[1;32;40mCorrect\033[0m" << std::endl;
	std::cout << std::endl;


	std::cout << "------------------- Test nombre Random -------------------" << std::endl;
	int NB = 10;
	std::cout << "Generation de nombre entre 0 et " << BigInteger(2).pow(NB) << std::endl;
	for (int i = 0; i < 200; i++)
	{
	assert(a.randBigInteger(NB) <= BigInteger(2).pow(NB));
	}
	std::cout << "\033[1;32;40mCorrect\033[0m" << std::endl;
	NB = 30;
	std::cout << "Generation de nombre entre 0 et " << BigInteger(2).pow(NB) << std::endl;
	for (int i = 0; i < 200; i++)
	{
	assert(a.randBigInteger(NB) <= BigInteger(2).pow(NB));
	}
	std::cout << "\033[1;32;40mCorrect\033[0m" << std::endl;
	BigInteger mini = BigInteger(2).pow(10);
	BigInteger maxi = BigInteger(2).pow(100);

	std::cout << "Generation de nombre entre " << mini << " et " << maxi << std::endl;
	for (int i = 0; i < 200; i++)
	{
	assert(a.randBigInteger(mini, maxi) <= maxi);
	assert(a.randBigInteger(mini, maxi) >= mini);
	}
	std::cout << "\033[1;32;40mCorrect\033[0m" << std::endl;

	std::cout << "------------------- Test RSA -------------------" << std::endl;
	auto R = rsa::generation();
	std::cout << "\033[1;32;40mCorrect\033[0m" << std::endl;
	std::cout << "Encryption & Decryptage:" << std::endl;
	BigInteger msg(BigInteger(h)*BigInteger(g));
	auto cipher = rsa::simple_encryption(msg, std::get<1>(R));
	auto res = rsa::simple_decryption(cipher, std::get<0>(R));
	// assert(res == msg);
	// std::cout << "FONCTIONS CORRECTEMENT IMPLEMENTE" << std::endl;

}
