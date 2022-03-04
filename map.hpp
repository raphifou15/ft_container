#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include <iostream>
# include <stdexcept>
# include <sstream>
# include <algorithm>
# include <sys/cdefs.h>
# include "bidirectional_iterator.hpp"
# include "pair.hpp"
# include "red_black_tree.hpp"
# include "lexicographical_compare.hpp"
# include "iterator.hpp"
# include "reverse_iterator.hpp"
# include "enable_if.hpp"
# include "is_integral.hpp"

namespace ft
{
    // template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
    template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
    class map
    {
        public:
    //     // types:
        typedef Key                                                     key_type;
        typedef T                                                       mapped_type;
        typedef ft::pair<const Key, T>                                  value_type;
        typedef Compare                                                 key_compare;
        typedef Allocator                                               allocator_type;
        typedef typename Allocator::reference                           reference;
        typedef typename Allocator::const_reference                     const_reference;
        typedef ft::treeIterator<value_type, ft::Node<value_type> >     iterator;// See 23.1
        typedef ft::treeIterator< const value_type, ft::Node<value_type> > const_iterator; // See 23.1
        typedef typename Allocator::size_type                           size_type; // See 23.1
        typedef typename Allocator::difference_type                     difference_type;// See 23.1
        typedef typename Allocator::pointer                             pointer;
        typedef typename Allocator::const_pointer                       const_pointer;
        typedef ft::reverse_iterator<iterator>                         reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>                   const_reverse_iterator;

