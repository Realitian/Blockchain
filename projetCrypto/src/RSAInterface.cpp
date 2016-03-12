#include "RSAInterface.h"

#define CLE_SIZE_BITS 800
#define ACCURACY_MRABIN 10
/*
BigInt Get_Prime(const int taille, const int Trial)
{
	int delta =  % (taille / 20) + 1;
	int bits = taille + delta;

	int noisy = rand() % 100 + 100;

	int counter = 0;
	BigInt W,V;
	while (1)
	{
		++ counter;
//		R.data = Get_Random(bits, 2);
		W(bits - noisy, noisy);    // empty >= 1
		//cout << W.N << endl;
//		cout << counter << endl;
//		cout << "* " << total_multiply <<  " / " <<  total_divide << " % " << total_mod << endl;
//		if (counter == 15) return 0;
		if (Miller_Rabin_Primality_Test(W, Trial))
		{
			cout << "Total Trial = " << counter << endl;
			signed_BigInt R;
			R.sign = 1;
			R.data = W.N;
			return R;
		}
	}
}


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