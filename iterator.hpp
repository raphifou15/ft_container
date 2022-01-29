#ifndef ITER
# define ITER

# include <cstddef>
# include <string>
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

    
    template<class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&> struct iterator
    {
        typedef T           value_type;
        typedef Distance    difference_type;
        typedef Pointer     pointer;
        typedef Reference   reference;
        typedef Category    iterator_category;
    };

    // 24.3.4, iterator operations:
    template <class InputIterator, class Distance>
    void advance(InputIterator& i, Distance n);

    // Requires: n may be negative only for random access and bidirectional iterators.
    // Effects: Increments (or decrements for negative n) iterator reference i by n.

    template <class InputIterator>
    typename iterator_traits<InputIterator>::difference_type
    distance(InputIterator first, InputIterator last);
    // Effects: Returns the number of increments or decrements needed to get from first to last.
    // Requires: last must be reachable from first.
    // 24.4, predefined iterators:
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

            reverse_iterator();
            explicit reverse_iterator(Iterator x); // Effects: Initializes current with x
            template <class U> reverse_iterator(const reverse_iterator<U>& u); // Effects: Initializes current with u.current
            Iterator base() const; // explicit Returns: current
            reference operator*() const; // Effects: Iterator tmp = current; return *--tmp;
            pointer operator->() const; // Effects: return &(operator*());
            reverse_iterator& operator++(); // Effects: --current; Returns: *this
            reverse_iterator operator++(int); // Effects: reverse_iterator tmp = *this; --current; return tmp;
            reverse_iterator& operator--(); // Effects: ++current Returns: *this;
            reverse_iterator operator--(int); // Effects: reverse_iterator tmp = *this; ++current; return tmp;
            reverse_iterator operator+ (difference_type n) const; // Returns: reverse_iterator(current-n)
            reverse_iterator& operator+=(difference_type n); // Effects: current -= n; Returns: *this
            reverse_iterator operator- (difference_type n) const; // Returns: reverse_iterator(current+n)
            reverse_iterator& operator-=(difference_type n); // Effects: current += n; Returns: *this
            reference operator[](difference_type n) const; // Returns: current[-n-1]
    };

    template <class Iterator>
    bool operator==( const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y); // Returns: x.current == y.current
    template <class Iterator>
    bool operator<( const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y); // Returns: x.current > y.current
    template <class Iterator>
    bool operator!=( const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y); // Returns: x.current != y.current
    template <class Iterator>
    bool operator>( const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y); // Returns: x.current < y.current
    template <class Iterator>
    bool operator>=( const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y); // Returns: x.current <= y.current
    template <class Iterator>
    bool operator<=( const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y); // Returns: x.current >= y.current
    template <class Iterator>
    typename reverse_iterator<Iterator>::difference_type operator-( const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y); // Returns: y.current - x.current  
    template <class Iterator>
    reverse_iterator<Iterator> operator+( typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& x); // Returns: reverse_iterator<Iterator> (x.current - n)
    
    template <class Container> class back_insert_iterator : public iterator<output_iterator_tag,void,void,void,void>
    {
        protected:
            Container*  container;
        public:
            typedef Container   container_type;
            explicit back_insert_iterator(Container& x); // Effects: Initializes container with &x.
            back_insert_iterator<Container>& operator=(typename Container::const_reference value); // Effects: container->push_back(value); Returns: *this. 
            back_insert_iterator<Container>& operator*(); // Returns: *this.
            back_insert_iterator<Container>& operator++(); // Returns: *this
            back_insert_iterator<Container> operator++(int); // Returns: *this
    };

    template <class Container>
    back_insert_iterator<Container> back_inserter(Container& x); // Returns: back_insert_iterator<Container>(x).
    
    template <class Container> class front_insert_iterator : public iterator<output_iterator_tag,void,void,void,void>
    {
        protected:
            Container*  container;
        public:
            typedef Container   container_type;
            explicit front_insert_iterator(Container& x); // Effects: Initializes container with &x
            front_insert_iterator<Container>& operator=(typename Container::const_reference value); // Effects: container->push_front(value); Returns: *this.
            front_insert_iterator<Container>& operator*(); // Returns: *this.
            front_insert_iterator<Container>& operator++(); // Returns: *this.
            front_insert_iterator<Container> operator++(int); // Returns: *this.
    };
    template <class Container>
    front_insert_iterator<Container> front_inserter(Container& x); // Returns: front_insert_iterator<Container>(x).
    
    template <class Container> class insert_iterator : public iterator<output_iterator_tag,void,void,void,void>
    {
        protected:
            Container*                      container;
            typename Container::iterator    iter;
        public:
            typedef Container container_type;
            insert_iterator(Container& x, typename Container::iterator i); // Effects: Initializes container with &x and iter with i
            insert_iterator<Container>& operator=(typename Container::const_reference value); // Effects: iter = container->insert(iter, value); ++iter; Returns: *this.
            insert_iterator<Container>& operator*(); // Returns: *this.
            insert_iterator<Container>& operator++(); // Returns: *this.
            insert_iterator<Container>& operator++(int); // Returns: *this.
    };
    template <class Container, class Iterator>
    insert_iterator<Container> inserter(Container& x, Iterator i); // Returns: insert_iterator<Container>(x,typename Container::iterator(i)).
    
    // 24.5, stream iterators:
    template <class T, class charT = char, class traits = std::char_traits<charT>,class Distance = ptrdiff_t>
    class istream_iterator : public iterator<input_iterator_tag, T, Distance, const T*, const T&>
    {
        public:
            typedef charT char_type 
            typedef traits traits_type;
            typedef basic_istream<charT,traits> istream_type;
            istream_iterator(); // Effects: Constructs the end-of-stream iterator.
            istream_iterator(istream_type& s);
            istream_iterator(const istream_iterator<T,charT,traits,Distance>& x);
            ~istream_iterator();
            const T& operator*() const;
            const T* operator->() const;
            istream_iterator<T,charT,traits,Distance>& operator++();
            istream_iterator<T,charT,traits,Distance> operator++(int);
            private:
                //basic_istream<charT,traits>* in_stream; exposition only
                //T value; exposition only
    };
    template <class T, class charT, class traits, class Distance>
    bool operator==(const istream_iterator<T,charT,traits,Distance>& x,
    const istream_iterator<T,charT,traits,Distance>& y);
    template <class T, class charT, class traits, class Distance>
    bool operator!=(const istream_iterator<T,charT,traits,Distance>& x,
    const istream_iterator<T,charT,traits,Distance>& y);
    /*
    template <class T, class charT = char, class traits = char_traits<charT> >
    class ostream_iterator;
    template<class charT, class traits = char_traits<charT> >
    class istreambuf_iterator;
    template <class charT, class traits>
    bool operator==(const istreambuf_iterator<charT,traits>& a,
    const istreambuf_iterator<charT,traits>& b);
    template <class charT, class traits>
    bool operator!=(const istreambuf_iterator<charT,traits>& a,
    const istreambuf_iterator<charT,traits>& b);
    template <class charT, class traits = char_traits<charT> >
    class ostreambuf_iterator;
    */
}


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


/*namespace ft
{
    //primitives:
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

    // end primitive;
}
*/
#endif