#ifndef RED_BLACK_TREE
# define RED_BLACK_TREE

# define BLACK 0
# define RED   1

# include <memory>
# include <iostream>
# include <stdexcept>
# include <sstream>
# include "map.hpp"
# include "bidirectional_iterator.hpp"
# include "pair.hpp"
#include <fstream>

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
  typedef typename Allocator::size_type       size_type;
  
  private:
    size_type _capacity;
    Allocator	_alloc;
    Node      *_nodeEnd;
    Node      *_nodeRoot;
    Compare   _cmp;
    //typename Allocator::size_type	_capacity;

  public:
  RedBlackTree(value_compare const &lala = value_compare()) : _cmp(lala) 
  {
    this->_capacity = 0;
    this->_nodeEnd = this->_alloc.allocate(1); // allocation d'un element de type Node;
    this->_alloc.construct(this->_nodeEnd, Node()); // creation d'un node vide;
    this->_nodeRoot = this->_nodeEnd; // le dernier element et le meme que le premier;
  }
  ~RedBlackTree()
  {
    destroyAllElements(this->_nodeRoot);
    destroy_lastElement();
  };
  
  void  destroy_lastElement(void)
  {
    this->_alloc.destroy(this->_nodeEnd);
    this->_alloc.deallocate(this->_nodeEnd, 1);
  }

  void  destroyAllElements(Node *lala)
  {
    if (lala != NULL && lala != this->_nodeEnd && lala->left != NULL && lala->left != this->_nodeEnd)
      destroyAllElements(lala->left);
    if (lala != NULL && lala != this->_nodeEnd && lala->right != NULL && lala->right != this->_nodeEnd)
      destroyAllElements(lala->right);
    if (lala != this->_nodeEnd)
    {
      if (lala == this->_nodeRoot)
        this->_nodeRoot = this->_nodeEnd;
      this->_alloc.destroy(lala);
      this->_alloc.deallocate(lala, 1);
      this->_capacity -= 1;
    }
  }

  // getter

  size_type size(void) const {return this->_capacity;}
  size_type maxSize(void) const {return this->_alloc.max_size();}

  Node  * getRoot(void) const {return this->_nodeRoot;}
  Node  * get_endl_node(void) const { return this->_nodeEnd;}
  //
  Node  * get_begin(void) const
  {
    Node *  node = this->_nodeRoot;
    if (this->_nodeRoot == this->_nodeEnd)
      return (this->_nodeRoot);
    while (node->left != this->_nodeEnd)
      node = node->left;
    return (node);
  }

  
  Node  *find(T x) const
  {
    Node *node = this->_nodeRoot;
    
    if (node == this->_nodeEnd)
      return (node);
    while (node != this->_nodeEnd)
    {
      if (node->data.first == x.first)
        return (node);
      if (this->_cmp(x, node->data))
        node = node->left;
      else
        node = node->right;
    }
    return this->_nodeEnd;
  }


void  swap(RedBlackTree &lala)
{
  Node *tmp_root = this->_nodeRoot;
  Node *tmp_end = this->_nodeEnd;
  size_type tmp_c = this->_capacity;
  

  this->_nodeRoot = lala._nodeRoot;
  this->_nodeEnd = lala._nodeEnd;
  this->_capacity = lala._capacity;
  
  lala._nodeRoot = tmp_root;
  lala._nodeEnd = tmp_end;
  lala._capacity = tmp_c;
}


