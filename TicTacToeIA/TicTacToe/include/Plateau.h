#ifndef PLATEAU_H
#define PLATEAU_H
#include <vector>
#include <iostream>
#include "Joueur.h"
#define VII std::vector<std::vector<int>>
class Plateau
{
public:
    Plateau();
    virtual ~Plateau();
    bool ajouterPion(Joueur*,const int,const int);
    void to_string();
    VII t;

private:
    bool verifierPion(int x,int y);
    bool verifierCoord(int x,int y);

};

#endif // PLATEAU_H
