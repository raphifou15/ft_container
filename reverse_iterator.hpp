#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include <cstddef>
# include <string>
# include <iostream>
# include "iterator.hpp"
# include "is_integral.hpp"
# include "enable_if.hpp"

namespace ft
{
    template <class Iterator> 
    class reverse_iterator : public iterator<typename iterator_traits<Iterator>::iterator_category, typename iterator_traits<Iterator>::value_type, typename iterator_traits<Iterator>::difference_type, typename iterator_traits<Iterator>::pointer, typename iterator_traits<Iterator>::reference>
    {
        protected:
            Iterator    current;
        public:
            typedef Iterator                                            iterator_type;
            typedef typename iterator_traits<Iterator>::difference_type difference_type;
            typedef typename iterator_traits<Iterator>::reference       reference;
            typedef typename iterator_traits<Iterator>::pointer         pointer;

            reverse_iterator(): current(){}
            explicit reverse_iterator(Iterator x): current(x){} // Effects: Initializes current with x
            template <class U> reverse_iterator(const reverse_iterator<U>& u) {current = u.base();} // Effects: Initializes current with u.current
            Iterator base() const {return this->current;} // explicit Returns: current

    /*

        operator reverse_iterator<const Iterator>(void) const {
            std::cout << "coucou4444" << std::endl;
			return reverse_iterator<const Iterator>(this->current); 
		}
*/
            reference operator*() const // Effects: Iterator tmp = current; return *--tmp;
            {
                iterator_type tmp = this->current;
                return (*--tmp);
            }
            pointer operator->() const // Effects: return &(operator*());
            {
                return &(operator*());
            }
            reverse_iterator& operator++() // Effects: --current; Returns: *this
            {
                --this->current;
                return (*this);
            }
            reverse_iterator operator++(int) // Effects: reverse_iterator tmp = *this; --current; return tmp;
            {
                reverse_iterator tmp = *this;
                --this->current;
                return (tmp);
            }
            reverse_iterator& operator--() // Effects: ++current Returns: *this;
            {
                ++this->current;
                return (*this);
            }
            reverse_iterator operator--(int) // Effects: reverse_iterator tmp = *this; ++current; return tmp;
            {
                reverse_iterator tmp = *this;
                ++this->current;
                return tmp;
            }
            reverse_iterator operator+ (difference_type n) const // Returns: reverse_iterator(current-n)
            {
                return reverse_iterator(this->current - n);
            }
            reverse_iterator& operator+=(difference_type n) // Effects: current -= n; Returns: *this
            {
                this->current -= n;
                return (*this);
            }
            reverse_iterator operator- (difference_type n) const // Returns: reverse_iterator(current+n)
            {
                return reverse_iterator(this->current + n);
            }
            reverse_iterator& operator-=(difference_type n) // Effects: current += n; Returns: *this
            {
                this->current += n;
                return (*this);
            }
            reference operator[](difference_type n) const // Returns: current[-n-1]
            {
                return this->current[-n - 1];
            }
    };

    template <class Iterator>
    bool operator==( const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) // Returns: x.current == y.current
    {
        return (x.base() == y.base());
    }
    template <class Iterator>
    bool operator<( const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) // Returns: x.current > y.current
    {
        return (x.base() > y.base());
    }
    template <class Iterator>
    bool operator!=( const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) // Returns: x.current != y.current
    {
        return (x.base() != y.base());
    }
    template <class Iterator>
    bool operator>( const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) // Returns: x.current < y.current
    {
        return (x.base() < y.base());
    }
    template <class Iterator>
    bool operator>=( const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) // Returns: x.current <= y.current
    {
        return (x.base() <= y.base());
    }
    template <class Iterator>
    bool operator<=( const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) // Returns: x.current >= y.current
    {
        return (x.base() >= y.base());
    }
    template <class Iterator>
    typename reverse_iterator<Iterator>::difference_type operator-( const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) // Returns: y.current - x.current
    {
        return (y.base() - x.base());
    }  
    template <class Iterator>
    reverse_iterator<Iterator> operator+( typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& x) // Returns: reverse_iterator<Iterator> (x.current - n)
    {
        return reverse_iterator<Iterator> (x.base() - n);
    }
    
///////////////////////////////////////////////////////////////////////////////////////////////////////////////// right left begin



    template <class IteratorL, class IteratorR>
    bool operator==( const reverse_iterator<IteratorL>& x, const reverse_iterator<IteratorR>& y) // Returns: x.current == y.current
    {
        return (x.base() == y.base());
    }
    template <class IteratorL, class IteratorR>
    bool operator<( const reverse_iterator<IteratorL>& x, const reverse_iterator<IteratorR>& y) // Returns: x.current > y.current
    {
        return (x.base() > y.base());
    }
    template <class IteratorL, class IteratorR>
    bool operator!=( const reverse_iterator<IteratorL>& x, const reverse_iterator<IteratorR>& y) // Returns: x.current != y.current
    {
        return (x.base() != y.base());
    }
    template <class IteratorL, class IteratorR>
    bool operator>( const reverse_iterator<IteratorL>& x, const reverse_iterator<IteratorR>& y) // Returns: x.current < y.current
    {
        return (x.base() < y.base());
    }
    template <class IteratorL, class IteratorR>
    bool operator>=( const reverse_iterator<IteratorL>& x, const reverse_iterator<IteratorR>& y) // Returns: x.current <= y.current
    {
        return (x.base() <= y.base());
    }
    template <class IteratorL, class IteratorR>
    bool operator<=( const reverse_iterator<IteratorL>& x, const reverse_iterator<IteratorR>& y) // Returns: x.current >= y.current
    {
        return (x.base() >= y.base());
    }
    
    template <class IteratorL, class IteratorR>
    typename reverse_iterator<IteratorL>::difference_type operator-( const reverse_iterator<IteratorL>& x, const reverse_iterator<IteratorR>& y) // Returns: y.current - x.current
    {
        return (y.base() - x.base());
    }  
    template <class IteratorL, class IteratorR>
    reverse_iterator<IteratorL> operator+( typename reverse_iterator<IteratorL>::difference_type n, const reverse_iterator<IteratorR>& x) // Returns: reverse_iterator<Iterator> (x.current - n)
    {
        return reverse_iterator<IteratorL> (x.base() - n);
    }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// right left end
}

#endif