#include "IAlphaBeta.h"
#define MAX_TIME 1'000'000'000

IAlphaBeta::IAlphaBeta(const int& code) :
    Joueur(code),
    l("output.out"),
    start()
{

}

IAlphaBeta::~IAlphaBeta()
{

}

/**
for(auto runUntil = std::chrono::system_clock::now() + std::chrono::seconds(5);
std::chrono::system_clock::now() < runUntil;)
{
// Do something
std::cout << "Hi !" << std::endl;
}
**/

PAIR IAlphaBeta::jouer(VII v)
{
    start = std::chrono::high_resolution_clock::now();
    std::vector<int> x = calculerBestMove(v,3,0,std::numeric_limits<int>::min(),std::numeric_limits<int>::max());
    auto fin = std::chrono::high_resolution_clock::now();
    l.write( std::to_string(std::chrono::duration_cast<std::chrono::nanoseconds>(fin - start).count()));
    return std::pair<int,int>(x[1],x[2]);
}


int IAlphaBeta::verifierVainqueur(VII v)
{
    if(v.at(0).at(0) == v.at(0).at(1) && v.at(0).at(1) == v.at(0).at(2) && v.at(0).at(1) != -1)
        return v.at(0).at(0);
    if(v.at(1).at(0) == v.at(1).at(1) && v.at(1).at(1) == v.at(1).at(2) && v.at(1).at(1) != -1)
        return v.at(1).at(0);
    if(v.at(2).at(0) == v.at(2).at(1) && v.at(2).at(1) == v.at(2).at(2) && v.at(2).at(1) != -1)
        return v.at(2).at(0);
    if(v.at(0).at(0) == v.at(1).at(0) && v.at(1).at(0) == v.at(2).at(0) && v.at(2).at(0) != -1)
        return v.at(0).at(0);
    if(v.at(0).at(1) == v.at(1).at(1) && v.at(1).at(1) == v.at(2).at(1) && v.at(2).at(1) != -1)
        return v.at(0).at(1);
    if(v.at(0).at(2) == v.at(1).at(2) && v.at(1).at(2) == v.at(2).at(2) && v.at(2).at(2) != -1)
        return v.at(0).at(2);
    if(v.at(0).at(0) == v.at(1).at(1) && v.at(1).at(1) == v.at(2).at(2) && v.at(0).at(0) != -1)
        return v.at(0).at(0);
    if(v.at(2).at(0) == v.at(1).at(1) && v.at(1).at(1) == v.at(0).at(2) && v.at(0).at(2) != -1)
        return v.at(2).at(0);
    return -1;
}

/*
Il est tant de quitter la récursion
*/
inline bool IAlphaBeta::getDiffTime()
{
    auto fin = std::chrono::high_resolution_clock::now();
    if(std::chrono::duration_cast<std::chrono::nanoseconds>(fin - start).count() > 0.65 * MAX_TIME)
    {
        return true;
    }
    return false;
}

std::vector<int> IAlphaBeta::calculerBestMove(VII &vec,const int depth,int code,int alpha,int beta)
{
    int currScore = 0;
    int bR = -1;
    int bC = -1;
    VIII possibleMove = movePossible(vec);
    if(possibleMove.empty() || depth == 0)
    {
        currScore = evaluer(vec,depth);
        std::vector<int> res = {currScore,bR,bC};
        return res;
    }
    else if(getDiffTime() == true)
    {
        l.write("Temps maximum atteint");
        std::vector<int> res = {currScore,possibleMove[0].first,possibleMove[0].second};
        return res;
    }
    else
    {
        for(auto p : possibleMove)
        {
            vec[p.first][p.second] = code;
            if(code == 0)
            {
                currScore = calculerBestMove(vec,depth-1,1,alpha,beta)[0];
                if(currScore > alpha)
                {
                    alpha = currScore;
                    bR = p.first;
                    bC = p.second;
                }
            }
            else if(code == 1)
            {
                currScore = calculerBestMove(vec,depth-1,0,alpha,beta)[0];
                if(currScore < beta)
                {
                    beta = currScore;
                    bR = p.first;
                    bC = p.second;
                }
            }
            vec[p.first][p.second] = -1;
            if(alpha >= beta)
                break;
        }
    }
    std::vector<int> res = {((code == 0)? alpha : beta ), bR,bC};
    return res;
}

int evaluateLine(const VII cell,int row1, int col1, int row2, int col2, int row3, int col3);

int IAlphaBeta::evaluer(const VII vec,int depth)
{
    depth++;
    // Evaluate score for each of the 8 lines (3 rows, 3 columns, 2 diagonals)
    if(verifierVainqueur(vec) == 0)
        return depth*1000;
    else if(verifierVainqueur(vec) == 1)
        return -depth*1000;
    return 0;
}

VIII IAlphaBeta::movePossible(const VII vec)
{
    VIII v;
    if(verifierVainqueur(vec) != -1)
    {
        return v;
    }
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            if(vec[i][j] == -1)
                v.push_back(std::pair<int,int>(i,j));
        }
    }
    return v;
}