/////////////////////////////////////////////////////////////////////// debut de l'insertion red black three ///////////////////////

  void  insert(const value_type &x)
  {
    Node *lala = this->_alloc.allocate(1);
    this->_alloc.construct(lala, Node(x, this->_nodeEnd, this->_nodeEnd, this->_nodeEnd, BLACK));
    this->_capacity += 1;
    if (this->_nodeRoot == this->_nodeEnd)
    {
      this->_nodeRoot = lala;
      this->_nodeEnd->left = this->_nodeRoot;
    }
    else
    {
      lala->color = RED;
      insert_elem(lala);
      this->_nodeEnd->left = this->_nodeRoot;
    }
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////nouvel tentative d'insertion////////////////////////////////////



  void  insert_elem(Node *node)
  {
    Node  *pr = this->_nodeRoot;
    while (pr != this->_nodeEnd)
    {
      if (this->_cmp(node->data, pr->data))
      {
        if (pr->left == this->_nodeEnd)
        {
          pr->left = node;
          node->parent = pr;
          if (pr->color == RED) red_conflict(node);
          return ;
        }
        else
          pr = pr->left;
      }
      else if (this->_cmp(pr->data, node->data))
      {
        if (pr->right == this->_nodeEnd)
        {
          pr->right = node;
          node->parent = pr;
          if (pr->color == RED) red_conflict(node);
          return ;
        }
        pr = pr->right;
      }
    }
  }




  void  red_conflict(Node *c)
  {
    bool  red_problem = 1;
    while (red_problem)
    {
      Node *p = NULL; Node *pp = NULL; Node *pc = NULL;
      p = c->parent;
      if (p != this->_nodeEnd) pp = p->parent;
      if (pp != NULL && pp != this->_nodeEnd)
        pc = (pp->right == p) ? pp->left : pp->right;

      if((c->color == RED && p->color == BLACK) || c->color == BLACK)
        red_problem = 0;
      else if (c->color == RED && p->color == RED && pc->color == RED)
      {
        p->color = BLACK;
        pc->color = BLACK;
        pp->color = (this->_nodeRoot == pp)? BLACK : RED;
        c = pp;
      }
      else if (c->color == RED && p->color == RED && pc->color == BLACK)
      {
        if (pp->left == p)
        {
          if (p->right == c)
          {
            Node *cc = c->left;
            pp->left = c;
            p->parent = c;
            p->right = cc;
            c->parent = pp;
            c->left = p;
            if (cc != this->_nodeEnd) cc->parent = p;
            p = c;
            c = p->left;
          }
          Node *app = pp->parent;
          Node *cc = p->right;
          pp->parent = p;
          pp->left = cc;
          if (cc != this->_nodeEnd) cc->parent = pp;
          p->parent = app;
          p->right = pp;
          if (app == this->_nodeEnd)
            this->_nodeRoot = p;
          else
            (app->right == pp) ? app->right = p : app->left = p;
        }
        else
        {
          if (p->left == c)
          {
            Node *cc = c->right;
            pp->right = c;
            p->parent = c;
            p->left = cc;
            c->parent = pp;
            c->right = p;
            if (cc != this->_nodeEnd) cc->parent = p;
            p = c;
            c = p->right;
          }
          Node *app = pp->parent;
          Node *cc = p->left;
          pp->parent = p;
          pp->right = cc;
           if (cc != this->_nodeEnd) cc->parent = pp;
          p->parent = app;
          p->left = pp;

          if (app == this->_nodeEnd)
            this->_nodeRoot = p;
          else
            (app->left == pp) ? app->left = p : app->right = p;
        }
        pp->color = RED;
        p->color = BLACK;
        red_problem = 0;
      }
    }
  }




















  ////////////////////////////////////////////////////////////////////////////////////////// fin de la nouvelle tentative//////////////////////////////////////////////

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
    //std::cout << c->data.first << std::endl;
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
        gP->color = (gP == this->_nodeRoot) ? BLACK : RED;
        if (gP->color == RED)
        {
          if (gP->parent->color == RED)
            redRedProblem(gP->parent, gP);
        }
        return;
        /*
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
        */
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
          //std::cout << c->data.first << std::endl;
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
       //  std::cout << c->data.first << std::endl;
        p->color = BLACK;
        gP->left->color = BLACK;
        gP->color = (gP == this->_nodeRoot) ? BLACK : RED;
        if (gP->color == RED)
        {
          if (gP->parent->color == RED)
            redRedProblem(gP->parent, gP);
        }
        return;
        /*
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
            redRedProblem(lala->parent, lala);
          }
        }
        return ;
        */
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
    Node *cc = c->left;
    gP->left = c;
    p->parent = c;
    p->right = cc;
    c->parent = gP;
    c->left = p;
    (cc != this->_nodeEnd) ? cc->parent = p : 0;
    return (p);
  }

  Node  *RightLeftRotation(Node *c, Node *p, Node *gP)
  {
    Node *cc = c->right;
    gP->right = c;
    p->parent = c;
    p->left = cc;
    c->parent = gP;
    c->right = p;
    (cc != this->_nodeEnd) ? cc->parent = p : 0;
    return (p);
    /*
    Node *cc = c->right;

              pp->right = c;
              p->parent = c;
              p->left = this->_nodeEnd;
              p->right = cc;
              c->parent = pp;
              c->right = p;
              (cc != this->_nodeEnd) ? cc->parent = p : 0;
              p = pp->right;
              c = p->right;*/
  }



