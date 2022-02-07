#include "stack.hpp"
#include "vector.hpp"
#include "lexicographical_compare.hpp"
#include "iterator.hpp"
#include "enable_if.hpp"
#include "is_integral.hpp"
#include <stack>
#include <vector>
//#include <type_traits>
#include <iostream>

#define COLOR_GRAY  "\e[1;30m"
#define COLOR_GREEN  "\e[0;32m"
#define COLOR_END  "\e[0m"

int main(void)
{
   /* 
    {
        std::vector<int>::iterator it;
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
        ft::vector<int>::iterator it;
        ft::vector<int>::iterator it2;
        ft::vector<int>::reverse_iterator ot;
        ft::vector<int>::reverse_iterator ot2;
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
        la[1] = 2;
        it = la.begin();
        it = la.end();
        ot = la.rbegin();
        //it++;
        it2 = it;
        if (it2 == it)
            std::cout << "== fonctionne" << std::endl;
        if (ot == ot2)
            std::cout << "== fonctionne" << std::endl;
        std::cout << COLOR_GRAY << *ot << COLOR_END << std::endl;
    }*/

    /*
    {
        ft::vector<int>::reverse_iterator ot;
        std::vector<int>::reverse_iterator ot_true;

        std::vector<int> la_true;
        ft::vector<int> la;

        for (int i = 0; i < 20; i++)
        {
            la_true.push_back(i);
            la.push_back(i);
        }

        ot_true = la_true.rbegin();
        ot = la.rbegin();
        std::cout << COLOR_GREEN << la_true.capacity() << COLOR_END << std::endl;
        std::cout << COLOR_GREEN << la_true.size() << COLOR_END << std::endl;
        std::cout << COLOR_GRAY << la.capacity() << COLOR_END << std::endl;
        std::cout << COLOR_GRAY << la.size() << COLOR_END << std::endl;
    }
    */
   /*
   {
    std::vector<int> lala (4, 10);
    std::vector<int>::iterator it;
    lala.clear();
    
    std::cout << COLOR_GREEN << lala.capacity() << COLOR_END << std::endl;
    std::cout << COLOR_GREEN << lala.size() << COLOR_END << std::endl;
    std::cout <<  COLOR_GREEN << *(lala.begin()) << COLOR_END << std::endl;
   }
   */
  /*
  {
    std::vector<int> lala (2, 2);
    std::vector<int> lili (1, 1);
    lala.swap(lili);
    std::cout << COLOR_GREEN << lala.capacity() << COLOR_END << std::endl;
    std::cout << COLOR_GREEN << lala.size() << COLOR_END << std::endl;
  }
  */
 /*
    {
        ft::vector<int> lala(5, 5);
        ft::vector<int> lila(3, 3);

        const ft::vector<int>::iterator rapha = lala.begin();
        ft::vector<int> kiki(++(lala.begin()), (--lala.end()));
        

        lala = lila;
        std::cout << COLOR_GREEN << kiki.capacity() << COLOR_END << std::endl;
        std::cout << COLOR_GREEN << kiki.size() << COLOR_END << std::endl;
        std::cout << COLOR_GREEN << *rapha << COLOR_END << std::endl;


        std::vector<int> la(5, 5);
        std::vector<int> li(3, 3);

        const std::vector<int>::iterator raph = la.begin();
        std::vector<int> ki(++(la.begin()), --(la.end()));

        la = li;
        std::cout << COLOR_GREEN << ki.capacity() << COLOR_END << std::endl;
        std::cout << COLOR_GREEN << ki.size() << COLOR_END <<sstd::endl;
        std::cout << COLOR_GREEN << *raph << COLOR_END << std::endl;

        
    }
    */
   /*
   {
       
       ft::vector<int> raph;
       ft::vector<int> myd (4, 200);
       //std::vector<int>::iterator pk;

       raph.insert(raph.begin(), 3, 34);
       raph.insert(raph.begin() + 1, 3, 4);
       raph.insert(raph.begin(), myd.begin(), myd.end());
       ft::vector<int>::iterator lala =  raph.insert(raph.begin() + 2, 1);
       std::cout << COLOR_GREEN << raph.capacity() << COLOR_END << std::endl;
       for (size_t i = 0; i < raph.size(); i++)
       {
            std::cout << COLOR_GREEN << raph[i] << COLOR_END << std::endl;
       }

        std::cout << *lala << std::endl;

      // std::vector<int> lol (5, 100);
       std::vector<int> rapha;
       std::vector<int> my (4, 200);
       //std::vector<int>::iterator pk;
        
       rapha.insert(rapha.begin(), 3, 34);
       rapha.insert(rapha.begin() + 1, 3, 4);
       rapha.insert(rapha.begin(), my.begin(), my.end());
       
       std::vector<int>::iterator lalala = rapha.insert(rapha.begin() + 2, 1);
       std::cout << COLOR_GREEN << rapha.capacity() << COLOR_END << std::endl;
       for (size_t i = 0; i < rapha.size(); i++)
       {
            std::cout << COLOR_GREEN << rapha[i] << COLOR_END << std::endl;
       }
       std::cout << *lalala << std::endl;
   }*/
   {
        std::vector<int> rapha(3, 3);
        rapha.erase(rapha.begin(), rapha.end());
        std::cout << COLOR_GREEN << rapha.capacity() << COLOR_END << std::endl;
        std::cout << COLOR_GREEN << rapha.size() << COLOR_END << std::endl;
        for (int i = 0; i < 3; i++)
        {
            std::cout << *(rapha.begin() + i) << std::endl;  
        }
       
       std::cout << "--------------------------------" << std::endl;
        std::vector<int> raph(3, 3);
        raph.erase(raph.begin(), raph.end());
        std::cout << COLOR_GREEN << raph.capacity() << COLOR_END << std::endl;
        std::cout << COLOR_GREEN << raph.size() << COLOR_END << std::endl;
        for (int i = 0; i < 3; i++)
        {
            std::cout << *(raph.begin() + i) << std::endl;  
        }
   }
    return (0);
}