#include <iostream> // cout
#include <random> // random_generator
#include <functional> // bind
#include <algorithm> // generate, bind, sort,for_each, partial_sort
#include <vector>   // vector
#include <fstream> // ofstream
#include <thread> // thread
#include <future> // future
#include <chrono> // time_point,high_resolution...
#include<unordered_map>
#include "../jsoncpp/dist/json/json.h"

#define MAX_X 200 // taille max en X de la Map de coordonnées pour le voyageur de commmerce
#define MAX_Y 200   // ...en Y
#define TAILLE_GENOME 20 // nombre de villes

class City;
// vecteur de villes
std::vector<City> villes;
std::map<std::pair<int,int>,int> city_to_int;

// FLUX DE RESULTAT
#define RES_FILE "res.txt"
std::ofstream out(RES_FILE,std::ofstream::out);

// Generateur d'aléatoire
std::random_device rd;
std::mt19937 gen(rd());



//------------------------------------- Classe City ----------------------------------------------------/
class City
{
public:
    City(int X,int Y) : X_(X),Y_(Y){};
    City() : X_(rand() % MAX_X), Y_(rand() % MAX_Y){};
    City& operator=(const City& rhs) { if(&rhs == this) return *this; X_= rhs.X() ; Y_ = rhs.Y(); return *this;};
    // destructeur
    virtual ~City() noexcept {};
    bool operator<(City rhs) const  { return (X_ <rhs.X() && Y_ <rhs.Y());};
    // Operateur de comparaison
    bool operator==(const City& other) const { return (X() == other.X() && Y() == other.Y());};
    // getter X
    inline int X() const { return X_;} ;
    // getter Y
    inline int Y() const { return Y_;} ;
    // flux de sortie
    friend std::ostream& operator<< (std::ostream& os, const City& rhs)
    {
        os << " (" << rhs.X() << " " << rhs.Y() << ") ";
        return os;
    };

    // distance entre deux villes
    double distance(City other) {return sqrt(pow(X()-other.X(),2) + pow(Y()-other.Y(),2));};
private:
    int X_,Y_;
};


//------------------------------------- Classe Tour ----------------------------------------------------/
class Tour
{
public:
    // Differents constructeur
    Tour() : fitness_(0),distance_(0),cities_() {};
    Tour(const std::vector<City>& vec): fitness_(0), distance_(0), cities_(vec){};
    Tour(const Tour& rhs) : fitness_(rhs.fitness_) , distance_(rhs.distance_), cities_(rhs.cities_) {};
    // Destructeur
    ~Tour() noexcept { cities_.clear(); };
    Tour& operator=(Tour rhs){
        if(&rhs == this)
            return *this;
        this->cities_.swap(rhs.cities_);
        this->fitness_=rhs.fitness_;
        this->distance_=rhs.distance_;
        return *this;
    };

    // Operateur d'égalité
    bool operator==(Tour other) const { return (cities() == other.cities()     );};

    // Comparer deux tour
    bool operator<(Tour other) { return (this->distance() < other.distance());};

    // Affichage d'un tour
    friend std::ostream& operator<< (std::ostream& os, const Tour& rhs)
    {
        std::vector<City> cities = rhs.cities();
        for_each(cities.begin(),cities.end(), [&os](City b){ os << b; });
        return os;
    }

    // Get fitness
    inline double fitness()            { if(fitness_ == 0) return 1000/distance(); return fitness_;};

    // Set Fitness
    inline void setFitness(double fit) { fitness_ = fit; };

    // Set City at pos
    inline void setCity(int pos,const City& city) { if(pos >= size()) ajouterVille(pos); cities_.at(pos) = city;};

    // Remplit le vecteur villes avec des valeurs par défaut
    // Utile car cities_ n'est pas remplit par défaut
    void ajouterVille(int pos)
    {
        cities_.clear();
        for(int i= 0;i<=pos;i++)
        {
            cities_.push_back(City(-1,-1));
        }
    }

    // get City à pos
    inline City  getCity(int pos)    const { return cities_.at(pos);};

