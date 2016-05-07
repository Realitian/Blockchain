#ifndef IA_H
#define IA_H
#include <limits>
#include <chrono>

#include "Joueur.h"
#include "Logger.h"
#define PAIR std::pair<int,int>

class IA : public Joueur
{
public:
    IA(const int&);
    virtual ~IA();
    PAIR jouer(VII) override;
private:
    std::vector<int>  calculerBestMove (VII&,const int ,int);
    VIII     movePossible     (const VII);
    int      evaluer          (const VII,int,int);
    Logger l;
    std::chrono::high_resolution_clock::time_point start;
    bool getDiffTime();

};

#endif // IA_H
