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
        bool     color;  // couleur du noeud

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
    if (lala->left != NULL && lala->left != this->_nodeEnd)
      destroyAllElements(lala->left);
    if (lala->right != NULL && lala->right != this->_nodeEnd)
      destroyAllElements(lala->right);
    if (lala != this->_nodeEnd)
    {
      this->_alloc.destroy(lala);
      this->_alloc.deallocate(lala, 1);
    }
  }

  // getter
  Node  * getRoot(void) const {return this->_nodeRoot;}
  Node  * get_begin(void) const
  {
    //Node *  node = this->_nodeRoot;
    if (this->_nodeRoot == this->_nodeEnd)
      return (this->_nodeRoot);
  }

/////////////////////////////////////////////////////////////////////// debut de l'insertion red black three ///////////////////////
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
            redRedProblem(begin, begin->left); // si le parent est rouge
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
            redRedProblem(begin, begin->right); // si le parent est rouge
          }
          return ;
        }
      }
    }
  }


  void  redRedProblem(Node *p, Node *c) // p = parent c = child
  {
    (void)c;
    Node *gP = p->parent;

    if (p == gP->left) // le noeud du parrent est celui de gauche du grand pere
    {
      if (gP->right == this->_nodeEnd) //// il faudra faire une rotation et recolorer
      {
        if (this->_cmp(p->data, c->data))
        {
          c = leftRightRotation(c, p, gP);
          p = leftLeftRotation(c, c->parent, c->parent->parent);
        }
        else
          p = leftLeftRotation(c, c->parent, c->parent->parent);
        return;
      }
      if (gP->right->color == BLACK)  //// il faudra faire une rotation et recolorer
      {
        if (this->_cmp(p->data, c->data))
        {
          c = leftRightRotation(c, p, gP);
          p = leftLeftRotation(c, c->parent, c->parent->parent);
        }
        else
          p = leftLeftRotation(c, c->parent, c->parent->parent);
        return;
      }
        
      if (gP->right->color == RED)
      {
        p->color = BLACK;
        gP->right->color = BLACK;
        if(gP != this->_nodeRoot)
        {
          (gP->color == RED) ? gP->color = BLACK : gP->color = RED;
        }
        int i = 1;
        while(i == 1)
        {
          Node *lala = NULL;
          i = 0;
          checkRedRedProblem(this->_nodeRoot, &i, &lala);
          if (lala != NULL)
          {
            redRedProblem(lala->parent, lala);
          }
        }
        return ;
      }
    }
    else // le noeud du parrent est celui de droite du grand pere
    {
      if (gP->left == this->_nodeEnd) //// il faudra faire une rotation et recolorer
      {
        if (this->_cmp(c->data, p->data))
        {
          c = RightLeftRotation(c, p, gP);
          p = RightRightRotation(c, c->parent, c->parent->parent);
        }
        else
          p = RightRightRotation(c, c->parent, c->parent->parent);
        return;
      }
      if (gP->left->color == BLACK)  //// il faudra faire une rotation et recolorer
      {
        if (this->_cmp(c->data, p->data))
        {
          c = RightLeftRotation(c, p, gP);
          p = RightRightRotation(c, c->parent, c->parent->parent);
        }
        else
        {
          p = RightRightRotation(c, c->parent, c->parent->parent);
        }
        return;
      }
      if (gP->left->color == RED)
      {
        p->color = BLACK;
        gP->left->color = BLACK;
        if(gP != this->_nodeRoot)
        {
          (gP->color == RED) ? gP->color = BLACK : gP->color = RED;
        }
        int i = 1;
        while(i == 1)
        {
          Node *lala = NULL;
          i = 0;
          checkRedRedProblem(this->_nodeRoot, &i, &lala);
          if (lala != NULL)
          {
            std::cout << lala->parent->data.first << std::endl;
            std::cout << lala->data.first << std::endl;
            redRedProblem(lala->parent, lala);
          }
        }
        return ;
      }
    }
  }

  void checkRedRedProblem(Node *node, int *i, Node **lala)
  {

    if (node != this->_nodeEnd)
    {
      if (node->color == 1 && node->parent->color == 1)
      {
          *i = 1;
          *lala = node;
          return ;
      }
    }
    if (node->left != this->_nodeEnd)
      checkRedRedProblem(node->left, i, lala);
    if (node->right != this->_nodeEnd)
      checkRedRedProblem(node->right, i, lala);
    return ;
  }

  Node *leftLeftRotation(Node *c, Node *p, Node *gP)
  {
    (void)c;
    Node *aGP = gP->parent;

    if (gP == this->_nodeRoot)
      this->_nodeRoot = p;
    (aGP->left == gP) ? aGP->left = p : aGP->right = p;
    if (p->right != this->_nodeEnd)
      p->right->parent = gP;
    gP->left = p->right;
    gP->parent = p;
    p->right = gP;
    p->parent = aGP;
    gP->color = (gP->color == RED) ? BLACK : RED;
    p->color = (p->color == RED) ? BLACK : RED; 
    return (p);
  }

  Node *RightRightRotation(Node *c, Node *p, Node *gP)
  {
    (void)c;
    Node *aGP = gP->parent;

    if (gP == this->_nodeRoot)
      this->_nodeRoot = p;
    (aGP->right == gP) ? aGP->right = p : aGP->left = p;
    gP->right = p->left;
    if (p->left != this->_nodeEnd)
      p->left->parent = gP;
    gP->parent = p;
    p->left = gP;
    p->parent = aGP;
    gP->color = (gP->color == RED) ? BLACK : RED;
    p->color = (p->color == RED) ? BLACK : RED; 
    return (p);
  }

  Node *leftRightRotation(Node *c, Node*p, Node*gP)
  {
    gP->left = c;
    p->parent = c;
    p->right = this->_nodeEnd;
    c->parent = gP;
    c->left = p;
    return (p);
  }

  Node  *RightLeftRotation(Node *c, Node *p, Node *gP)
  {
    gP->right = c;
    p->parent = c;
    p->left = this->_nodeEnd;
    c->parent = gP;
    c->right = p;
    return (p);
  }
