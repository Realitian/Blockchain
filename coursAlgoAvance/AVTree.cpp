#include <bits/stdc++.h>
#include <memory>
/**
*   Classe représentant un AVL Tree
**/
namespace Tree
{
/// Classe représentant un noeud
template<typename T>
class Node
{
	using NodePtr = std::shared_ptr<Node<T>>;
public:
    // Constructeur par défaut
    Node():
        m_height (1),
        m_left(nullptr),
        m_right(nullptr)
    {
    }
public:
    // Getter constant et normaux + setter
    inline const T key() const
    {
        return this->m_key;
    }
    inline const NodePtr left() const
    {
        return this->m_left;
    }
    inline const NodePtr right() const
    {
        return this->m_right;
    }
    inline T key() 
    {
        return this->m_key;
    }
    NodePtr left() 
    {
        return this->m_left;
    }
    NodePtr right() 
    {
        return this->m_right ;
    }
    inline int height() 
    {
        return this->m_height;
    }
    inline void setKey(const T& key)
    {
        this->m_key=key;
    }
    inline void setLeft(const NodePtr& left)
    {
        this->m_left=left;
    }
    inline void setRight(const NodePtr &right)
    {
        this->m_right=right;
    }
    inline void setHeight(const int& height)
    {
        this->m_height=height;
    }
private:
    // Une clé
    T m_key;
    // Une hauteur
    int m_height;
    // Un fils gauche
    std::shared_ptr<Node> m_left;
    // Un fils droit
    std::shared_ptr<Node>m_right;

};



// Chercher si le noeud n'existe pas déja
template<typename T>
std::shared_ptr<Node<T> >chercher(T key,std::shared_ptr<Node<T> >root)
{
    if(root ==  nullptr )
        return nullptr;
    if(key > root->key())
        return chercher(key,root->right());
    else if(key < root->key())
        return chercher(key,root->left());
    else if (key == root->key())
        return root;

}



// Creer un nouveau noeud
template<typename T>
std::shared_ptr<Node<T> > creerNoeud(T& key)
{
    std::shared_ptr<Node<T> > noeud = std::make_shared<Node<T> >();
    noeud->setKey(key);
    //  std::cerr << "Noeud cree"<<std::endl;
    return noeud;
}
template<typename T>
T max(const T &a,const T &b)
{
    return (a > b) ?  a : b;
}

// Recuperer la hauteur de l'arbre
template<typename T>
int hauteur(std::shared_ptr<Node<T> >noeud)
{
    if(noeud == nullptr)
        return 0;
    return noeud->height();
}


// Recuperer la différence des hauteurs des deux fils
template<typename T>
int getBalance(std::shared_ptr<Node<T> >noeud)
{
    if(noeud == nullptr)
        return 0;
    return hauteur(noeud->left())-hauteur(noeud->right());
}


/// Faire une rotation a gauche
template<typename T>
std::shared_ptr<Node<T> >leftRotate(std::shared_ptr<Node<T> > node)
{

    std::shared_ptr<Node<T> >x= node->right();
    std::shared_ptr<Node<T> >y = x->left();

    // Effectue la rotation
    x->setLeft(node);
    node->setRight(y);

    // Update les hauteurs
    node->setHeight(max(hauteur(node->left()),hauteur(node->right()))+1);
    x->setHeight(max(hauteur(x->left()),hauteur(x->right()))+1);
//std::cerr << "Rotation a gauche";
    return x;
}


/// Faire une rotation a droite
template<typename T>
std::shared_ptr<Node<T> >rightRotate(std::shared_ptr<Node<T> >node)
{
    std::shared_ptr<Node<T> >x=node->left();
    std::shared_ptr<Node<T> >y= x->right();

    // Effectue la rotation
    x->setRight(node);
    node->setLeft(y);

    node->setHeight(max(hauteur(node->left()),hauteur(node->right()))+1);
    x->setHeight(max(hauteur(x->left()),hauteur(x->right()))+1);
   // std::cerr << "Rotation a droite"<<std::endl;
    return x;
}

/// Ajouter un noeud a l'arbre
template<typename T>
std::shared_ptr<Node<T> >  insererNoeudUtil(T key, std::shared_ptr<Node<T> >root)
{

    int balance;
    // Arbre vide
    if(root == nullptr)
        return creerNoeud(key);
    // Ajouter a droite
    if(root->key() < key)
        root->setRight(insererNoeudUtil(key,root->right()));
    // Ajouter a gauche
    else
        root->setLeft(insererNoeudUtil(key,root->left()));

    // Mettre a jour la hauteurr
    root->setHeight(max(hauteur(root->right()),hauteur(root->left()))+1);

    // Difference de taille entre la gauche et la droite
    balance = getBalance(root);
   // std::cerr << balance<< std::endl;
    // Rotation de l'arbre
    if(balance > 1 && key > root->left()->key())
    {
        root->setLeft(leftRotate(root->left()));
        return rightRotate(root);
    }
    else if(balance < -1 && key > root->right()->key())
        return leftRotate(root);
    else if(balance > 1 && key < root->left()->key())
        return rightRotate(root);
    else if(balance <-1 && key < root->right()->key())
    {
        root->setRight(rightRotate(root->right()));
        return leftRotate(root);
    }

    // Si aucune rotation a éfféctuer
    return root;
}

/// Fonction qui vérifie si le noeud n'existe pas déja
template<typename T>
std::shared_ptr<Node<T> > insererNoeud(const T& key,std::shared_ptr<Node<T> >& root)
{

    if(chercher(key,root) == nullptr)
        return insererNoeudUtil(key,root);
    else
        return root;
}


/// Affiche le parcours en largeur de l'arbre
template<typename T>
void BFS(std::shared_ptr<Node<T> >root)
{
    std::queue< std::pair<int,std::shared_ptr<Node<T> >> > q;
    q.push(std::pair<int,std::shared_ptr<Node<T> >  >(1,root));
    int level=0;
    while(!q.empty())
    {
        auto u=q.front();
        q.pop();
        if(level!= u.first)
        {
            level++;
            std::cout << std::endl << "Level "<<u.first<<" : ";
        }
        std::cout<<" "<<u.second->key();
        if(u.second->left() != nullptr) q.push(std::make_pair(u.first+1,u.second->left()));
        if(u.second->right() != nullptr) q.push(std::make_pair(u.first+1,u.second->right()));

    }
    std::cout << std::endl << std::endl;
}

/// Affiche le parcours en profondeur de l'arbre
template<typename T>
void DFS(std::shared_ptr<Node<T> >root)
{
    if(root == nullptr)
        return;
    std::cout << root->key() << " ";
    DFS(root->left());
    DFS(root->right());
    return;
}

}
int main()
{
    using namespace Tree;

    uint32_t N;
    std::shared_ptr<Node<int> > root=nullptr;
    srand(time(NULL));
    std::cout << "Nombre de valeurs a ajouter a l'arbre ";
    std::cin >> N;
    for(int i=0; i<N; i++)
    {
        root = insererNoeud(rand() % 10000000,root);
    }
    // root = insererNoeud(a,root);
    // root = insererNoeud(b,root);
    // root = insererNoeud(c,root);
    // root = insererNoeud(d,root);

    //  root = insererNoeud(15,root);
    //  root = insererNoeud("aab",root);
    //  root = insererNoeud("abc",root);
    //  root = insererNoeud("baa",root);

    // Parcours en profondeur
    std::cout<< std::endl<<"Parcours en profondeur:"<<std::endl;
  //  DFS(root);

    // Parcours en largeur
    std::cout<< std::endl<<"Parcours en largeur:"<<std::endl;
 //   BFS(root);


    // Resultats coupe:
    std::cout << "Si je coupe sur l'arc a gauche de la racine,\n on a taille arbre gauche : " << root->left()->height() << " et la taille arbre droit : " << root->right()->height() + 1 /* pour la racine */ ;
    return 0;
}