    // Générer un Tour random
    inline void generateRadom()
    {
        cities_ = villes;
        std::random_shuffle(cities_.begin(),cities_.end());
    };


    double distance()           // V
    {
        if(distance_ == 0)
        {
            if(size() == 0)
                return 0;
            double dist = distance_;
            City city = cities_.at(0);
            std::for_each(cities_.begin()+1,cities_.end(),[&city,&dist](City x)
            {
                dist+=x.distance(city);
                city=x;
            });
            distance_ = dist;
        }
        return distance_;
    }

    // Obtenir la taille de cities_
    inline int size() const { return cities_.size();};

    // Obtenir le vecteur cities
    std::vector<City> cities() const { return cities_;};

    /**
    @city : vérifie si city est contenu dans City
    */
    bool containsCity(const City& city) const { auto res = std::find(cities_.begin(),cities_.end(),city); return (res != cities_.end());}

private:
    double fitness_;
    double distance_;
    std::vector<City> cities_;
};



/*------------------------------------- Classe Population ----------------------------------------------------*/
class Population
{
public:
    Population(int taille,bool initialize) :
        tours_()
    {
        tours_.resize(taille);
        if(initialize)
            for(int i = 0; i<taille; i++)
            {
                Tour tour;
                tour.generateRadom();
                setTour(i,tour);
            }
    };
    Population(const Population& rhs) : tours_(rhs.tours_) {};

    Population() = delete;
    ~Population() noexcept { tours_.clear();} ;

    // Tri les tours
    void trier() { std::sort(tours_.begin(),tours_.end()); };

    // Obtenir le nombre de tour
    inline Tour getTour(int pos)    const  { return tours_.at(pos);};
    // Obtenir le nombre de Tour
    inline void setTour(uint pos,const Tour& tour) { if(pos >= tours_.size()) ajouterTour(pos); tours_.at(pos)=tour;};
    // Ajouter des tours pour eviter l'erreur
    inline void ajouterTour(int pos)
    {
        tours_.clear();
        for(int i=0;i<=pos;i++)
        {
            tours_.push_back(Tour());
        }

    }
    // Obtenir le gène le meilleur
    inline Tour getFittest() { std::partial_sort(tours_.begin(),tours_.begin()+2,tours_.end()); return tours_.at(0);};
    // Obtenir le nombre de chromosomes
    inline int size() const { return tours_.size(); };
    std::vector<Tour> tours_;

    /**
    Affichage dans un fichier Json
    **/
    void JsonSave(const std::string& filename)
    {
    #define tost(a) std::to_string(a)
        std::ofstream out2(filename,std::ofstream::out);
        Json::Value jsonA(Json::objectValue);
        Json::Value jsonArray(Json::arrayValue);
        Json::Value jsonArray1(Json::arrayValue);
        std::sort(tours_.begin(),tours_.end());
        jsonA["fitness of the best"]= getFittest().fitness();
        for(uint j=0;j<tours_.size()/4;j++)
        {
            std::string buff = std::string("genome"+tost(j));
            std::string res;
            for(int i=0;i<tours_.at(j).size();i++)
            {
                City b = tours_.at(j).getCity(i);
              //  res+= std::string(" ("+tost(b.X())+" "+tost(b.Y())+") ");
                res+= std::string(" "+tost(city_to_int[std::make_pair(b.X(),b.Y())]));
            }
            jsonA[buff.c_str()]=res;
        }

        out2 << jsonA;
        out2.close();
    }

};
//------------------------------------- Namespace Debugger ----------------------------------------------------/
namespace debugger
{
    // Simplifie l'affichage du debug
    template<typename T>
    void debug(const T& l)
    {
        std::cout << l << std::endl;
    }
    template<typename T,typename ...R>
    void debug(const T& l,const R& ...res)
    {
        std::cout << l << " ";
        debug(res...);
    }

}

