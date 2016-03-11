#ifndef JOUEUR_H
#define JOUEUR_H
#include <string>
#include <iostream>
#include <vector>


#define PAIR std::pair<int,int>
#define VIII std::vector<PAIR>
#define VII std::vector<std::vector<int>>

class Joueur
{
public:
    Joueur(const int&);
    virtual ~Joueur();
    std::string nom_;
    uint16_t _CODE_;
    virtual PAIR jouer(VII);
protected:

};

#endif // JOUEUR_H
