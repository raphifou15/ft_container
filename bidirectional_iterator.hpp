#ifndef TREEITER
# define TREEITER

# include "iterator.hpp"
# include "red_black_tree.hpp"

namespace ft
{
    template<class T, class Node>
    class treeIterator : public iterator<bidirectional_iterator_tag, T>
    {
        public:
        
        typedef typename ft::iterator<bidirectional_iterator_tag, T>::value_type         value_type;
        typedef typename ft::iterator<bidirectional_iterator_tag, T>::difference_type    difference_type;
        typedef typename ft::iterator<bidirectional_iterator_tag, T>::pointer            pointer;
        typedef typename ft::iterator<bidirectional_iterator_tag, T>::reference          reference;
        typedef typename ft::iterator<bidirectional_iterator_tag, T>::iterator_category  iterator_category;

        

        explicit treeIterator(Node *const &lala, Node *const &lala2, Node *const &lala3): current(lala), _node_endl(lala2), _node_root(lala3){ std::cout << "ici" << std::endl;}
        treeIterator(void): current(NULL), _node_endl(NULL), _node_root(NULL){ std::cout << "lili lala" << std::endl; }
        template <class U> 
        treeIterator(const treeIterator<U, Node>& u)
        {
            std::cout << "mli33" << std::endl;
            this->current = u.base();
            this->_node_endl = u.base2();
            this->_node_root = u.base3();
        }
         template <class U> treeIterator &operator=(const treeIterator<U, Node>& u)
         {
             std::cout << "mli222" << std::endl;

             this->current = u.base();
             this->_node_endl = u.base2();
             this->_node_root = u.base3();
             return (*this);
         }
        /*
        operator treeIterator<const T, Node>(void) const {
            std::cout << "coucou" << std::endl;
			return treeIterator<const T, Node>(this->current, this->_node_endl, this->_node_root); 
		}
        */

        Node *  base() const { return this->current;}
        Node *  base2() const { return this->_node_endl;}
        Node *  base3() const { return this->_node_root;}
        ~treeIterator(){ std::cout << "treeiterator dtor called" <<std::endl;}
        reference operator*() const
        {
            return  (this->current->data);
        }
        pointer operator->() const
        {
            return &(operator*());
        }

        treeIterator&    operator++()
        {
           Node *max = max_node();
           
            
            if (this->current == this->_node_endl)
            {   
                this->current = max;
                if (this->current->left != this->_node_endl)
                    this->current = this->current->left;
                return *this;
            }

            if (this->current == max)
            {
                this->current = this->_node_endl;
                return *this;
            }

            if (this->current->right != this->_node_endl)
            {
                if (this->current->right->left != this->_node_endl)
                {
                    this->current = this->current->right->left;
                    while (this->current->left != this->_node_endl)
                        this->current = this->current->left;
                }
                else
                    this->current = this->current->right;
            }
            else
            {
                while (this->current == this->current->parent->right)
                    this->current = this->current->parent;
                this->current = this->current->parent;
            }
            
            return *this;
        }

        treeIterator    operator++(int)
        {
            treeIterator    tmp = *this;
            operator++();
            return tmp;
        }

        treeIterator&    operator--()
        {
            Node *min = min_node();

            if (this->current == this->_node_endl)
            {
                this->current = max_node();
                return *this;
            }
            if (this->current == min)
            {
                this->current = this->_node_endl;
                return *this;
            }
            if (this->current->left != this->_node_endl)
            {
                if (this->current->left->right != this->_node_endl)
                {
                    this->current = this->current->left->right;
                    while (this->current->right != this->_node_endl)
                        this->current = this->current->right;
                }
                else
                    this->current = this->current->left;
            }
            else
            {
                while (this->current == this->current->parent->left)
                    this->current = this->current->parent;
                this->current = this->current->parent;
            }
            return *this;
        }

        treeIterator    operator--(int)
        {
            treeIterator    tmp = *this;
            operator--();
            return tmp;
        }

        private:
            Node    *current;
            Node    *_node_endl;
            Node    *_node_root;

            Node    *max_node(void)
            {
                Node *node = this->_node_endl->left;

                if (node == NULL)
                    return this->_node_endl;
                while (node->right != this->_node_endl)
                {            
                    node = node->right;
                }
                return (node);
            }
        


            Node    *min_node(void)
            {
                Node *node = this->_node_endl->left;

                if (node == NULL)
                    return (this->_node_endl);
                while (node->left != this->_node_endl)
                    node = node->left;
                return (node);
            }
    };

    template <class T, class Node>
    bool operator==( const treeIterator<T, Node>& x, const treeIterator<T, Node>& y)
    {
        return (x.base() == y.base());
    }

    template <class T, class Node>
    bool operator!=( const treeIterator<T, Node>& x, const treeIterator<T, Node>& y)
    {
        return (x.base() != y.base());
    }
    ////////////////////////////////////////////////////////////////////////////
    // right left //////////////////////

    template <class TL, class TR, class Node>
    bool operator==( const treeIterator<TL, Node>& x, const treeIterator<TR, Node>& y)
    {
        return (x.base() == y.base());
    }

    template <class TL, class TR, class Node>
    bool operator!=( const treeIterator<TL, Node>& x, const treeIterator<TR, Node>& y)
    {
        return (x.base() != y.base());
    }

    /////////////////////////////////////////////////////////////////
}

#endif



