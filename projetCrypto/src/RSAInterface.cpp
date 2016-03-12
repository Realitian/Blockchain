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
      	std::cerr << "Nombre d'essai pour trouver un nombre premier " << counter << std::endl;
		return W;

      }


        void generation(int taille)
        {
         BACK:

         	// Trouver e comme dans OpenSSL 0.9.8k
         	BigInteger E(65537);
         	BigInteger P = Get_Prime(taille/2);
         	while(math_crypto::Euclid_GCD(E,P-1) != 1) P = Get_Prime(taille/2);
         	BigInteger Q = Get_Prime(taille/2);
			while(math_crypto::Euclid_GCD(E,Q-1) != 1) Q = Get_Prime(taille/2);
        	if(P ==  Q) goto BACK;


        	// p et q doivent avoir au moins un bit différent dans leur 100 bits de poids faible
        	if(taille > 200 && (P % BigInteger(2).pow(100)) == (Q % BigInteger(2).pow(100)))
        			goto BACK;

        	BigInteger phi = (P - 1) * (Q - 1);
        	BigInteger N = P * Q;
        	
        	BigInteger D, temp;
        	math_crypto::Extended_Euclid_GCD(E, phi, D, temp);
        	// e doit être impaire > 65536 et < 2^56
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