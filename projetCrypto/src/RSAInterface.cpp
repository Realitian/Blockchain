#include "../include/RSAInterface.h"


namespace rsa
{
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

// phi_n = 260724137268046088778803276940
std::tuple<Pair,Pair> generation(int taille)
{

BACK:

    // Trouver e comme dans OpenSSL 0.9.8k
    BigInteger E(65537);
// Explication du choix : Note that because the public key is prime, it has a high chance of a gcd equal to 1 with ϕ(n)
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
    BigInteger pgcd = math_crypto::Extended_Euclid_GCD(E, phi, D, temp);
// Verification que l'algorithme d'Euclide Etendu est correct
    std::cerr << "PGCD " << pgcd << std::endl;
    BigInteger rs = E*D + phi*temp;
    std::cerr << "Opérateur de Bézoult " << rs << std::endl;
    assert(rs == pgcd);
// verification que (E*D) mod phi == 1
    assert(BigInteger(1) == math_crypto::Modular_Exponentiation(E*D,1,phi));

// e doit être impaire > 65536 et < 2^56
 //   if (D.getSign() == -1)
   //     D = D + phi;

    std::cout << "P = " << P << std::endl;
    std::cout << "Q = " << Q << std::endl;
    std::cout << std::endl;
    std::cout << "Public Key\n";
    std::cout << "D = " <<  D << std::endl;
    std::cout << "N = " << N << std::endl;
    std::cout << "Private Key\n";
    std::cout << "E = " << E << std::endl;
    std::cout << "N = " << N << std::endl;
    std::cout << std::endl;
    return std::tuple<Pair,Pair>(std::pair<BigInteger,BigInteger>(D,N),
	std::pair<BigInteger,BigInteger>(E,N));
}



BigInteger simple_encryption(const BigInteger& num,const Pair& clePu)
{
   return math_crypto::Modular_Exponentiation(num,clePu.first,clePu.second);
}

BigInteger simple_decryption(const BigInteger& num,const Pair& clePr)
{
   return math_crypto::Modular_Exponentiation(num,clePr.first,clePr.second);
}

}