//////////////////////////////////////////////////////////// fin de l'insertion red black three //////////////////////
/*
  void  checkColorOncle(Node *begin, Node *child)
  {
    if (begin->parent->left == begin)
    {
      if (begin->parent->right == this->_nodeEnd)
      {
        rotationBalance(child);
        return ;
      }
      if (begin->parent->right->color == RED)
      {
        std::cout << "lala2\n" << std::endl;
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
        {
          std::cout << "lala" << begin->parent->parent->color << std::endl;
          std::cout << begin->parent->data.first << std::endl;
          begin->parent->parent->color = (begin->parent->parent->color == RED) ? BLACK : RED;
          std::cout << "lala" << begin->parent->parent->color << std::endl;
        }
      }
      else
      {

      }
    }
  }

  void  rotationBalance(Node *child)
  {
    Node  *p = child->parent;
    Node  *gP = child->parent->parent;
    if (this->_cmp(p->data, child->data))
    {
      if (this->_cmp(p->data, gP->data))
      {
        child = leftRightRotation(child, p, gP);
        p = leftLeftRotation(child);
        p->color = BLACK;
        p->right->color = RED;
      }
    }
  }

  Node  *leftLeftRotation(Node *child)
  {
    Node *p = child->parent;
    Node *gP = child->parent->parent;
    Node *aGP = child->parent->parent->parent;

    (aGP->left == gP) ? aGP->left = p : aGP->right = p;
    p->parent = gP->parent;
    p->right = gP;
    gP->parent = p;
    gP->left = this->_nodeEnd;
    return (p);
  }

  Node *leftRightRotation(Node *child, Node *p, Node *gP)
  {
    gP->left = child;
    child->parent = gP;
    child->left = p;
    p->parent = child;
    p->right = this->_nodeEnd;
    return (p);
  }
*/
  void  displayAllNode(Node *node)
  {
    if (node->left != NULL && node->left != this->_nodeEnd)
      displayAllNode(node->left);
    if (node != this->_nodeEnd)
    {
      std::cout << "clef = " << node->data.first << std::endl;
      std::cout << "value = " << node->data.second << std::endl;
      std::cout << "mon noeud " << node << std::endl;
      std::cout << "parent = "<< node->parent << std::endl;
      std::cout << "left = "<< node->left << std::endl;
      std::cout << "right = "<< node->right << std::endl;
      std::cout << "color = "<< node->color << std::endl;
      std::cout << "///////////////" << std::endl;
    }
    if (node->right != NULL && node->right != this->_nodeEnd)
      displayAllNode(node->right);
  }
////////////////////////////////////////////////////////////////////////////
};
}
#endif