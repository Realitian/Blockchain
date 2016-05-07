#include "Plateau.h"

Plateau::Plateau() :
    t(3,std::vector<int>(3,-1))
{

}

Plateau::~Plateau()
{
    //dtor
}

void Plateau::to_string()
{
    system("CLS");
    for(int i=0; i<3; i++)
    {
        std::cout << "------- ------- -------" << std::endl;
        for(int j=0; j<3; j++)
        {
            std::cout << "| " << ((t[i][j] == -1) ? "  " : std::string(" "+std::to_string(t[i][j]))) << "  | ";
        }
        std::cout << std::endl;
    }
    std::cout << "------- ------- -------" << std::endl;
}
bool Plateau::ajouterPion(Joueur *j,const int x,const int y)
{
    if(verifierPion(x,y) == false)
        return false;
  //  std::cout << x << y;
    t[x][y] = j->_CODE_;
    to_string();
    return true;
}
bool Plateau::verifierPion(int x,int y)
{
    if(verifierCoord(x,y) == false)
        return false;
    if(t[x][y] != -1)
        return false;
    return true;
}

bool Plateau::verifierCoord(int x,int y)
{
    if(x >=0 && x < 3 && y >=0 && y < 3)
        return true;
    else
        return false;
}
