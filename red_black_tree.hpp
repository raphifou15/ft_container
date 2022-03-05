#ifndef RED_BLACK_TREE
# define RED_BLACK_TREE

# define BLACK 0
# define RED   1

# include <memory>
# include <iostream>
# include <stdexcept>
# include <sstream>
# include "map.hpp"
# include "treeIterator.hpp"
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



  Node  *insert(const value_type &x, bool *tf)
  {
    Node *lala = this->_alloc.allocate(1);
    this->_alloc.construct(lala, Node(x, this->_nodeEnd, this->_nodeEnd, this->_nodeEnd, BLACK));
    this->_capacity += 1;
    if (this->_nodeRoot == this->_nodeEnd && this->_capacity == 1)
    {
      this->_nodeRoot = lala;
      this->_nodeEnd->left = this->_nodeRoot;
    }
    else
    {
      lala->color = RED;
      lala = insert_elem(lala, tf);
      this->_nodeEnd->left = this->_nodeRoot;
    }
    return (lala);
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////nouvel tentative d'insertion////////////////////////////////////



  Node  *insert_elem(Node *node, bool *tf)
  {
    Node  *pr = this->_nodeRoot;
    while (pr != this->_nodeEnd)
    {
      if (node->data.first == pr->data.first)
      {
        this->_alloc.destroy(node);
        this->_alloc.deallocate(node, 1);
        this->_capacity -= 1;
        *tf = 0;
        return (pr);
      }
      if (this->_cmp(node->data, pr->data))
      {
        if (pr->left == this->_nodeEnd)
        {
          pr->left = node;
          node->parent = pr;
          if (pr->color == RED) red_conflict(node);
          return node;
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
          return node;
        }
        pr = pr->right;
      }
    }
    return (pr);
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



///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////                            ///////////////////////////////////////
////////////////////////////////////////// deletion in red_black_tree ///////////////////////////////////////
/////////////////////////////////////////                             //////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////                           /////////////////////////////////////
////////////////////////////////////        fin deletion       /////////////////////////////////////
///////////////////////////////////                           /////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// fonction de debug ////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

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
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////fin de fonction de debug ////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
};

}
#endif