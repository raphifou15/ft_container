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
    Node(void) : data(), parent(NULL), left(NULL), right(NULL), color(BLACK) {}
    // faire un constructeur normale avec des bonnes valeurs
    Node(T const & va, Node *parent = NULL, Node *left = NULL, Node *right = NULL, int color = RED) : data(va), parent(parent), left(left), right(right), color(color) {}
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
    destroyAllElements(this->_nodeRoot);
    this->_alloc.destroy(this->_nodeEnd);
    this->_alloc.deallocate(this->_nodeEnd, 1);
  };

  void  destroyAllElements(Node *lala)
  {
    if (lala->left != this->_nodeEnd)
      destroyAllElements(lala->left);
    if (lala->right != this->_nodeEnd)
      destroyAllElements(lala->right);
    if (lala != this->_nodeEnd)
    {
      this->_alloc.destroy(lala);
      this->_alloc.deallocate(lala, 1);
    }
  }

  // getter
  Node *  getRoot(void) const {return this->_nodeRoot;}

  //


///////////////////////////////////////////////////////////////////////
  void  insert(const value_type &x)
  {
    Node *lala = this->_alloc.allocate(1);
    this->_alloc.construct(lala, Node(x, this->_nodeEnd, this->_nodeEnd, this->_nodeEnd, BLACK));
    if (this->_nodeRoot == this->_nodeEnd)
      this->_nodeRoot = lala;
    else
    {
      lala->color = RED;
      insert2(x, lala);
    }
  }

  void  insert2(const value_type &x, Node *lala)
  {
    Node *begin = this->_nodeRoot;
    while (1)
    {
      if (this->_cmp(x, begin->data))
      {
        if (begin->left != this->_nodeEnd)
          begin = begin->left;
        else
        {
          begin->left = lala;
          lala->parent = begin;
          if (begin->color == BLACK)
            return ;
          else
          {
            checkColorOncle(begin, begin->left);
          }
          return ;
        }
      }
      else
      {
        if (begin->right != this->_nodeEnd)
          begin = begin->right;
        else
        {
          begin->right = lala;
          lala->parent = begin;
          if (begin->color == BLACK)
            return ;
          else
          {
            checkColorOncle(begin, begin->right);
          }
          return ;
        }
      }
    }
  }


  void  checkColorOncle(Node *begin, Node *child)
  {
    if (begin->parent->left == begin)
    {
      if (begin->parent->right == this->_nodeEnd)
      {
        rotationBalance(child)
        return ;
      }
      if (begin->parent->right->color == RED)
      {
        begin->color = BLACK;
        begin->parent->right->color = BLACK;
        if (begin->parent->parent != this->_nodeRoot)
          begin->parent->parent->color = (begin->parent->parent->color == RED) ? BLACK : RED;
      }
      else
      {
        
      }
    }
    else
    {
      if (begin->parent->left == this->_nodeEnd)
      {
        rotationBalance(child);
        return ;
      }
      if (begin->parent->left->color == RED)
      {
        begin->color = BLACK;
        begin->parent->left->color = BLACK;
        if (begin->parent->parent != this->_nodeRoot)
          begin->parent->parent->color = (begin->parent->parent->color == RED) ? BLACK : RED;
      }
      else
      {

      }
    }
  }

  void  rotationBalance(Node *child)
  {
    if (this->_cmp(child->parent->data, child->data))
    {
      if (this->_cmp(child->parent->data, child->parent->parent->data))
      {
        //child->parent->right = this->_nodeEnd;
        //child->parent = child->parent->parent;
      }
    }
  }


  void  displayAllNode(Node *node)
  {
    if (node->left != this->_nodeEnd)
      displayAllNode(node->left);
    if (node != this->_nodeEnd)
    {
      std::cout << "clef = " << node->data.first << std::endl;
      std::cout << "value = " << node->data.second << std::endl;
      std::cout << "parent = "<< node->parent << std::endl;
      std::cout << "left = "<< node->left << std::endl;
      std::cout << "right = "<< node->right << std::endl;
      std::cout << "color = "<< node->color << std::endl;
      std::cout << "///////////////" << std::endl;
    }
    if (node->right != this->_nodeEnd)
      displayAllNode(node->right);
  }

////////////////////////////////////////////////////////////////////////////

};
}
#endif