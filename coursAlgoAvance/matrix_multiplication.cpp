#include <array>
#include <limits>
#include <iostream>
int finalSolution;


///-------------------------------------------------------- Algorithme génétique --------------------------------------------------------------------------/




class Population
{
public:
	Population() :
	std::vector<int> villes;
	long double fitness;
	long double resultat;
}


void mutation(std::vector<int>& ville)
{

}

std::vector<int> crossover(const Population& pop)
{

}

Population evoluer(const Population& pop)
{

}




///-------------------------------------------------------- Algorithme classique de DP ----------------------------------------------------------------/


/*      Classic Matrix Multiplication                */

template <typename T,size_t SIZE>
T Matrix_Multiplication_DP(const std::array<T,SIZE>& tab)
{
    std::array<std::array<T, SIZE>, SIZE> DP;
    for(size_t i = 0 ; i < SIZE ; i++){
    	DP.at(i).fill(std::numeric_limits<T>::max());
    	DP.at(i).at(i) = std::max(0,std::numeric_limits<T>::min());
    }
    int L,i,j,z;
    for(L = 2 ; L < SIZE ; L++) 
    	for(i = 1; i < SIZE-L+1 ;i++)
    	{
    			j= i + L - 1;
    			for( z = i ; z < j ; z++)
    				DP.at(i).at(j) = std::min( DP.at(i).at(j) , DP.at(i).at(z) + DP.at(z+1).at(j) + tab.at(i-1)*tab.at(z)*tab.at(j));
    	}
	return  finalSolution = DP.at(1).at(SIZE-1);
}






///--------------------------------------------------------------- MAIN -------------------------------------------------------------------------------/

int main()
{
    std::array<int,9> array = {20,30,50,80,40,70,50,60,40};
    std::cout << Matrix_Multiplication_DP(array);
}
