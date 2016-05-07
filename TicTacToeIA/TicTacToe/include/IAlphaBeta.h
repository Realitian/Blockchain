#ifndef IA_H
#define IA_H
#include <limits>
#include <chrono>

#include "Joueur.h"
#include "Logger.h"
#define PAIR std::pair<int,int>

class IAlphaBeta : public Joueur
{
public:
    IAlphaBeta(const int&);
    virtual ~IAlphaBeta();
    PAIR jouer(VII) override;
private:
    std::vector<int> calculerBestMove   (VII &,const int ,int,int ,int);
    VIII             movePossible       (const VII);
    int              evaluer            (const VII,int);
    int              verifierVainqueur  (VII v);
    inline bool      getDiffTime        ();
    Logger l;
    std::chrono::high_resolution_clock::time_point start;

};

#endif // IA_H
