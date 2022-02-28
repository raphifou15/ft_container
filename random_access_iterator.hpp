#ifndef RANDOM_ACCESS_ITER
# define RANDOM_ACCESS_ITER

# include <cstddef>
# include <string>
# include "iterator.hpp"
# include "is_integral.hpp"
# include "enable_if.hpp"

namespace ft
{
    template<class Iterator>
    class random_access_iterator : public iterator<random_access_iterator_tag, Iterator>
    {
        public:

            typedef typename ft::iterator<random_access_iterator_tag, Iterator>::value_type         value_type;
            typedef typename ft::iterator<random_access_iterator_tag, Iterator>::difference_type    difference_type;
            typedef typename ft::iterator<random_access_iterator_tag, Iterator>::pointer            pointer;
            typedef typename ft::iterator<random_access_iterator_tag, Iterator>::reference          reference;
            typedef typename ft::iterator<random_access_iterator_tag, Iterator>::iterator_category  iterator_category;

            random_access_iterator(): current(NULL){}
            explicit random_access_iterator(pointer x) : current(x){}
            template <class U> random_access_iterator(const random_access_iterator<U>& u)
            {
                current = u.base();
            }

            pointer     base() const
            {
                 return this->current;
            }
            template <class U> random_access_iterator  &operator=(const random_access_iterator<U>& u)
            {
                this->current = u.base();
                return (*this);
            }

            ~random_access_iterator(){}

            reference operator*() const
            {
                return  *(this->current);
            }

            pointer operator->() const
            {
                return &(operator*());
            }

            random_access_iterator& operator++()
            {
                ++this->current;
                return *this;
            }
            random_access_iterator operator++(int) 
            {
                random_access_iterator  tmp = *this;
                ++this->current;
                return tmp;
            }
            random_access_iterator& operator--()
            {
                --this->current;
                return *this;
            }
            random_access_iterator operator--(int) 
            {
                random_access_iterator  tmp = *this;
                --this->current;
                return tmp;
            }
            random_access_iterator& operator+=(difference_type n) 
            {
                this->current += n;
                return (*this);
            }

            random_access_iterator operator+(difference_type n) const
            {
                /*random_access_iterator  tmp = *this;
                tmp.current = this->current + n;
                return (tmp);*/
                return random_access_iterator(this->current + n);
            }
            random_access_iterator& operator-=(difference_type n) 
            {
                this->current -= n;
                return (*this);
            }
            random_access_iterator operator-(difference_type n) const
            {
              /*  random_access_iterator  tmp = *this;
                tmp.current = this->current + n;
                return (tmp);*/
                return random_access_iterator(this->current - n);
            }
            reference operator[](difference_type n) const
            {
                random_access_iterator  tmp = *this;
                tmp.current = this->current + n;
                return *tmp.current;
            }
            
        private:
            pointer current;
    };

    template <class Iterator>
    bool operator==( const random_access_iterator<Iterator>& x, const random_access_iterator<Iterator>& y)
    {
        return (x.base() == y.base());
    }
    template <class Iterator>
    bool operator!=( const random_access_iterator<Iterator>& x, const random_access_iterator<Iterator>& y)
    {
        return (x.base() != y.base());
    }
    template <class Iterator>
    bool operator<( const random_access_iterator<Iterator>& x, const random_access_iterator<Iterator>& y)
    {
        return (x.base() < y.base());
    }
    template <class Iterator>
    bool operator>( const random_access_iterator<Iterator>& x, const random_access_iterator<Iterator>& y)
    {
        return (x.base() > y.base());
    }
    template <class Iterator>
    bool operator>=( const random_access_iterator<Iterator>& x, const random_access_iterator<Iterator>& y)
    {
        return (x.base() >= y.base());
    }
    template <class Iterator>
    bool operator<=( const random_access_iterator<Iterator>& x, const random_access_iterator<Iterator>& y)
    {
        return (x.base() <= y.base());
    }


    template <class Iterator>
    typename random_access_iterator<Iterator>::difference_type operator-( const random_access_iterator<Iterator>& x, const random_access_iterator<Iterator>& y)
    {
        return (x.base() - y.base());
    }

    template <class Iterator>
    random_access_iterator<Iterator> operator+( typename random_access_iterator<Iterator>::difference_type n, const random_access_iterator<Iterator>& x)
    {
        return random_access_iterator<Iterator> (x.base() + n);
    }

//////////////////////////////////////////////////////// right left begin

    template <class IteratorL, class IteratorR>
    bool operator==( const random_access_iterator<IteratorL>& x, const random_access_iterator<IteratorR>& y)
    {
        return (x.base() == y.base());
    }

    template <class IteratorL, class IteratorR>
    bool operator!=( const random_access_iterator<IteratorL>& x, const random_access_iterator<IteratorR>& y)
    {
        return (x.base() != y.base());
    }

    template <class IteratorL, class IteratorR>
    bool operator<( const random_access_iterator<IteratorL>& x, const random_access_iterator<IteratorR>& y)
    {
        return (x.base() < y.base());
    }

    template <class IteratorL, class IteratorR>
    bool operator>( const random_access_iterator<IteratorL>& x, const random_access_iterator<IteratorR>& y)
    {
        return (x.base() > y.base());
    }

    template <class IteratorL, class IteratorR>
    bool operator>=( const random_access_iterator<IteratorL>& x, const random_access_iterator<IteratorR>& y)
    {
        return (x.base() >= y.base());
    }

    template <class IteratorL, class IteratorR>
    bool operator<=( const random_access_iterator<IteratorL>& x, const random_access_iterator<IteratorR>& y)
    {
        return (x.base() <= y.base());
    }

    template <class IteratorL, class IteratorR>
    typename random_access_iterator<IteratorL>::difference_type operator-( const random_access_iterator<IteratorL>& x, const random_access_iterator<IteratorR>& y)
    {
        return (x.base() - y.base());
    }

    template <class IteratorL, class IteratorR>
    random_access_iterator<IteratorL> operator+( typename random_access_iterator<IteratorL>::difference_type n, const random_access_iterator<IteratorR>& x)
    {
        return random_access_iterator<IteratorL> (x.base() + n);
    }


///////////////////////////////  right left end
}

#endif