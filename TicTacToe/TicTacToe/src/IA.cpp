#include "IA.h"
#define MAX_TIME 1'000'000'000
#define COEFFICIENT 0.98

IA::IA(const int& code) :
    Joueur(code),
    l("output.out"),
    start()
{
}

IA::~IA()
{
    //dtor
}
/**
for(auto runUntil = std::chrono::system_clock::now() + std::chrono::seconds(5);
		std::chrono::system_clock::now() < runUntil;)
	{
		// Do something
		std::cout << "Hi !" << std::endl;
	}
**/

PAIR IA::jouer(VII v)
{
    start = std::chrono::high_resolution_clock::now();
    std::vector<int> x = calculerBestMove(v,9,0);
    auto fin = std::chrono::high_resolution_clock::now();
    l.write( std::to_string(std::chrono::duration_cast<std::chrono::nanoseconds>(fin - start).count()));
    return std::pair<int,int>(x[1],x[2]);
}

uint64_t getTime()
{

}

int verifierVainqueur(VII v)
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

inline bool IA::getDiffTime()
{
    auto fin = std::chrono::high_resolution_clock::now();
    if(std::chrono::duration_cast<std::chrono::nanoseconds>(fin - start).count() > COEFFICIENT * MAX_TIME)
    {
        return true;
    }
    return false;
}
std::vector<int> IA::calculerBestMove(VII &vec,const int depth,int code)
{
    int best = (code == 0 ?  std::numeric_limits<int>::min() : std::numeric_limits<int>::max());
    int currScore = 0;
    int bR = -1;
    int bC = -1;
    VIII possibleMove = movePossible(vec);
    if(possibleMove.empty() || depth == 0)
    {
        best = evaluer(vec,code,depth);
    }
    else if(getDiffTime() == true)
    {
        l.write("Temps maximum atteint");
        std::vector<int> res = {best,possibleMove[0].first,possibleMove[0].second};
        return res;
    }
    else
    {
        for(auto p : possibleMove)
        {
            vec[p.first][p.second] = code;
            if(code == 0)
            {
                currScore = calculerBestMove(vec,depth-1,1)[0];
                if(currScore >= best)
                {
                    best= currScore;
                    bR = p.first;
                    bC = p.second;
                }
            }
            else if(code == 1)
            {
                currScore = calculerBestMove(vec,depth-1,0)[0];
                if(currScore <= best)
                {
                    best = currScore;
                    bR = p.first;
                    bC = p.second;
                }
            }
            vec[p.first][p.second] = -1;
        }
    }
    std::vector<int> res = {best,bR,bC};
    return res;
}

int evaluateLine(const VII cell,int row1, int col1, int row2, int col2, int row3, int col3);

int IA::evaluer(const VII vec,int code,int depth)
{
    int score = 0;
    depth++;
    // Evaluate score for each of the 8 lines (3 rows, 3 columns, 2 diagonals)
    if(verifierVainqueur(vec) == 0)
        return depth*1000;
    else if(verifierVainqueur(vec) == 1)
        return -depth*1000;
    return 0;
}

VIII IA::movePossible(const VII vec)
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

