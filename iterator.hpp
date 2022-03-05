#ifndef ITER
# define ITER

# include <cstddef>
# include <string>
# include "is_integral.hpp"
# include "enable_if.hpp"
namespace ft
{
    // Standard iterator tags
    struct input_iterator_tag {};
    struct output_iterator_tag {};
    struct forward_iterator_tag: public input_iterator_tag {};
    struct bidirectional_iterator_tag: public forward_iterator_tag {};
    struct random_access_iterator_tag: public bidirectional_iterator_tag {};

    // 24.3, primitives:
    // > definis comme suit
    template<class Iterator> struct iterator_traits
    {
        typedef typename Iterator::difference_type      difference_type;
        typedef typename Iterator::value_type           value_type;
        typedef typename Iterator::pointer              pointer;
        typedef typename Iterator::reference            reference;
        typedef typename Iterator::iterator_category    iterator_category;
    };

    // Il est spécialisé pour les pointeurs comme
    template<class T> struct iterator_traits<T*>
    {
        typedef ptrdiff_t                   difference_type;
        typedef T                           value_type;
        typedef T*                          pointer;
        typedef T&                          reference;
        typedef random_access_iterator_tag  iterator_category;
    };
    // pour les pointeurs à const comme
    template<class T> struct iterator_traits<const T*>
    {
        typedef ptrdiff_t                   difference_type;
        typedef T                           value_type;
        typedef const T*                    pointer;
        typedef const T&                    reference;
        typedef random_access_iterator_tag iterator_category;
    };

    // [Note : S’il y a un pointeur supplémentaire de type type __far tel que la différence de deux __far est de type long, une implémentation peut etre définis
    // https://stackoverflow.com/questions/3869830/near-and-far-pointers/3869852
    /*
    template<class T> struct iterator_traits<T __far*>
    {
        typedef long difference_type;
        typedef T value_type;
        typedef T __far* pointer;
        typedef T __far& reference;
        typedef random_access_iterator_tag iterator_category;
    };
    */

    
    template<class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
    struct iterator
    {
        typedef T           value_type;
        typedef Distance    difference_type;
        typedef Pointer     pointer;
        typedef Reference   reference;
        typedef Category    iterator_category;
    };

    // 24.3.4, iterator operations:
    template <class InputIterator, class Distance>
    void advance(InputIterator& i, Distance n, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
    {
        i += n;
    }
    
    // Requires: n may be negative only for random access and bidirectional iterators.
    // Effects: Increments (or decrements for negative n) iterator reference i by n.

    template <class InputIterator>
    typename iterator_traits<InputIterator>::difference_type
    distance(InputIterator first, InputIterator last)
    {
        typename iterator_traits<InputIterator>::difference_type lala = 0;
        for (; first != last; first++)
            lala++;
        return (lala);
    }
    // Effects: Returns the number of increments or decrements needed to get from first to last.
    // Requires: last must be reachable from first.
    // 24.4, predefined iterators:   

}
#endif