///////////////////////////////////////////////////////////deletion in red_black_tree //////////////////

  bool  erase(const value_type &x)
  {
    Node *node = this->_nodeRoot;
    if (node == this->_nodeEnd)
      return (0);
    while (node != this->_nodeEnd)
    {
      if (x.first == node->data.first)
      {   
        erase_element(node);
        this->_capacity -= 1;
        this->_nodeEnd->left = this->_nodeRoot;
        return (1);
      }
      if (this->_cmp(x, node->data))
        node = node->left;
      else
        node = node->right;
    }
    return (0);
  }

  void  erase_element(Node *node)
  {
    Node  *last = find_last(node);
    Node  *small = find_small(node);
    // std::cout << last->data.first << std::endl;
    // std::cout << small->data.first << std::endl;
    // std::cout << node->data.first << std::endl;
    if (last->color == RED)
    {
      if (node != last && node != small && small == last)
        last = transfert(node, small);
      else if (node != last && node != small && small != last)
      {
        small = transfert(node, small);
        last = transfert(small, last);
      }
      destroy_last_node(last);
    }
    else
    {
      if (node != last && node != small && small == last)
        last = transfert(node, last);
      black_black_conflict(last, 0);
    }
  }

  void  black_black_conflict(Node *dbp, int tr) // le parrent de l'element qui vient d'etre suprimmer;
  {
    bool  double_black = 1;
    while (double_black)
    {
      Node  *p = dbp->parent;
      Node  *cibling = NULL;

      if (p != this->_nodeEnd)
        cibling = (p->left == dbp) ? p->right : p->left;

      if (dbp == this->_nodeRoot)
      {
        if (tr == 0) destroy_last_node(dbp);
        if (tr == 0) this->_nodeRoot = this->_nodeEnd;
        if (tr == 0) this->_nodeEnd->left = this->_nodeRoot;
        double_black = 0;
      }
      else if(cibling != NULL && cibling->color == BLACK && cibling->left->color == BLACK && cibling->right->color == BLACK)
      {
        if (tr == 0) destroy_last_node(dbp);
        cibling->color = RED;
        if (p->color == RED)  
        {
          double_black = 0;
          p->color = BLACK;
        }
        else
          dbp = p;
      }
      else if (cibling != NULL && cibling->color == RED)
      {
        cibling->color = p->color;
        p->color = RED;
        //rotation in dbp direction
        if (p->left == dbp)//if (this->_cmp(dbp->data, p->data))
        {
          Node *cc = cibling->left;
          cibling->parent = p->parent;
          if(p->parent != this->_nodeEnd)
            (p->parent->left == p) ? p->parent->left = cibling : p->parent->right = cibling;
          cibling->left = p;
          p->parent = cibling;
          p->right = cc;
          if (cc != this->_nodeEnd)
            cc->parent = p;
          if (cibling->parent == this->_nodeEnd) this->_nodeRoot = cibling;
          if (cibling->parent == this->_nodeEnd) this->_nodeEnd->left = this->_nodeRoot;
          if (tr == 0) tr = -1 ;
        }
        else if (p->right == dbp)//else if (this->_cmp(p->data, dbp->data))
        {
          Node *cc = cibling->right;
          cibling->parent = p->parent;
          if(p->parent != this->_nodeEnd)
            (p->parent->left == p) ? p->parent->left = cibling : p->parent->right = cibling;
          cibling->right = p;
          p->parent = cibling;
          p->left = cc;
          if (cc != this->_nodeEnd)
            cc->parent = p;
          if (cibling->parent == this->_nodeEnd) this->_nodeRoot = cibling;
          if (cibling->parent == this->_nodeEnd) this->_nodeEnd->left = this->_nodeRoot;
          if (tr == 0) tr = -1 ;
        }
      }
      else if (cibling != NULL && cibling->color == BLACK && (cibling->left->color == RED || cibling->right->color == RED))
      {
        Node *far = find_far(cibling);
        Node *near = find_near(cibling);
        if (far->color == BLACK && near->color == RED)
        {
          near->color = BLACK;
          cibling->color = RED;
          if (cibling->parent->right == cibling)
          {
            Node  *child = cibling->left;
            Node  *cc = child->right;
            Node  *pa = cibling->parent;

            cibling->parent = child;
            cibling->left = cc;
            pa->right = child;
            child->parent = pa;
            child->right = cibling;
            if (cc != this->_nodeEnd) cc->parent = cibling;
          }
          else
          {
            Node  *child = cibling->right;
            Node  *cc = child->left;
            Node  *pa = cibling->parent;

            cibling->parent = child;
            cibling->right = cc;
            pa->left = child;
            child->parent = pa;
            child->left = cibling;
            if (cc != this->_nodeEnd) cc->parent = cibling;
          }
          cibling = (dbp->parent->left == dbp) ? dbp->parent->right : dbp->parent->left;
          far = find_far(cibling);
          near = find_near(cibling);
        }
        if (far->color == RED)
        {
          if (tr == 0) destroy_last_node(dbp);
          bool  tmp_color = p->color;
          p->color = cibling->color;
          cibling->color = tmp_color;
          if (p->right == cibling)
          {
            Node *app = p->parent;
            Node *cc = cibling->left;
            if (app != this->_nodeEnd)
              (app->right == p) ? app->right = cibling : app->left = cibling;
            cibling->parent = app;
            cibling->left = p;
            p->parent = cibling;
            p->right = cc;
            if (cc != this->_nodeEnd) cc->parent = p;
            if (app == this->_nodeEnd) this->_nodeRoot = cibling;
            if (app == this->_nodeEnd) this->_nodeEnd->left = this->_nodeRoot;
            far->color = BLACK;
            double_black = 0;
          }
          else
          {
            Node *app = p->parent;
            Node *cc = cibling->right;
            if (app != this->_nodeEnd)
              (app->left == p) ? app->left = cibling : app->right = cibling;
            cibling->parent = app;
            cibling->right = p;
            p->parent = cibling;
            p->left = cc;
            if (cc != this->_nodeEnd) cc->parent = p;
            if (app == this->_nodeEnd) this->_nodeRoot = cibling;
            if (app == this->_nodeEnd) this->_nodeEnd->left = this->_nodeRoot;
            far->color = BLACK;
            double_black = 0;
          }
        }
      }
      tr++;
    }
  }
  Node  *find_far(Node *cibling)
  {
    return (cibling->parent->right == cibling) ? cibling->right : cibling->left;
  }

  Node  *find_near(Node *cibling)
  {
    return (cibling->parent->right == cibling) ? cibling->left : cibling->right;
  }
  Node  *find_last(Node *node)
  {
    if (node->right != this->_nodeEnd)
      node = node->right;
    while (node->left != this->_nodeEnd)
      node = node->left;
    if (node->right != this->_nodeEnd)
      node = node->right;
    return (node);
  }

  Node  *find_small(Node *node)
  {
    if (node->right != this->_nodeEnd)
      node = node->right;
    while (node->left != this->_nodeEnd)
      node = node->left;
    return (node);
  }

  void  destroy_last_node(Node *node)
  {
    (node->parent->left == node) ? node->parent->left = this->_nodeEnd : node->parent->right = this->_nodeEnd;
    this->_alloc.destroy(node);
    this->_alloc.deallocate(node, 1);
  }

  Node  *transfert(Node *node1, Node *node2)
{
  Node *tmp = node1;
  Node  *r  = node2->right;
  Node  *l  = node2->left;
  Node  *p  = node2->parent;
  bool  color = node2->color;
  bool  rl;                                      ///// right = 1 left = 0;

  rl = (node2->parent->right == node2) ? 1 : 0;
  node1 = node2;
  
  node1->color = tmp->color;
  node1->parent = tmp->parent;
  if (node1->parent != this->_nodeEnd)
  {
    if (node1->parent->left == tmp)
      node1->parent->left = node1;
    else
      node1->parent->right = node1;
  }
  node1->right = (node1 != tmp->right) ? tmp->right : tmp;
  node1->left = (node1 != tmp->left) ? tmp->left : tmp;

  (node1->right != this->_nodeEnd) ? node1->right->parent = node1 : 0;
  (node1->left != this->_nodeEnd) ? node1->left->parent = node1 : 0;

  if (tmp == this->_nodeRoot)
    this->_nodeRoot = node1;

  tmp->parent = p;
  if (tmp == p)
    tmp->parent = node1;
  (rl == 1) ? tmp->parent->right = tmp : tmp->parent->left = tmp;

  tmp->right = r;
  (r != this->_nodeEnd) ? r->parent = tmp : 0;
  tmp->left = l;
  (l != this->_nodeEnd) ? l->parent = tmp : 0;
  tmp->color = color;
  return (tmp);
}

