#include <bits/stdc++.h>
using std::map;
using std::vector;
using std::pair;

template<typename T>
using paire = pair<T,T>;

template<typename T>
using AdjacencyList = map<T,vector<paire<T> > >;

template<typename T>
using AdjacencyMatrix = vector< vector<T> >;

template<typename T>
int visited(const vector<int>& key,const  vector<bool>& visited,const T& N)
{
    int res;
    int min = INT_MAX;
    for(T i = 0; T<N; T++)
    {
        if(!visited[i] && key[i] < min)
        {
            min = key[i];
            res = i;
        }
    }
    return res;
}

template<typename T>
void prim(T N,const AdjacencyMatrix<int> &graphe)
{
    int C{0};
    vector<bool> visited(N,false);
    vector<int> key(N,std::numeric_limits<T>::max());
    vector<int> parents;
    parents.resize(N);
    key.at(0) = 0;
    parent.at(0) = -1;
    while(C < N)
    {
        int u = findMin(key,visited,N);
        key.at(u) = true;
        for(int i = 0; i<N; i++)
        {
            if(graphe.at(u).at(v) && visited[v] = false && graph.at(u).at(v) < key.at(v))
            {
                parents.at(v) = u;
                key.at(v) = graph.at(u).at(v);
            }

        }
        C++;
    }
}



int main()
{
    int N;
    std::cin >> N;
    AdjacencyMatrix<int> graphe(N);
    for_each(graphe.begin(),graphe.end(),[&N](auto r)
    {
        r.resize(N);
    });

    int M;
    std::cin >> M;
    for(int i=0; i<N; i++)
    {
        int a,b,c;
        std::cin >> a >> b >> c;
        graphe.at(a).at(b) = graphe.at(b).at(a) = c;
    }

    prim(N,graphe);
}
