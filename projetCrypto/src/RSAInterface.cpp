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
}
/*
int Big_Prime_Bits, Trial;

void Generating()
{
	
	signed_BigInt P = Get_Prime(CLE_SIZE, Trial), Q = Get_Prime(Big_Prime_Bits, Trial);
	signed_BigInt Phi = (P - 1) * (Q - 1);
	signed_BigInt N = P * Q;

	signed_BigInt D, E, temp;
	for (E = 7; !(Extended_Euclid_GCD(E, Phi, D, temp) == One); E = E + 2);
	if (D.sign == -1)
		D = D + Phi;
		

	fout << "P = " << endl;
	fout << P << endl;
	fout << endl;
	fout << "Q = " << endl;
	fout << Q << endl;
	fout << endl;
	
	fout << "N = " << endl;
	fout << N << endl;
	fout << endl;
	fout << "E = " << endl;
	fout << E << endl;
	fout << endl;
	fout << "D = " << endl;
	fout << D << endl;

	public_out << N;
	public_out << E;
	
	
	private_out << N;
	private_out << D;
	
	fout.close();
	public_out.close();
	private_out.close();
}*/