// bool  erase(const value_type &x)
// {
//     Node *node = this->_nodeRoot;

//     if (node == this->_nodeEnd)
//       return (0);

//     if (this->_capacity == 1 && this->_nodeRoot->data.first == x.first)
//     {
//       destroy_last_node(node);
//       this->_capacity -= 1;
//       this->_nodeRoot = this->_nodeEnd;
//       return 1;
//     }
    
//     while (node != this->_nodeEnd)
//     {
//       if (node->data.first == x.first)
//       {
//         erase2(node);
//         this->_capacity -= 1;
//         this->_nodeEnd->left = this->_nodeRoot;
//         return  1;
//       }
//       if (this->_cmp(x, node->data))
//         node = node->left;
//       else
//         node = node->right;
//     }
//     this->_nodeEnd->left = this->_nodeRoot;
   
//     return  0;
// }

// void  erase2(Node *node)
// {
//   // premier cas si le dernier noeud a effacer est rouge
//   // 1 regarder quel est le plus petit noeud en partant sur la droite;

//   Node  *tmp = node;
//   Node  *small = find_smallest_node_subtree_right(node);
//   Node  *last = find_last_elem_subtree_right(small);

//   //std::cout << tmp->data.first << std::endl;
//   //std::cout << small->data.first << std::endl;
//   //std::cout << last->data.first << std::endl;

  
//   if (last->color == RED)
//   {
//     if (last == small && last == tmp && small == tmp)
//     {
//       destroy_last_node(node);
//       return ;
//     }
//     if (tmp != last && tmp != small && small == last)
//     {
//       last = swap_internal_node_second(tmp, small);
//       destroy_last_node(last);
//       return ;
//     }
//     if (tmp != last && tmp != small && small != last)
//     {
//       small = swap_internal_node_second(tmp, small);
//       last = swap_internal_node_second(small, last);
//       destroy_last_node(last);
     
