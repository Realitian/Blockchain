#include "MathCrypto.h"
#include <cstdlib>
#include <iostream> // for debug
#include <random>
#include <functional>
#include <climits>
namespace math_crypto
{

	int Rand()
	{
		std::random_device rd;
		std::mt19937 gen(rd());

		std::uniform_int_distribution<int> dist(0, INT_MAX);
		std::function<int()> f = std::bind(dist, std::ref(gen));
		return f();
	}


	/**
	Calculer de manière rapide a ^ x mod n
	**/
	BigInteger Modular_Exponentiation(BigInteger a, BigInteger x, const BigInteger& n)
	{
		BigInteger r = 1;
		if (n == 0)
			return 0;
		a = a % n;
		while (x > 0)
		{

			if (x % BigInteger(2) == 1)
			{
				r = (r * a) % n;
			}
			x /= 2;
			a = (a*a) % n;
		}

		return r;
	}


	/**
	  Retourne true si le nombre @h est pair
	  Implementation du test de Miller Rabin
	**/
	bool Is_Prime(BigInteger n, int32_t k)
	{
		// Cas particulier
		if (n == 2 || n == 3) return true;
		// Si le nombre est negatif ou qu'il est pair
		if (n <= 1 || (n % BigInteger(2) == 0)) return false;

		BigInteger s = 0, d = n - 1;
		// On ecrit n-1 = (d*2)^s
		while (d % 2 == 0)
		{
			d = d / 2;
			s++;
		}
		// Pour le nombre de test demandé
		for (int32_t i = 0; i < k; i++)
		{
			int boolean = false;
			BigInteger s1 = s;
			// on prend d pour obtenir un nombre premier, on aurait pu en prendre un autre
			BigInteger a = d.randBigInteger(2, n - 2);
			// On calcule son exponentiation modulaire
			BigInteger x = Modular_Exponentiation(a, d, n);
			if (x == 1 || x == n - 1) {
				boolean = true;
				continue;
			}
			while (!boolean && s1 > 1)
			{
				x = Modular_Exponentiation(x, 2, n);
				if (x == 1) return false;
				if (x == n - 1) { boolean = true; continue; }
				s1--;
			}
			if (!boolean)
				return false;
		}
		// n is *probably* prime
		return true;
	}



	BigInteger Euclid_GCD(const BigInteger &A, const BigInteger &B)
	{
		return (B.getSign() == 0) ? A : Euclid_GCD(B, A % B);
	}



	BigInteger Extended_Euclid_GCD(const BigInteger &A, const BigInteger &B, BigInteger &X, BigInteger &Y)
	{
		// Si B = 0
		if (B.getSign() == 0)
		{
			X = 1, Y = 0;
			return A;
		}
		// Sinon
		else
		{
			// Variable intérmédiaire, permet de ne pas perdre les variables précédentes
			BigInteger XX, YY;
			BigInteger D = Extended_Euclid_GCD(B, A % B, XX, YY);
			X = YY;
			Y = XX - (A / B) * YY;
			return D;
		}

	}



	/** Test de Solovay–Strassen  PAS FINI */
	//bool Is_Prime2(BigInteger n,int32_t k)
	//{
	//  if(p == 3 || p == 2) return true;  
	//  if(n % 2 == 0) return false;
	//  if(p < 2) return false;
	//  for(int i=0;i<k;i++)
	//  {
	//     BigInteger a = n.randBigInteger(2,n-1);     
	//     BigInteger x(a/n);
	//     if(x == 0 || Modular_Exponentiation(a,(n-1)/2,n) != Modular_Exponentiation(x,1,n))
	//       return false;
	//     return true;
	//  }
	//}
}

