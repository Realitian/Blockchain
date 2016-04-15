
#include <iostream>
#include <cstdlib>
#include <string>
#include <cassert>
#include <ctime>
#include "Transaction.h"
using std::cout; using std::endl;
int fonctionTest();

int main()
{
	Identite id("Franc","Jerome");
	cout << "Test identite :";
	cout << id.getNom() << " " << id.getPrenom() << endl;
	cout << "Affichage de la clé :";
	KeyPair p = id.getKeyPair();
	cout << "Cle publique : " << p.getClePublique().GetPublicExponent() << " " << p.getClePublique().get
	system("pause");
}