//       return ;
//     }
//   }
//   if (last->color == BLACK)
//   {
//     if (tmp != last && tmp != small && small == last)
//       last = swap_internal_node_second(tmp, last);
//     //std::cout << last->data.first << " raph" << std::endl;
//     db_black_problem(last, 0);
//     return ;
//   }
// }



// void  db_black_problem(Node *dbp, int x)
// {
//   if (dbp == this->_nodeRoot)
//     return ;
//   //std::cout << dbp->data.first << std::endl;
//   //std::cout << dbp->left << std::endl;
//   //std::cout << dbp->right << std::endl;
//   //std::cout << _nodeEnd << std::endl;
//   //std::cout << dbp->parent->data.first << " --------"<<std::endl;
//   Node  *p = dbp->parent;
//   Node  *cibling = (dbp->parent->left == dbp) ? dbp->parent->right : dbp->parent->left;
//   //std::cout << cibling->data.first << std::endl;
//   if (p->color == RED && cibling->color == BLACK && cibling->left->color == BLACK && cibling->right->color == BLACK)
//   {
//     if (x == 0)
//       destroy_last_node(dbp);
//     p->color = BLACK;
//     cibling->color = RED;
//     return ;
//   }
//   if (p->color == BLACK && cibling->color == BLACK && cibling->left->color == BLACK && cibling->right->color == BLACK)
//   {
//     if (x == 0)
//       destroy_last_node(dbp);
//     cibling->color = RED;
//     //std::cout << "limite" << std::endl;
//     db_black_problem(p, x + 1);
//     return ;
//   }
//   if (p->color == BLACK && cibling->color == RED)
//   {

