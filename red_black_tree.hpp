#ifndef RED_BLACK_TREE
# define RED_BLACK_TREE

# define BLACK 0;
# define RED   1;

# include <memory>
# include <iostream>
# include <stdexcept>
# include <sstream>



// code inspirer de la documentation https://www.programiz.com/dsa/red-black-tree
template <class T>
class Node
{
    public:
        T  data;   //value de la clef
        Node        *parent; // noeud parent
        Node        *left; // noeud droit
        Node        *right; // noeud gauche
        int         color;  // couleur du noeud

    // initialisation de node a 0
  //  Node() : data(), parent(NULL), left(NULL), right(NULL), color(BLACK) {}
  //  Node () : 
};

template <class T, >

#endif