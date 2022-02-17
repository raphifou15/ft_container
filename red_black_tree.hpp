#ifndef RED_BLACK_TREE
# define RED_BLACK_TREE

# define BLACK 0
# define RED   1

# include <memory>
# include <iostream>
# include <stdexcept>
# include <sstream>
# include "map.hpp"
# include "pair.hpp"

namespace ft
{

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
    Node(Node const &copie) : data(copie.data), parent(copie.parent), left(copie.left), right(copie.right), color(copie.color) {}
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

    /*std::ostream&   operator<<(std::ostream & ostream, Node const &i)
    {
      ostream << i.data;
      return (ostream);
    }*/
};

// trouver un moyen de faire passer la classe de comparaison.

template <class T, class Compare, class Node = Node<T>, class Allocator = std::allocator<Node> >
class RedBlackTree
{
  // mettre en place des typedef pour faciliter l'ecriture.
  typedef T                                   value_type; //cette value sera ma paire;
  typedef Compare                             value_compare; // cette value me permet d'utiliser les foncions de la classe compare
  typedef typename Allocator::reference       reference;
  typedef typename Allocator::const_reference const_reference;
  typedef typename Allocator::pointer         pointer;
  typedef typename Allocator::const_pointer   const_pointer;
  
  private:
    Allocator	_alloc;
    Node      *_nodeEnd;
    Node      *_nodeRoot;
    Compare   _cmp;
    //typename Allocator::size_type	_capacity;

  public:
  RedBlackTree(value_compare const &lala = value_compare()) : _cmp(lala) 
  {
    this->_nodeEnd = this->_alloc.allocate(1); // allocation d'un element de type Node;
    this->_alloc.construct(this->_nodeEnd, Node()); // creation d'un node vide;
    this->_nodeRoot = this->_nodeEnd; // le dernier element et le meme que le premier;
    //this->_capacity = 1;
  }
  ~RedBlackTree()
  {
    this->_alloc.destroy(this->_nodeEnd);
    this->_alloc.deallocate(this->_nodeEnd, 1);
  };

  // getter
  Node *  getRoot(void) const {return this->_nodeRoot;}

  //

  void  displayAllNode(Node *node)
  {
    if (node != NULL)
    {
      std::cout << node->data.first << std::endl;
      std::cout << node->data.second << std::endl;
      std::cout << node->parent << std::endl;
      std::cout << node->left << std::endl;
      std::cout << node->right << std::endl;
      std::cout << node->color << std::endl;
    }
    if (node->left)
     return  displayAllNode(node->left);
    if (node->right)
     return  displayAllNode(node->right);
  }
};
}
#endif