#ifndef PARTIE_H
#define PARTIE_H
#include <cassert>
#include <string>



#include "Plateau.h"

#include "IA.h"

#define PAIR std::pair<int,int>
class Joueur;
class Partie
{
public:
    Partie(const int&,const int&);
    virtual ~Partie();

    static bool verifierVainqueur(Plateau p);
    void afficher(const std::string&);
    void jouer();

    Plateau *p_;
    Joueur *j1_;
    Joueur *j2_;
private:

};

#endif // PARTIE_H
