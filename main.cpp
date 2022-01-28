#include "stack.hpp"
#include "vector.hpp"
#include "lexicographical_compare.hpp"
#include "iterator.hpp"
#include <stack>
#include <vector>
#include <iostream>

#define COLOR_GRAY  "\e[1;30m"
#define COLOR_GREEN  "\e[0;32m"
#define COLOR_END  "\e[0m"

int main(void)
{
    
    {
        std::vector<int> la (4, 100);
        std::vector<int> lou;
        for (int i = 0 ; i < 4; i++)
            std::cout << la[i] << std::endl;
        try
        {
            std::cout << COLOR_GREEN << "at: " << la.at(4) << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        std::cout << COLOR_GREEN << "at: " << la.at(1) << std::endl;
        std::cout << COLOR_GREEN << lou.size() << COLOR_END << std::endl;
        std::cout << COLOR_GREEN << lou.max_size() << COLOR_END << std::endl;
        std::cout << COLOR_GREEN << lou.capacity() << COLOR_END << std::endl;
        std::cout << COLOR_GREEN << lou.empty() << COLOR_END << std::endl;
        try
        {
            lou.reserve(2305843009213693952);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        lou.reserve(5);
        lou.resize(10);
        std::cout << COLOR_GREEN << lou.capacity() << COLOR_END << std::endl;
        std::cout << COLOR_GREEN << lou.size() << COLOR_END << std::endl;
        std::cout << COLOR_GREEN << la.front() << COLOR_END << std::endl;
    }

    {
        ft::vector<int> la (4, 100);
        ft::vector<int> lou;

        for (int i = 0 ; i < 4; i++)
            std::cout << la[i] << std::endl;
        try
        {
            std::cout << COLOR_GRAY << "at: " << la.at(4) << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        std::cout << COLOR_GRAY << "at: " << la.at(1) << std::endl;
        std::cout << COLOR_GRAY << lou.size() << COLOR_END << std::endl;
        std::cout << COLOR_GRAY << lou.max_size() << COLOR_END << std::endl;
        std::cout << COLOR_GRAY << lou.capacity() << COLOR_END << std::endl;
        std::cout << COLOR_GRAY << lou.empty() << COLOR_END << std::endl;
        try
        {
            lou.reserve(2305843009213693952);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        lou.reserve(5);
        lou.resize(10);
        std::cout << COLOR_GRAY << lou.capacity() << COLOR_END << std::endl;
        std::cout << COLOR_GRAY << lou.size() << COLOR_END << std::endl;
        std::cout << COLOR_GRAY << la.front() << COLOR_END << std::endl;
    }
    return (0);
}