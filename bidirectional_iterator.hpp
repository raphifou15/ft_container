#ifndef TREEITER
# define TREEITER

# include "iterator.hpp"
# include "red_black_tree.hpp"

namespace ft
{
    template<class T>
    class treeIterator : public iterator<bidirectional_iterator_tag, T>
    {
        public:
        
        typedef typename ft::iterator<bidirectional_iterator_tag, T>::value_type         value_type;
        typedef typename ft::iterator<bidirectional_iterator_tag, T>::difference_type    difference_type;
        typedef typename ft::iterator<bidirectional_iterator_tag, T>::pointer            pointer;
        typedef typename ft::iterator<bidirectional_iterator_tag, T>::reference          reference;
        typedef typename ft::iterator<bidirectional_iterator_tag, T>::iterator_category  iterator_category;

        treeIterator(): current(NULL){}
        explicit treeIterator(pointer x) : current(x){}
        template <class U> treeIterator(const treeIterator<U>& u)
        {
            this->current = u.base();
        }
        pointer     base() const
        {
            return this->current;
        }
        private:
            pointer current;
    };
}

#endif