        class value_compare : public std::binary_function<value_type,value_type,bool>
        {
            friend class map;
            protected:
            Compare comp;
            value_compare(Compare c) : comp(c) {}
            public:
            bool operator()(const value_type& x, const value_type& y) const
            {
                return comp(x.first, y.first);
            }
        };
        private:
            RedBlackTree<value_type, value_compare>   _rb;
        public:
    //// 23.3.1.1 construct/copy/destroy:
        explicit map(const Compare& comp = Compare(), const Allocator& = Allocator()) : _rb(value_compare(comp)) {
        }
        template <class InputIterator>
        map(InputIterator first, InputIterator last, const Compare&comp = Compare(), const Allocator& = Allocator(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL) : _rb(value_compare(comp))
        {
            insert(first, last);
        }
        map(const map<Key,T,Compare,Allocator>& x): _rb(value_compare(key_compare())){ insert(x.begin(), x.end()); }
        ~map(){}
        map<Key,T,Compare,Allocator>& operator=(const map<Key,T,Compare,Allocator>& x)
        {
            this->_rb.destroyAllElements(this->_rb.getRoot());
            insert(x.begin(), x.end());
            return (*this);
        }
    // iterators:
        iterator begin()
        {
            return (iterator(this->_rb.get_begin(), this->_rb.get_endl_node(), this->_rb.getRoot()));
        }

        const_iterator begin() const
        {
            return (const_iterator(this->_rb.get_begin(), this->_rb.get_endl_node(), this->_rb.getRoot()));
        }

        iterator end()
        {
            return (iterator(this->_rb.get_endl_node(), this->_rb.get_endl_node(), this->_rb.getRoot()));
        }

        const_iterator end() const
        {
            return (const_iterator(this->_rb.get_endl_node(), this->_rb.get_endl_node(), this->_rb.getRoot()));
        }

        reverse_iterator rbegin()
        {
            return (reverse_iterator(end()));
        }

        const_reverse_iterator rbegin() const
        {
            return (const_reverse_iterator(end()));
        }

        reverse_iterator rend()
        {
            return (reverse_iterator(begin()));
        }

        const_reverse_iterator rend() const
        {
           
            return (const_reverse_iterator(begin()));
        }

        // capacity:

        bool empty() const{ return (this->_rb.size() != 0) ? 0 : 1; }
        size_type size() const { return (this->_rb.size());}
        size_type max_size() const { return (this->_rb.maxSize());}

    //     // 23.3.1.2 element access:

        T& operator[](const key_type& x)
        {
            return (*((insert(ft::make_pair(x, T()))).first)).second;
        }

        // modifiers:
        pair<iterator, bool> insert(const value_type& x)
        {
            iterator it = find(x.first);
            if (it != iterator(this->_rb.get_endl_node(), this->_rb.get_endl_node(), this->_rb.getRoot()))
                return (ft::make_pair(it, false));
            this->_rb.insert(x);
            it = find(x.first);
            return (ft::make_pair(it, true));
            //faire une insertion d'un element
            // dans un premier temps rechercher si la clef existe ou non si elle existe deja ne pas inserer d'element nouveau.
            // dans un second temps inserer le nouvel element.
        }
    
        iterator insert(iterator , const value_type& x)
        {
            insert(x);
            return (find(x.first));
        }
        template <class InputIterator>  void insert(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
        {
            for (; first != last; first++)
            {
                iterator it = find((*first).first);
                if (it == iterator(this->_rb.get_endl_node(), this->_rb.get_endl_node(), this->_rb.getRoot()))
                    insert(*first);
            }
        }

        void erase(iterator position)
        {
            this->_rb.erase(*position);
        }

        size_type erase(const key_type& x)
        {
            //display_element();
            //std::cout << "\n\n\n\n\n\n" << std::endl;
            bool tf = this->_rb.erase(ft::make_pair(x, mapped_type()));
            //display_element();
            //std::cout << "\n\n\n\n\n\n" << std::endl;
            return (tf);
        }

        void erase(iterator first, iterator last)
        {
            while (first != last)
            {
                //display_element();
                //std::cout << "\n\n\n\n\n\n" << std::endl;
                iterator position = first;
                ++first;
                this->_rb.erase(*position);
                //display_element();
                //std::cout << "\n\n\n\n\n\n" << std::endl;
            }
        }
        void swap(map<Key,T,Compare,Allocator> &lala)
        {
            this->_rb.swap(lala._rb);
        }
        void clear(void)
        {
            this->_rb.destroyAllElements(this->_rb.getRoot());
        }


    //     // observers:
        key_compare key_comp() const
        {
            return (key_compare());
        }
        
        value_compare value_comp() const
        {
            return value_compare(key_compare());
        }
        

    //     // 23.3.1.3 map operations:
        iterator find(const key_type& x)
        {
            return iterator(this->_rb.find(ft::make_pair(x, mapped_type())), this->_rb.get_endl_node(), this->_rb.getRoot()); 
        }
        const_iterator find(const key_type& x) const
        {
            return const_iterator(this->_rb.find(ft::make_pair(x, mapped_type())), this->_rb.get_endl_node(), this->_rb.getRoot());
        }

        size_type count(const key_type& x) const
        {
            const_iterator it = find(x);
            const_iterator et = end();
            return (it == et) ? 0 : 1;
            //return ((*it).first);
        }

        iterator lower_bound(const key_type& x)
        {
            const Compare& comp = Compare();
            iterator it = begin();
            iterator ite = end();
            for (;it != ite; it++)
            {
                if (comp((*it).first, x))
                    ;
                else
                    break;
            }
            return (it);
        }

        const_iterator lower_bound(const key_type& x) const
        {
            const Compare& comp = Compare();
            const_iterator it = begin();
            const_iterator ite = end();
            for (;it != ite; it++)
            {
                if (comp((*it).first, x))
                    ;
                else
                    break;
            }
            return (it);
        }
        
        iterator upper_bound(const key_type& x)
        {
            iterator    ite = end();
            iterator    it = lower_bound(x);

            if (it != ite && (*it).first == x)
                return (++it);
            return (it);
        }
        const_iterator upper_bound(const key_type& x) const
        {
            const_iterator  ite = end();
            const_iterator it = lower_bound(x);
            if (it != ite && (*it).first == x)
                return (++it);
            return (it);
        }
    
        pair<iterator,iterator> equal_range(const key_type& x)
        {
            return ft::make_pair(lower_bound(x), upper_bound(x));
        }

        pair<const_iterator,const_iterator> equal_range(const key_type& x) const
        {
            return ft::make_pair(lower_bound(x), upper_bound(x));
        }

        void    display_element(void)
           {
            this->_rb.displayAllNode(this->_rb.getRoot(), 0);
        }

        void    change_color(const key_type& x, bool color)
        {
            this->_rb.change_color(this->_rb.getRoot(), ft::make_pair(x, mapped_type()), color);
        }

        void    check(void)
        {
            this->_rb.checker();
        }

        friend bool operator==(const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y)
        {
            if (x.size() != y.size())
                return (0);
            if (ft::equal(x.begin(), x.end(), y.begin()))
                return (1);
            return (0);
        }
        friend bool operator< (const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y)
        {
            return (ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()));
        }
    };

    template <class Key, class T, class Compare, class Allocator>
    bool operator!=(const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y)
    {
        return ((x == y) ? 0 : 1);
    }
    template <class Key, class T, class Compare, class Allocator>
    bool operator> (const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y)
    {
        return (y < x);
    }
    template <class Key, class T, class Compare, class Allocator>
    bool operator>=(const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y)
    {
        return ((y < x) || (x == y));
    }
    template <class Key, class T, class Compare, class Allocator>
    bool operator<=(const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y)
    {
        return ((x < y) || (x == y));
    }
    // specialized algorithms:
    template <class Key, class T, class Compare, class Allocator>
    void swap(map<Key,T,Compare,Allocator>& x, map<Key,T,Compare,Allocator>& y)
    {
        x.swap(y);
    }
}

#endif