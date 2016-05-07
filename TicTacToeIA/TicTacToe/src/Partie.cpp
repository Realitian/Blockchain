#include "Partie.h"

Partie::Partie(const int& j1,const int& j2) :
    p_(new Plateau()),
    j1_( (j1 == 0) ? new IA(j1) : new Joueur(j1)),
    j2_( (j2 == 0) ? new IA(j2) : new Joueur(j2))
{
    assert(j1 != j2);
    jouer();
}

Partie::~Partie()
{
    delete j1_;
    delete j2_;
}


void Partie::jouer()
{
    int nbreTour = 0;
    bool _vainqueur = false;
    while( ! _vainqueur)
    {
        nbreTour++;
        p_->to_string();
        PAIR xy1 = j1_->jouer(p_->t);
        int compteur = 4;
        while(--compteur)
        {
            if(true == p_->ajouterPion(j1_,xy1.first,xy1.second))
                break;
            afficher(std::string(std::to_string(j1_->_CODE_)+": mauvaise entree pour "+std::to_string(xy1.first)+" "+std::to_string(xy1.second )));
            xy1 = j1_->jouer(p_->t);
        }
        _vainqueur = verifierVainqueur(*p_);
        if(_vainqueur)
        {
            afficher(std::string(std::to_string(j1_->_CODE_)+": a gagne"));
            break;
        }
        if(compteur == 0)
        {
            afficher(std::string(std::to_string(j1_->_CODE_)+": a perdu"));
            break;
        }
        if(nbreTour == 5)
        {
            afficher("MATCH NUL");
            break;
        }
        PAIR xy2 = j2_->jouer(p_->t);
        compteur = 4;
        while(--compteur)
        {
            if(p_->ajouterPion(j2_,xy2.first,xy2.second) == true)
                break;
            afficher(std::string(std::to_string(j2_->_CODE_)+": mauvaise entree pour "+std::to_string(xy2.first)+" "+std::to_string(xy2.second )));
            xy2 = j2_->jouer(p_->t);
        }
        _vainqueur = verifierVainqueur(*p_);
        if(_vainqueur)
        {
            afficher(std::string(std::to_string(j2_->_CODE_)+": a gagne"));
        }
        if(compteur == 0)
        {
            afficher(std::string(std::to_string(j2_->_CODE_)+": a perdu"));
            break;
        }

    }

}


void Partie::afficher(const std::string& err)
{
    std::cout << std::endl<< err << std::endl;
}



bool Partie::verifierVainqueur(Plateau p)
{
    if(p.t.at(0).at(0) == p.t.at(0).at(1) && p.t.at(0).at(1) == p.t.at(0).at(2) && p.t.at(0).at(1) != -1)
        return true;
    if(p.t.at(1).at(0) == p.t.at(1).at(1) && p.t.at(1).at(1) == p.t.at(1).at(2) && p.t.at(1).at(1) != -1)
        return true;
    if(p.t.at(2).at(0) == p.t.at(2).at(1) && p.t.at(2).at(1) == p.t.at(2).at(2) && p.t.at(2).at(1) != -1)
        return true;
    if(p.t.at(0).at(0) == p.t.at(1).at(0) && p.t.at(1).at(0) == p.t.at(2).at(0) && p.t.at(2).at(0) != -1)
        return true;
    if(p.t.at(0).at(1) == p.t.at(1).at(1) && p.t.at(1).at(1) == p.t.at(2).at(1) && p.t.at(2).at(1) != -1)
        return true;
    if(p.t.at(0).at(2) == p.t.at(1).at(2) && p.t.at(1).at(2) == p.t.at(2).at(2) && p.t.at(2).at(2) != -1)
        return true;
    if(p.t.at(0).at(0) == p.t.at(1).at(1) && p.t.at(1).at(1) == p.t.at(2).at(2) && p.t.at(0).at(0) != -1)
        return true;
    if(p.t.at(2).at(0) == p.t.at(1).at(1) && p.t.at(1).at(1) == p.t.at(0).at(2) && p.t.at(0).at(2) != -1)
        return true;
    return false;
}