//------------------------------------- Namespace Genetic Algorithm Fonctions ----------------------------------------------------/
namespace GAWORK
{
#define PROB_MUTATION 115 // correspond a 1/15 que ca mute
#define NBREGENOME 50 // nombre de genome
#define NOMBRE_GENERATION 2000 // nombre de génération

#define RAND_FLOAT static_cast<float>(static_cast <float> (1) / static_cast <float> (rand() % PROB_MUTATION + 1))
    constexpr static double mutationRate = 0.2;
    constexpr bool elitism = true;

    bool checkValidiyTour(const Tour& t)
    {
        for(int i=0;i<t.size();i++)
        {
            if(std::find(villes.begin(),villes.end(),t.getCity(i)) == villes.end())
                return false;
        }
        return true;
    }

    // selection d'un génome par la méthode de la roulette
    Tour selectionRoulette(const Population& pop)
    {
        long double score = 0,score1=0,score2=0;
        for(int i=0;i<pop.size();i++)
        {
            score+= pop.getTour(i).fitness();
        }
        std::uniform_int_distribution<int> dist(1, std::max(static_cast<int>(score),1));
        std::function<int()> f =std::bind(dist, std::ref(gen));
        score1 = static_cast<double>(f());
        int i=0;
        while(score2 <= score1 && i < pop.size())
        {
            score2+= pop.getTour(i++).fitness();
        }
        Tour res =pop.getTour(std::min(i,pop.size()-1));

        return res;
    }


    // Selection d'un génome en tirant aléatoirement
    Tour selectionMeilleureAleatoire(const Population& pop)
    {
      //  debug("Debut de Selection");
        Tour bestTour;
        std::uniform_int_distribution<int> dist(1, std::max(pop.size()-1,1));
        std::function<int()> f =std::bind(dist, std::ref(gen));

        for(int i=0 ; i<pop.size() ; i++)
        {
            Tour tirer = pop.getTour(f());

            // bestTour est vide par défaut
            if(bestTour.distance() == 0) bestTour = tirer;

            // Prend le meilleur des deux tours
            bestTour = (bestTour < tirer ? bestTour : tirer);
            bestTour = tirer;
        }
        if(! checkValidiyTour(bestTour)){
            std::cout << "ALLLLLERT SELECTION FAILED";
            return pop.getTour(std::min(1,NBREGENOME));
        }
        return bestTour;
    }

    /**
    Effectue le crossover entre deux tours
    @a@b : tours qui vont etre mélanges
    */
    Tour crossover(const Tour& a,const Tour& b)
    {
        int taille = a.size();
        Tour child;

        for(int i=0;i<taille;i++)
        {
            City buff(-1,-1);
            child.setCity(i,buff);
        }

        std::uniform_int_distribution<int> dist(1, std::max(a.size()-1,1));
        std::function<int()> f =std::bind(dist, std::ref(gen));
        int st = f();
        int ed = f();
      //  st = std::min(st,ed);
      //  ed = std::max(st,ed);
        for(int i=0;i<taille;i++)
        {
           if (st < ed && i >= st && i <= ed) {
                 child.setCity(i, a.getCity(i));
           }
           else if (st > ed) {
                if (!(i <= st && i >= ed)) {
                    child.setCity(i, a.getCity(i));
                }
            }
        }
        // Pour moi on en a pas besoin a l'intérieur
        std::vector<City> ville = child.cities();
        for(int i=0 ; i < b.size();i++)
        {
            if(std::find(ville.begin(),ville.end(),b.getCity(i)) == ville.end())
            {
                for(int j=0;j<child.size();j++)
                {
                    if(child.cities().at(j).X() == -1 && child.cities().at(j).Y() == -1)
                    {
                        child.setCity(j,b.getCity(i));
                        break;
                    }
                }
            }
        }

        if(! checkValidiyTour(a) || !checkValidiyTour(b)){
            std::cout << "ALLLLLERT CROSSOVER FAILED";
            return a;
        }
        return child;
    }