//     if (p->right == cibling)
//     {
//       Node *cc = cibling->left;
//       //destroy_last_node(last);
//       p->color = RED;
//       cibling->color = BLACK;
//       cibling->parent = p->parent;
//       if (p != this->_nodeRoot)
//         (cibling->parent->left == p) ? cibling->parent->left = cibling : cibling->parent->right = cibling;
//       else
//         this->_nodeRoot = cibling;
//       p->right = cc;
//       cibling->left = p;
//       cc->parent = p;
//       p->parent = cibling;
//       /*
//       p->right = cc;
//       cc->parent = p;
//       cibling->parent = p->parent;
//       cibling->left = p;
//       p->parent = cibling;
//       (cibling->parent->left == p) ? cibling->parent->left = cibling : cibling->parent->right = cibling;*/
//       db_black_problem(p->left , x);
      
//       return ;
//     }

//     if (p->left == cibling)
//     {
       
//       Node *cc = cibling->right;
//       //destroy_last_node(last);
//       cibling->color = BLACK;
//       p->color = RED;
//       p->left = cc;
//       cc->parent = p;
//       cibling->parent = p->parent;
//       cibling->right = p;
//       p->parent = cibling;
//       (cibling->parent->right == p) ? cibling->parent->right = cibling : cibling->parent->left = cibling;
//       db_black_problem(p->right , x);
//       return ;
//     }
  
//   }
  
//   if ((cibling->color == BLACK && cibling->right->color == BLACK && cibling->left->color == RED) ||
//       (cibling->color == BLACK && cibling->right->color == RED && cibling->left->color == BLACK))
//    {
      
//     Node *red = (cibling->right->color == RED) ? cibling->right : cibling->left;
//     Node *black = (cibling->right->color == BLACK) ? cibling->right : cibling->left;
//     if ((this->_cmp(p->data, dbp->data) && cibling->right->color == RED) ||
//         (this->_cmp(dbp->data, p->data) && cibling->left->color == RED))
//     {
//       red->color = BLACK;
//       cibling->color = RED;
//       red->parent = p;
//       (p->left == cibling) ? p->left = red : p->right = red;
//       if (this->_cmp(red->data, cibling->data))
//       {
//         Node *cc = red->right;
//         red->right = cibling;
//         cibling->parent = red;
//         cibling->left = cc;
//         cc->parent = cibling;
//         //db_black_problem(dbp, x);
//         return ;
//       }
//       if (this->_cmp(cibling->data, red->data))
//       {
//         Node *cc = red->left;
//         red->left = cibling;
//         cibling->parent = red;
//         cibling->right = cc;
//         cc->parent = cibling;
//         db_black_problem(dbp, x);
//         return ;
//       }
//     }
//     if ((this->_cmp(p->data, dbp->data) && cibling->left->color == RED) ||
//         (this->_cmp(dbp->data, p->data) && cibling->right->color == RED))
//     {
//       std::cout << "lala" <<std::endl;
//       if (p->color == RED)
//       {
//         p->color = BLACK;
//         cibling->color = RED;
//       }
//       (p == this->_nodeRoot) ? cibling->parent = this->_nodeEnd : cibling->parent = p->parent;
//       (p == this->_nodeRoot) ? this->_nodeRoot = cibling : 0;
//       if (p->parent != this->_nodeEnd)
//         (p->parent->left == p) ? p->parent->left = cibling : p->parent->right = cibling;
//       // pas sur du tout pour cela on verra //
//       p->parent = cibling;
      
//       if (this->_cmp(p->data, dbp->data))
//       {
//         cibling->right = p;
//         p->left = black;
//         black->parent = p;
//         red->color = BLACK;
//         if (x == 0)
//           destroy_last_node(dbp);
//         return ;
//       }
//       else
//       {
//         cibling->left = p;
//         p->right = black;
//         black->parent = p;
//         red->color = BLACK;
//         if (x == 0)
//           destroy_last_node(dbp);
//         return ;
//       }
//     }
//    }
//   if (cibling->color == BLACK && cibling->left->color == RED && cibling->right->color == RED && dbp->color == BLACK && dbp->right == this->_nodeEnd && dbp->left == this->_nodeEnd)
//     {
      
