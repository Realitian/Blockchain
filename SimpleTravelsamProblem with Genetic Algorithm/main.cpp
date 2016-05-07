#include <iostream> // cout
#include <random> // random_generator
#include <functional> // bind
#include <algorithm> // generate, bind, sort,for_each, partial_sort
#include <vector>   // vector
#include <fstream> // ofstream
#include <thread> // thread
#include <future> // future
#include <chrono> // time_point,high_resolution...
//#include "json.h"

#define MAX_X 200 // taille max en X de la Map de coordonnées pour le voyageur de commmerce
#define MAX_Y 200   // ...en Y
#define TAILLE_GENOME 20 // nombre de villes

class City;
// vecteur de villes
std::vector<City> villes;

// FLUX DE RESULTAT
#define RES_FILE "res.txt"
std::ofstream out(RES_FILE,std::ofstream::out);

// Generateur d'aléatoire
std::random_device rd;
std::mt19937 gen(rd());



//------------------------------------- Classe City ----------------------------------------------------/
class City
{
char NOM = 'A';
public:
    City(int X,int Y,char nom) : X_(X),Y_(Y), nom_(nom){};
  //  City() : X_(rand() % MAX_X), Y_(rand() % MAX_Y) nom_((NOM++) % 90 + 65){};
    City& operator=(const City& rhs) { if(&rhs == this) return *this; X_= rhs.X() ; Y_ = rhs.Y(); nom_ = rhs.nom() ; return *this;};
    // destructeur
    virtual ~City() noexcept {};
    bool operator<(City rhs) const  { return (X_ <rhs.X() && Y_ <rhs.Y());};
    // Operateur de comparaison
    bool operator==(const City& other) const { return (X() == other.X() && Y() == other.Y() && nom_ == other.nom_);};
    // getter X
    inline int X() const { return X_;} ;
    // getter Y
    inline int Y() const { return Y_;} ;
    // obtenir le nom de la ville
    inline char nom() const { return nom_;} ;
    // flux de sortie
    friend std::ostream& operator<< (std::ostream& os, const City& rhs)
    {
       // os << " (" << rhs.X() << " " << rhs.Y() << ") ";
        os << rhs.nom() << " ";
        return os;
    };

    // distance entre deux villes
    double distance(City other) {return sqrt(pow(X()-other.X(),2) + pow(Y()-other.Y(),2));};
private:
    int X_,Y_;
    char nom_;
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
    bool operator<(Tour other) { return (this->fitness() > other.fitness());};

    // Affichage d'un tour
    friend std::ostream& operator<< (std::ostream& os, const Tour& rhs)
    {
        std::vector<City> cities = rhs.cities();
        for_each(cities.begin(),cities.end(), [&os](City b){ os << b; });
        return os;
    }

    // Get fitness
    inline double fitness()            { if(fitness_ == 0) return 1/distance(); return fitness_;};

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
            cities_.push_back(City(-1,-1,'-'));
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


    double distance()
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
        Met a jour la fitness de la population
        fitness(xi)  = (distance(xi) - (sum(distance(xi))/n)) / ( max(distance) - min(distance) )
    **/
    inline void setGlobalFitness()
    {
        double mini=std::numeric_limits<double>::max(),maxi=0,moy=0;
        for(int i=0;i<tours_.size();i++)
        {
            double fit_i = 1/tours_.at(i).distance();
            mini = std::min(mini,fit_i);
            maxi = std::max(maxi,fit_i);
            moy+= fit_i;
        }
        moy/=tours_.size();
        for(int i=0;i<tours_.size();i++)
        {
            tours_.at(i).setFitness(((1/tours_.at(i).distance()) - moy) / (maxi - mini));
        }
    }
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
    double max_score;
    double min_score;
    double moyenne_score;

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
#define PROB_MUTATION 100      // correspond a 1/15 que ca mute
#define NBREGENOME 200         // nombre de genome
#define NOMBRE_GENERATION 100 // nombre de génération

#define RAND_FLOAT static_cast<float>(static_cast <float> (1) / static_cast <float> (rand() % PROB_MUTATION ))
    double mutationRate = 0.0001;
    constexpr bool elitism = true;
    double steadystateRate = 0.005;

    double lastDistance;
    int hasnChange = 0;
    int compteurIncreaseMutation = 0;


    void setLastDistance(double t)
    {
        lastDistance = t;
    }

    void setHas_n_Change(int value)
    {
        (value == -1) ? hasnChange++ : hasnChange = 0;
    }

    void check_no_modif_and_mutate()
    {
        if(hasnChange > 30 && compteurIncreaseMutation == 0)
        {
            std::cerr << "Debut de la mutation intense" << std::endl;
            compteurIncreaseMutation = 30;
        }
        if(compteurIncreaseMutation > 1)
        {

            compteurIncreaseMutation--;
            mutationRate+= 0.3;
            steadystateRate = 0;
        }
        if(compteurIncreaseMutation == 1)
        {
            std::cerr << " Fin de la mutation intense" << std::endl;
            compteurIncreaseMutation--;
            mutationRate-=0.3;
            steadystateRate = 0.05;
        }
    }


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
        std::uniform_int_distribution<int> dist(0, std::max(static_cast<int>(score),1));
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

