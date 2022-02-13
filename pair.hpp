#ifndef PAIR
# define PAIR

namespace ft
{
    template <class T1, class T2>
    struct pair
    {
        typedef T1 first_type;
        typedef T2 second_type;
        T1 first;
        T2 second;
        pair() : first(), second() {}
        pair(const T1& x, const T2& y) : first(x), second(y) {}
        template<class U, class V> pair(const pair<U, V> &p) : first(p.first), second(p.second) {}
        pair& operator=(const pair& p)
        {
            this->first = p.first;
            this->second = p.second;
            return(*this);
        }
    };
    template <class T1, class T2> bool operator==(const pair<T1, T2>& x, const pair<T1, T2>& y)
    {
        return ((x.first == y.first) && (x.second == y.second));
    }

    template <class T1, class T2> bool operator<(const pair<T1, T2>& x, const pair<T1, T2>& y)
    {
        return (x.first < y.first || (!(y.first < x.first) && x.second < y.second));
    }

    template <class T1, class T2> bool operator!=(const pair<T1, T2>& x, const pair<T1, T2>& y)
    {
        return (!(x == y));
    }

    template <class T1, class T2> bool operator<=(const pair<T1, T2>& x, const pair<T1, T2>& y)
    {
        return (!(y < x));
    }

    template <class T1, class T2> bool operator>(const pair<T1, T2>& x, const pair<T1, T2>& y)
    {
        return (y < x);
    }

    template <class T1, class T2> bool operator>=(const pair<T1, T2>& x, const pair<T1, T2>& y)
    {
        return (!(x < y));
    }

    template <class T1, class T2> pair<T1, T2> make_pair(const T1& x, const T2& y)
    {
        return pair<T1, T2>(x, y);
    }
}

#endif