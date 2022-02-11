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
    

    /*

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
            typedef charT char_type; 
            typedef traits traits_type;
            typedef std::basic_istream<charT,traits> istream_type;
            istream_iterator(); // Effects: Constructs the end-of-stream iterator.
            istream_iterator(istream_type& s); // Effects: Initializes in_stream with s. value may be initialized during construction or the first time it is referenced.
            istream_iterator(const istream_iterator<T,charT,traits,Distance>& x); // Effects: Constructs a copy of x.
            ~istream_iterator(); // Effects: The iterator is destroyed.
            const T& operator*() const; // Returns: value
            const T* operator->() const; // Returns: &(operator*())
            istream_iterator<T,charT,traits,Distance>& operator++(); // Effects: *in_stream >> value; Returns: *this
            istream_iterator<T,charT,traits,Distance> operator++(int); // istream_iterator<T,charT,traits,Distance> tmp = *this; *in_stream >> value; return (tmp);
            private:
                //basic_istream<charT,traits>* in_stream; exposition only
                //T value; exposition only
    };
    template <class T, class charT, class traits, class Distance>
    bool operator==(const istream_iterator<T,charT,traits,Distance>& x, const istream_iterator<T,charT,traits,Distance>& y);
    template <class T, class charT, class traits, class Distance>
    bool operator!=(const istream_iterator<T,charT,traits,Distance>& x, const istream_iterator<T,charT,traits,Distance>& y);
    // Returns: (x.in_stream == y.in_stream)

    
    template <class T, class charT = char, class traits = std::char_traits<charT> >
    class ostream_iterator : public iterator<output_iterator_tag, void, void, void, void>
    {
        public:
            typedef charT char_type; 
            typedef traits traits_type;
            typedef std::basic_ostream<charT,traits> ostream_type;
            ostream_iterator(ostream_type& s); // Effects: Initializes out_stream with s and delim with null.
            ostream_iterator(ostream_type& s, const charT* delimiter); // Effects: Initializes out_stream with s and delim with delimiter.
            ostream_iterator(const ostream_iterator<T,charT,traits>& x); // Effects: Constructs a copy of x;
            ~ostream_iterator(); // Effects: The iterator is destroyed.
            ostream_iterator<T,charT,traits>& operator=(const T& value); // Effects: *out_stream << value; if(delim != 0) *out_stream << delim; return (*this);
            ostream_iterator<T,charT,traits>& operator*(); // Returns: *this
            ostream_iterator<T,charT,traits>& operator++(); // Returns: *this
            ostream_iterator<T,charT,traits>& operator++(int); // Returns: *this
        private:
            // basic_ostream<charT,traits>* out_stream; exposition only
            // const char* delim; exposition only
    };
    template<class charT, class traits = std::char_traits<charT> >
    class istreambuf_iterator : public iterator<input_iterator_tag, charT, typename traits::off_type, charT*, charT&>
    {
        public:
            typedef charT char_type;
            typedef traits traits_type;
            typedef typename traits::int_type int_type;
            typedef std::basic_streambuf<charT,traits> streambuf_type;
            typedef std::basic_istream<charT,traits> istream_type;
            class proxy; // exposition only
        public:
            istreambuf_iterator() throw(); // Effects: Constructs the end-of-stream iterator
            istreambuf_iterator(istream_type& s) throw(); // Effects: Constructs an istreambuf_iterator<> that uses the basic_streambuf<> object *(s.rdbuf()), or *s, respectively. Constructs an end-of-stream iterator if s.rdbuf() is null.
            istreambuf_iterator(streambuf_type* s) throw(); // Effects: Constructs an istreambuf_iterator<> that uses the basic_streambuf<> object *(s.rdbuf()), or *s, respectively. Constructs an end-of-stream iterator if s.rdbuf() is null.
            istreambuf_iterator(const proxy& p) throw(); // Effects: Constructs a istreambuf_iterator<> that uses the basic_streambuf<> object pointed to by the proxy object’s constructor argument p
            charT operator*() const; // Returns: The character obtained via the streambuf member sbuf_->sgetc().
            istreambuf_iterator<charT,traits>& operator++(); // Effects: sbuf_->sbumpc(). Returns: *this.
            proxy operator++(int); // Returns: proxy(sbuf_->sbumpc(), sbuf_). istreambuf_iterator<charT,traits> tmp = *this; sbuf_->sbumpc(); return(tmp);
            bool equal(istreambuf_iterator& b); // Returns: true if and only if both iterators are at end-of-stream, or neither is at end-of-stream, regardless of what streambuf object they use.
        private:
            streambuf_type* sbuf_; //exposition only
    };

    template <class charT, class traits>
    bool operator==(const istreambuf_iterator<charT,traits>& a, const istreambuf_iterator<charT,traits>& b); // Returns: a.equal(b)
    template <class charT, class traits>
    bool operator!=(const istreambuf_iterator<charT,traits>& a, const istreambuf_iterator<charT,traits>& b); // Returns: !a.equal(b).
    
    template <class charT, class traits = std::char_traits<charT> >
    class ostreambuf_iterator : public iterator<output_iterator_tag, void, void, void, void>
    {
        public:
            typedef charT char_type;
            typedef traits traits_type;
            typedef std::basic_streambuf<charT,traits> streambuf_type;
            typedef std::basic_ostream<charT,traits> ostream_type;
        public:
            ostreambuf_iterator(ostream_type& s) throw(); // Requires: s is not null Effects: : sbuf_(s.rdbuf()) {}
            ostreambuf_iterator(streambuf_type* s) throw(); // Effects: : sbuf_(s) {}
            ostreambuf_iterator& operator=(charT c); // Effects: If failed() yields false, calls sbuf_->sputc(c); otherwise has no effect Returns: *this.
            ostreambuf_iterator& operator*(); // Returns: *this.
            ostreambuf_iterator& operator++(); // Returns: *this.
            ostreambuf_iterator& operator++(int); // Returns: *this.
            bool failed() const throw(); // Returns: true if in any prior use of member operator=, the call to sbuf_->sputc() returned traits::eof(); or false otherwise.
        private:
            streambuf_type* sbuf_; // exposition only
    };
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