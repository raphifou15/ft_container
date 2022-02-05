#ifndef IS_INTEGRAL_HPP
# define IS_INTEGRAL_HPP

# include "iterator.hpp"
namespace ft
{
    template <class T, T v>
    struct integral_constant
    {
        static const T value = v;
        typedef T value_type;
        typedef integral_constant<T,v> type;
        operator T() const { return v; }
    };

    template <class T> struct is_integral : public integral_constant<bool, false>{};

    template <> struct is_integral<bool> : public integral_constant<bool, true>{};
    template <> struct is_integral<char> : public integral_constant<bool, true>{};
    template <> struct is_integral<wchar_t> : public integral_constant<bool, true>{};
    template <> struct is_integral<signed char> : public integral_constant<bool, true>{};
    template <> struct is_integral<short int> : public integral_constant<bool, true>{};
    template <> struct is_integral<int> : public integral_constant<bool, true>{};
    template <> struct is_integral<long int> : public integral_constant<bool, true>{};
    template <> struct is_integral<long long int> : public integral_constant<bool, true>{};
    template <> struct is_integral<unsigned char> : public integral_constant<bool, true>{};
    template <> struct is_integral<unsigned short int> : public integral_constant<bool, true>{};
    template <> struct is_integral<unsigned int> : public integral_constant<bool, true>{};
    template <> struct is_integral<unsigned long int> : public integral_constant<bool, true>{};
    template <> struct is_integral<unsigned long long int> : public integral_constant<bool, true>{};
}
# endif