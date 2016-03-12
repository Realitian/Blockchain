#include "RSAInterface.h"


namespace rsa{
      BigInteger Get_Prime(const int taille, const int Trial)
      {
      //	int delta = math_crypto::Rand()  % (taille / 20) + 1;
      	int bits = taille;
      	int counter = 0;
      	BigInteger W,V;
      
      	W = W.randBigInteger(bits);  
      	while(!math_crypto::Is_Prime(W, Trial))
      	{
      		++ counter;
	      	W = W.randBigInteger(bits);  
	      	if(counter == 1000)
      			break;
      	}
      	// Pour être sur de pas rester indéfiniment dans la boucle du dessus
      	if(counter == 1000)
      	{
      	    while(!math_crypto::Is_Prime(W, Trial))
      	    {
      	    	++ counter;
	          	W-- ;
      	    }
      	}
      //	std::cerr << "Nombre d'essai pour trouver un nombre premier " << counter << std::endl;
		return W;

      }


void generation()
{
 BACK:
	BigInteger P = Get_Prime(), Q = Get_Prime();
	if(P ==  Q) goto BACK;

	BigInteger phi = (P - 1) * (Q - 1);
	BigInteger N = P * Q;

	BigInteger D, E, temp;
	for (E = 7; !(math_crypto::Extended_Euclid_GCD(E, phi, D, temp) == 1); E = E + 2);
	if (D.getSign() == -1)
		D = D + phi;
	
	std::cout << "P = " << std::endl;
	std::cout << P << std::endl;
	std::cout << std::endl;
	std::cout << "Q = " << std::endl;
	std::cout << Q << std::endl;
	std::cout << std::endl;
	std::cout << "N = " << std::endl;
	std::cout << N << std::endl;
	std::cout << std::endl;
	std::cout << "E = " << std::endl;
	std::cout << E << std::endl;
	std::cout << std::endl;
	std::cout << "D = " << std::endl;
	std::cout << D << std::endl;

}
}