    // doublement de la méilleure population, et suppression de la mauvaise
    void steady_state(Population& pop)
    {
        std::vector<Tour> buff;
        buff.resize(pop.tours_.size()/2);
        std::partial_sort_copy (pop.tours_.begin(), pop.tours_.begin()+pop.tours_.size()/2, buff.begin(), buff.end());
        std::copy(buff.begin(),buff.end(), pop.tours_.begin() + pop.tours_.size()/2);
    }

    // Selection d'un génome en tirant aléatoirement
    Tour selectionMeilleureAleatoire(const Population& pop)
    {
      //  debug("Debut de Selection");
        Tour bestTour;
        std::uniform_int_distribution<int> dist(0, std::max(pop.size()-1,1));
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
        // initialise le nouveau génome
        for(int i=0;i<taille;i++)
        {
            City buff(-1,-1,'-');
            child.setCity(i,buff);
        }

        std::uniform_int_distribution<int> dist(0, std::max(a.size()-1,1));
        std::function<int()> f =std::bind(dist, std::ref(gen));
        int st = f();
        int ed = f();
        // st et ed sont des indices
        // si st < ed je prend dans le génome 1 les villes entre [st,ed]
        // si ed > st je prend dans le génome 1 les villes en dehors de [st,ed]
        for(int i=0;i<taille;i++)
        {
           if (st <= ed && i >= st && i <= ed) {
                 child.setCity(i, a.getCity(i));
           }
           else if (st > ed) {
                if (!(i <= st && i >= ed)) {
                    child.setCity(i, a.getCity(i));
                }
            }
        }
        // J'effectue une copie pour simplifier l'ecriture (pour que ligne 345 soit plus courte a comprendre
        std::vector<City> ville = child.cities();
        // Je complète le nouveau génome, avec les villes qui sont dans le deuxième génome b
        // et qui n'étaient pas dans l'intervalle [st,ed] (si st<ed) ou * \ [st,ed] (si st > ed)
        for(int i=0 ; i < b.size();i++)
        {
            // Si la ville de b n'est pas dans le chromosome final
            if(std::find(ville.begin(),ville.end(),b.getCity(i)) == ville.end())
            {
                // recherche de la première position vide du nouvau chromosome
                for(int j=0;j<child.size();j++)
                {
                    if(child.cities().at(j).X() == -1 && child.cities().at(j).Y() == -1)
                    {
                        // Je met la ville indice i de b dans le chromosome final
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
        pop.setGlobalFitness();
        pop.trier();
        Population newPop(pop.size(),false);
        // Steady - State
        if(RAND_FLOAT < steadystateRate)
            steady_state(pop);
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


        if(lastDistance == newPop.getFittest().distance())
            setHas_n_Change(-1);
        else
            setHas_n_Change(0);
        check_no_modif_and_mutate();
        setLastDistance(newPop.getFittest().distance());
        return newPop;
    }

    void hill_Climbing(Tour tour)
    {
        int generation = 0;
        Tour other;
        while(generation < 100000)
        {
            other = mutate(tour);
            if(other.fitness() >= tour.fitness())
                tour = other;
            std::cerr << "Generation " << generation++ << " : " <<  tour.distance() <<std::endl;
        }
    }
};



namespace timer
{
#define MAX_TIME 10000000
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

    pop = evoluer(pop);
    for (int i = 0; i < NOMBRE_GENERATION; i++)
    {
        pop = evoluer(pop);
        std::cout << "Generation "<< i+1 << " fittest distance: " <<  pop.getFittest().distance()<< std::endl;
    }

    std::cout << "ORDRE VILLE FINALE" << std::endl;
    std::vector<City> finale = pop.getFittest().cities();
    for_each(finale.begin(),finale.end(),[](City x){
        std::cout << x.nom() << " ";
    });
    std::cout << std::endl;
    return pop.getFittest().distance();
}





int main()
{
    srand(time(NULL));
    villes.push_back(City(60,200,'A'));
    villes.push_back(City(180,200,'B'));
    villes.push_back(City(80,180,'C'));
    villes.push_back(City(140,180,'D'));
    villes.push_back(City(20,160,'E'));
    villes.push_back(City(100,160,'F'));
    villes.push_back(City(200,160,'G'));
    villes.push_back(City(140,140,'H'));
    villes.push_back(City(40,120,'I'));
    villes.push_back(City(100,120,'J'));
    villes.push_back(City(180,100,'K'));
    villes.push_back(City(60,80,'L'));
    villes.push_back(City(120,80,'M'));
    villes.push_back(City(180,60,'N'));
    villes.push_back(City(20,40,'O'));
    villes.push_back(City(100,40,'P'));
    villes.push_back(City(200,40,'Q'));
    villes.push_back(City(20,20,'R'));
    villes.push_back(City(60,20,'S'));
    villes.push_back(City(160,20,'T'));

   // std::future<int> f1 = std::async(std::launch::async,lancer);
   // std::future<int> f2 = std::async(std::launch::async,lancer);
   // std::future<int> f3 = std::async(std::launch::async,lancer);
   // std::cout << f1.get(); //<< " " << f2.get() << " " << f3.get();
   lancer();

    return 0;
}

