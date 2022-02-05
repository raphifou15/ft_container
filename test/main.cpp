#include <vector>
#include <iostream>
/*
struct Test
{
  typedef int foo;
};

template <typename T>
void f(typename T::foo) { std::cout << "1" << std::endl;}  // Definition #1

template <typename T>
void f(T) {std::cout << "2" << std::endl;}  // Definition #2

int main(void)
{
    f<Test>(10);  // Call #1.
    f<int>(10);   // Call #2. Without error (even though there is no int::foo)
                // thanks to SFINAE.
    }
    return 0;
}
*/

template <typename T>
struct has_typedef_foobar
{
    // Types "yes" and "no" are guaranteed to have different sizes,
    // specifically sizeof(yes) == 1 and sizeof(no) == 2.
    typedef char yes[1];
    typedef char no[2];

    template <typename U>
    static no& test(U);

    template <typename C>
    static yes& test(typename C::foobar*);

    template <typename>
    static yes& test(...);

    // If the "sizeof" of the result of calling test<T>(nullptr) is equal to
    // sizeof(yes), the first overload worked and T has a nested type named
    // foobar.
    static const bool value = sizeof(test<T>(NULL)) == sizeof(yes);
};

struct foo
{
  typedef float foobar;
};

int main() {
  std::cout << std::boolalpha;
  std::cout << has_typedef_foobar<int>::value << std::endl;  // Prints false
  std::cout << has_typedef_foobar<foo>::value << std::endl;  // Prints true
}