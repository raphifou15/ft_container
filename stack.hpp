#ifndef STACK_HPP
# define STACK_HPP

# include <iterator>
# include <vector>

namespace ft
{
    template <class T, class Container = std::vector<T> >
    class stack
    {
        public:
            typedef typename Container::value_type  value_type;
            typedef typename Container::size_type   size_type;
            typedef Container                       container_type;
        protected:
            Container                               c;
        public:
            explicit                                stack(const Container& = Container()) {}
            bool                                    empty() const { return c.empty(); }
            size_type                               size() const { return c.size(); }
            value_type&                             top() { return c.back(); }
            const value_type&                       top() const { return c.back(); }
            void                                    push(const value_type& x) { c.push_back(x); }
            void                                    pop() {c.pop_back(); }
            friend bool                             operator==(const stack<T, Container>& x, const stack<T, Container>& y)
            {
                return (x.c == y.c);
            }
            friend bool                             operator< (const stack<T, Container>& x, const stack<T, Container>& y)
            {
                return (x.c < y.c);
            }
    };

    template <class T, class Container>
    bool    operator!=(const stack<T, Container>& x, const stack<T, Container>& y)
    {
        return ((x == y) ? 0 : 1);
    }
    template <class T, class Container>
    bool    operator> (const stack<T, Container>& x, const stack<T, Container>& y)
    {
        return (y < x);
    }
    template <class T, class Container>
    bool    operator>=(const stack<T, Container>& x, const stack<T, Container>& y)
    {
        return ((y < x) || (x == y));
    }
    template <class T, class Container>
    bool    operator<=(const stack<T, Container>& x, const stack<T, Container>& y)
    {
        return ((x < y) || (x == y));
    }
}

#endif