#include "Joueur.h"

Joueur::Joueur(const int& code) :
    _CODE_(code)
{
}

Joueur::~Joueur()
{
    //dtor
}


PAIR Joueur::jouer(VII)
{
    int X,Y;
    std::cout<< "Rentrez les coordonnées du jeu"<<std::endl;
    std::cin >> X >> Y;
    std::pair<int,int> pai(X,Y);
    std::cout << "LA";
    return pai;
}
