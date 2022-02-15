#ifndef RED_BLACK_TREE
# define RED_BLACK_TREE

# define BLACK 0;
# define RED   1;

# include <memory>
# include <iostream>
# include <stdexcept>
# include <sstream>
# include "pair.hpp"



// code inspirer de la documentation https://www.programiz.com/dsa/red-black-tree
template <class T> // T = pair
class Node
{
    public:
        T       data;   // pair
        Node    *parent; // noeud parent
        Node    *left; // noeud droit
        Node    *right; // noeud gauche
        int     color;  // couleur du noeud

    // initialisation de node a 0
    // creer un truc qui vq me renvoyer NILL;
    Node() : data(), parent(NULL), left(NULL), right(NULL), color(BLACK) {}
    // faire un constructeur normale avec des bonnes valeurs
    Node(T const & va ) : data(va), parent(NULL), left(NULL), right(NULL), color(RED) {}
    // constructeur par copie pour effectuer les donnees
    Node(Node const &copie) : data(copie.va), parent(copie.parent), left(copie.left), right(copie.right), color(copie.color) {}
    // constructeur par assignation
    Node &operator=(const Node &lala)
    {
      this->data = lala.data;
      this->parent = lala.parent;
      this->left = lala.left;
      this->right = lala.right;
      this->color = lala.color;
      return (*this);
    }
    ~Node() {}
  // rajouter un bouleen pour savoir si un node est egale a un autre.
     bool operator==(const Node &lala)
     {
       return (this->data == lala.data);
     }
};

// trouver un moyen de faire passer la classe de comparaison.

template <class T, class Compare, class Node = Node<T>, class Allocator = std::allocator<Node>>
class RedBlackTree
{
  // mettre en place des typedef pour faciliter l'ecriture.
  typedef T                                   value_type; //cette value sera ma paire;
  typedef Compare                             key_compare; // cette value me permet d'utiliser les foncions de la classe compare
  typedef Node                                type_node; 
  typedef typename Allocator::reference       reference;
  typedef typename Allocator::const_reference const_reference;
  typedef typename Allocator::pointer         pointer;
  typedef typename Allocator::const_pointer   const_pointer;
  
};

#endif