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

        treeIterator(void): current(NULL){}
        explicit treeIterator(Node *const &lala): current(lala){}
        template <class U> treeIterator(const treeIterator<U, Node>& u){ this->current = u.base();}
        template <class U> treeIterator &operator=(const treeIterator<U, Node>& u)
        {
            this->current = u.base();
            return (*this);
        }
        Node *  base() const { return this->current;}
        ~treeIterator(){}
        reference operator*() const
        {
            return  (this->current->data);
        }

        private:
            Node *current;
    };
}

#endif