    /**
    Effectuer la mutation d'un tour
    @tour : le tour
    */
    Tour mutate(const Tour& tour)
    {
        Tour newTour = tour;
        Tour init = tour;

        //   debug("Debut d'un mutate");
        for(int i=0;i<newTour.size();i++)
        {
            if(RAND_FLOAT < mutationRate)
            {
             std::uniform_int_distribution<int> dist(1, tour.size()-1);
             std::function<int()> f =std::bind(dist, std::ref(gen));
             int j = f();
             City city = newTour.getCity(i);
             City city2 = newTour.getCity(j);
             newTour.setCity(j,city);
             newTour.setCity(i,city2);
            }
        }
        // Si la mutation est mauvaise, alors retourne l'ancien chromosome
     //  if(newTour < init)
       //     newTour = init;
        if(! checkValidiyTour(newTour)){
            std::cout << "ALLLLLERT MUTATION FAILED";
            return tour;
        }
        return newTour;
    }

    /**
    Fonction qui consiste a faire évoluer une population
    @pop : la population a faire évoluer durant une génération
    **/
    Population evoluer(Population pop)
    {
       // pop.trier();
        Population newPop(pop.size(),false);
        // Copie du meilleure génome
        if(elitism ==  true)
            newPop.setTour(0,pop.getTour(0));
        for(int i= (elitism == true ? 1 : 0) ; i < newPop.size() ; i++)
        {
            Tour a,b;
             a = selectionRoulette(pop);
             b = selectionMeilleureAleatoire(pop);
            Tour child = crossover(a,b);
            newPop.setTour(i,child);
        }
        for (int i = (elitism == true ? 1 : 0); i < newPop.size(); i++) {
           newPop.setTour(i,mutate(newPop.getTour(i))) ;
        }
        return newPop;
    }


};



namespace timer
{
#define MAX_TIME 10'000'000
    typedef  std::chrono::high_resolution_clock::time_point timepoint;
    timepoint getStartedTime()
    {
        return std::chrono::high_resolution_clock::now();
    }
    bool is_stop(long long int diff,timepoint start,timepoint fin)
    {
       if(std::chrono::duration_cast<std::chrono::nanoseconds>(fin - start).count() > 0.65 * MAX_TIME)
       {
            return true;
       }
      return false;
    }
}


int lancer()
{
    using namespace GAWORK;
    Population pop(NBREGENOME,true);
  //  out << "Best Distance  : " << pop.getFittest().distance() << std::endl;
    pop = evoluer(pop);
    for (int i = 0; i < NOMBRE_GENERATION; i++)
    {
       // std::cout  << "TOUR NUMERO " << i+1<< std::endl;
        pop = evoluer(pop);
        std::cout << pop.getFittest().distance()<< std::endl;
    }
    pop.JsonSave("out.json");
    return pop.getFittest().distance();

}

int main()
{
    srand(time(NULL));
    for(int i=0 ; i<TAILLE_GENOME ; i++ )
    {
        City X;
       // std::cerr << "Nouvelle ville : pos X = " << X.X() <<" et pos Y = " << X.Y() << std::endl;
       // villes.push_back(X);
    }
    villes.push_back(City(60,200));
    villes.push_back(City(180,200));
    villes.push_back(City(80,180));
    villes.push_back(City(140,180));
    villes.push_back(City(20,160));
    villes.push_back(City(100,160));
    villes.push_back(City(200,160));
    villes.push_back(City(140,140));
    villes.push_back(City(40,120));
    villes.push_back(City(100,120));
    villes.push_back(City(180,100));
    villes.push_back(City(60,80));
    villes.push_back(City(120,80));
    villes.push_back(City(180,60));
    villes.push_back(City(20,40));
    villes.push_back(City(100,40));
    villes.push_back(City(200,40));
    villes.push_back(City(20,20));
    villes.push_back(City(60,20));
    villes.push_back(City(160,20));
    for(uint i=0;i<villes.size();i++)
    {
        city_to_int[std::make_pair(villes.at(i).X(),villes.at(i).Y())]=i;
    }
   // std::future<int> f1 = std::async(std::launch::async,lancer);
   // std::future<int> f2 = std::async(std::launch::async,lancer);
   // std::future<int> f3 = std::async(std::launch::async,lancer);
   // std::cout << f1.get(); //<< " " << f2.get() << " " << f3.get();
   lancer();
    return 0;
}
