#ifndef ITER
# define ITER

/*
template<class In> typename iterator_traits<In>: :difference_type distance(In first, In last)
{
    typename iterator_traits<In>: :difference_type d= 0;
    while(first++!=last) d++;
    return d;
}
*/

/*
template<class In, class T> typename iterator_traits<In>::difference_type count(In first, In last, const T& val)
{
    typename iterator_traits<In>::difference_type res= 0;
    while(first!= last) if(*first++ == val) ++res;
    return res;
}
*/
#include <cstddef>

namespace ft
{
    struct input_iterator_tag{};
    struct output_iterator_tag{};
    struct forward_iterator_tag: public input_iterator_tag{};
    struct bidirectional_iterator_tag: public forward_iterator_tag{};
    struct random_access_iterator_tag: public bidirectional_iterator_tag{};

    template<class Iter> struct iterator_traits
    {
        typedef typename Iter::iterator_category    iterator_category; // §19.2.3
        typedef typename Iter::value_type           value_type; // type of element
        typedef typename Iter::difference_type      difference_type;
        typedef typename Iter::pointer              pointer; // return type of operator– >()
        typedef typename Iter::reference            reference; // return type of operator*()
    };

    template<class T> struct iterator_traits<const T*>
    { // specialization for pointers
        typedef random_access_iterator_tag  iterator_category;
        typedef T                           value_type;
        typedef ptrdiff_t                   difference_type;
        typedef T*                          pointer;
        typedef T&                          reference;
    };

    template<class T> struct iterator_traits<T*>
    { // specialization for pointers
        typedef random_access_iterator_tag  iterator_category;
        typedef T                           value_type;
        typedef ptrdiff_t                   difference_type;
        typedef T*                          pointer;
        typedef T&                          reference;
    };
    
    template<class Cat, class T, class Dist= ptrdiff_t, class Ptr= T*, class Ref= T&>
    struct iterator
    {
        typedef Cat     iterator_category; // §19.2.3
        typedef T       value_type; // type of element
        typedef Dist    difference_type; // type of iterator difference
        typedef Ptr     pointer; // return type for – >
        typedef Ref     reference; // return type for *
    };
}

#endif