//       if (this->_cmp(dbp->data, cibling->data))
//       {
//         (this->_nodeRoot == p) ? this->_nodeRoot = cibling : 0;
//         Node *app = p->parent;
//         Node *cc = cibling->left;
//         if (x == 0)
//           destroy_last_node(dbp);
//         p->parent = cibling;
//         p->right = cc;
//         p->left = this->_nodeEnd;
//         cc->parent = p;
//         cibling->left = p;
//         cibling->right->color = BLACK;
//         cibling->parent = app;
//         if (app != this->_nodeEnd)
//           (app->left == p) ? app->left = cibling : app->right = cibling;
//         return ;
//       }
//       if (this->_cmp(cibling->data , dbp->data) && p->color == BLACK)
//       {
//         (this->_nodeRoot == p) ? this->_nodeRoot = cibling : 0;
//         Node *app = p->parent;
//         Node *cc = cibling->right;
//         if (x == 0)
//           destroy_last_node(dbp);
//         p->parent = cibling;
//         p->left = cc;
//         p->right = this->_nodeEnd;
//         cc->parent = p;
//         cibling->right = p;
//         cibling->left->color = BLACK;
//         cibling->parent = app;
//         if (app != this->_nodeEnd)
//           (app->left == p) ? app->left = cibling : app->right = cibling;
//         return ;
//       }
//       if (this->_cmp(cibling->data , dbp->data) && p->color == RED)
//       {
//         if (x == 0)
//           destroy_last_node(dbp);
//         Node *cc = cibling->right;
//         cibling->parent = p->parent;
//         (cibling->parent->left == p) ? cibling->parent->left = cibling : cibling->parent->right = cibling;
//         cibling->right = p;
//         p->parent = cibling;
//         p->left = cc;
//         cc->parent = p;
//         cibling->color = RED;
//         cibling->left->color = BLACK;
//         cibling->right->color = BLACK;
//         return ;
//       }
//     }
//     if (cibling->color == BLACK && cibling->left->color == RED && cibling->right->color == RED && dbp->color == BLACK)
//     {
//       if (this->_cmp(dbp->data, cibling->data))
//       {
//         (this->_nodeRoot == p) ? this->_nodeRoot = cibling : 0;
//         Node *app = p->parent;
//         Node *cc = cibling->left;
//         if (x == 0)
//           destroy_last_node(dbp);
//         p->parent = cibling;
//         p->right = cc;
//         cc->parent = p;
//         cibling->left = p;
//         cibling->parent = app;
//         cibling->right->color = BLACK;
//         if (app != this->_nodeEnd)
//           (app->left == p) ? app->left = cibling : app->right = cibling;
//         return ;
//       }
//       if (this->_cmp(cibling->data, dbp->data))
//       {
//         (this->_nodeRoot == p) ? this->_nodeRoot = cibling : 0;
//         Node *app = p->parent;
//         Node *cc = cibling->right;
//         if (x == 0)
//           destroy_last_node(dbp);
//         p->parent = cibling;
//         p->left = cc;
//         cc->parent = p;
//         cibling->right = p;
//         cibling->parent = app;
//         cibling->left->color = BLACK;
//         if (app != this->_nodeEnd)
//           (app->left == p) ? app->left = cibling : app->right = cibling;
//         return ;
//       }
//     }
  
// }


// void  destroy_last_node(Node *node)
// {
//   if (node->parent->left == node)
//     node->parent->left = this->_nodeEnd;
//   else
//     node->parent->right = this->_nodeEnd;
//   this->_alloc.destroy(node);
//   this->_alloc.deallocate(node, 1);
// }

// Node  *swap_internal_node_second(Node *node1, Node *node2)
// {
//   Node *tmp = node1;
//   Node  *r  = node2->right;
//   Node  *l  = node2->left;
//   Node  *p  = node2->parent;
//   bool  color = node2->color;
//   bool  rl;                                      ///// right = 1 left = 0;

//   rl = (node2->parent->right == node2) ? 1 : 0;
//   node1 = node2;
  
//   node1->color = tmp->color;
//   node1->parent = tmp->parent;
//   if (node1->parent != this->_nodeEnd)
//   {
//     if (node1->parent->left == tmp)
//       node1->parent->left = node1;
//     else
//       node1->parent->right = node1;
//   }
//   node1->right = (node1 != tmp->right) ? tmp->right : tmp;
//   node1->left = (node1 != tmp->left) ? tmp->left : tmp;

//   (node1->right != this->_nodeEnd) ? node1->right->parent = node1 : 0;
//   (node1->left != this->_nodeEnd) ? node1->left->parent = node1 : 0;

//   if (tmp == this->_nodeRoot)
//     this->_nodeRoot = node1;

//   tmp->parent = p;
//   if (tmp == p)
//     tmp->parent = node1;
//   (rl == 1) ? tmp->parent->right = tmp : tmp->parent->left = tmp;

//   tmp->right = r;
//   (r != this->_nodeEnd) ? r->parent = tmp : 0;
//   tmp->left = l;
//   (l != this->_nodeEnd) ? l->parent = tmp : 0;
//   tmp->color = color;
//   return (tmp);
// }

// Node *find_smallest_node_subtree_right(Node *node)
// {
//   if (node->right != this->_nodeEnd)
//     node = node->right;
//   while (node->left != this->_nodeEnd)
//     node = node->left;
//   return (node);
// }

// Node *find_last_elem_subtree_right(Node *node)
// {
//   if (node->right == this->_nodeEnd)
//     return (node);
//   else
//     return (node->right);
// }

///////////////////////////////////////////////////
///////////////////case/////////////////////////
//////////////////////////////////////////////////









////////////////////////////////////////////
///////////////////////////////////////// fin deletion in red_black_tree ///////////////////////////////









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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void  checker2(Node *node)
{
  if (node != NULL && node->left != NULL && node != this->_nodeEnd && node->left != this->_nodeEnd)
    checker2(node->left);
  if (node != NULL && node->right != NULL && node != this->_nodeEnd && node->right != this->_nodeEnd)
    checker2(node->right);
  if (node != NULL && node->parent != NULL)
  {
    if (node->color == RED && node->parent->color == RED)
      std::cout << "\e[0;31m" <<"red red problem" << "\e[0m" << std::endl;
  }
}

void  checker(void)
{
  Node *node = this->_nodeRoot;
  int i = 0;
  int lala = 0;
  while (node != this->_nodeEnd)
  {
    if (node->color == BLACK)
      i++;
    node = node->left;
  }
  parcour1(this->_nodeRoot, i, &lala);
  if (lala > 0)
  {
    std::cout << "\e[0;34m" << "error l'arbre est desequilibrer" << "\e[0m" << std::endl;
    displayAllNode(this->_nodeRoot, 0);
  }
}


void  parcour1(Node *node, int nbr, int *i)
{
  (void)i;
  if (node->left != NULL && node->left != this->_nodeEnd)
    parcour1(node->left, nbr, i);
  if (node->left != NULL && node->right != NULL && node->left == this->_nodeEnd && node->right == this->_nodeEnd)
    {
      if (parcour2(node, nbr) == 0) 
        *i += 1;
    }
  if (node->right != NULL && node->right != this->_nodeEnd)
    parcour1(node->right, nbr, i);
}

bool parcour2(Node *node, int nbr)
{
  int i = 0;
  while (node != this->_nodeEnd)
  {
    if (node->color == BLACK)
      i++;
    node = node->parent;
  }
  return  (i != nbr) ? 0 : 1;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  void  displayAllNode(Node *node, int n)
  {
    if (node->left != NULL && node->left != this->_nodeEnd)
      displayAllNode(node->left , n + 1);
    if (node != this->_nodeEnd)
    {
      std::string spaces((20 * n), ' ');
      std::cout << spaces << "clef = " << node->data.first << std::endl;
      std::cout << spaces << "value = " << node->data.second << std::endl;
      std::cout << spaces << "mon noeud " << node << std::endl;
      std::cout << spaces << "parent = "<< node->parent->data.first << std::endl;
      std::cout << spaces << "left = "<< node->left->data.first << std::endl;
      std::cout << spaces << "right = "<< node->right->data.first << std::endl;
      if (node->color == RED)
        std::cout << spaces << "\e[0;31m" << "color = "<< node->color << "\e[0m"  << std::endl;
      else
        std::cout << spaces << "\e[0;32m" << "color = "<< node->color << "\e[0m"  << std::endl;
      std::cout << spaces << "///////////////" << std::endl;
    }
    if (node->right != NULL && node->right != this->_nodeEnd)
      displayAllNode(node->right, n + 1);
  }

   void change_color(Node *node, const value_type &x, bool color)
   {
    if (node->left != NULL && node->left != this->_nodeEnd)
      change_color(node->left, x, color);
    if (node != this->_nodeEnd && node->data.first == x.first)
      node->color = color;
    if (node->right != NULL && node->right != this->_nodeEnd)
      change_color(node->right, x, color);
   }
////////////////////////////////////////////////////////////////////////////
};
}
#endif