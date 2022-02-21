#include "stack.hpp"
#include "map.hpp"
#include "pair.hpp"
#include "vector.hpp"
#include "lexicographical_compare.hpp"
#include "iterator.hpp"
#include "enable_if.hpp"
#include "is_integral.hpp"
#include <stack>
#include <vector>
#include <map>
#include <list>
//#include <type_traits>
#include <iostream>
# include <stdexcept>
#define TESTED_TYPE int

#define COLOR_GRAY  "\e[1;30m"
#define COLOR_GREEN  "\e[0;32m"
#define COLOR_BLUE	"\e[0;34m"
#define COLOR_END  "\e[0m"
/*
int main()
{
	{
		std::vector<int>			test(3, 3);

		std::cout << "self assignation test\n";
		std::vector<std::vector<int> >	self_assign;
		std::vector<std::vector<int> >	*ptr = &self_assign;
		std::vector<std::vector<int> >	*ptr2 = &self_assign;

		self_assign.assign(4, test);
		*ptr = *ptr2;

		std::cout << COLOR_GREEN << std::boolalpha << (*ptr == *ptr2) << COLOR_END << '\n' ;
		//	self_assign = self_assign; //compiler doesn't like it!

		std::cout << COLOR_BLUE << "test 2" << COLOR_END << std::endl;

		std::vector<std::vector<int> > JOHN;
		std::vector<std::vector<int> > BOB(5, test);
		std::cout << "BOB(5, test(test, 5)) : \n";
		for (size_t i = 0; i < BOB.size(); i++)
		{
			for (size_t j = 0; j < BOB[i].size(); j++)
				std::cout << BOB[i][j] << ' ';
			std::cout << '\n';
		}
		std::vector<std::vector<int> > MIKE(BOB);

		// CTORs
		std::cout << COLOR_BLUE << "test 3" << COLOR_END << std::endl;
		std::cout << "\nCTORS\n";
		std::cout << "Empty is empty ? " << std::boolalpha << JOHN.empty() << '\n';
		std::cout << "BOB is empty? " << BOB.empty() << '\n';

		std::cout << "Size of JOHN " << JOHN.size() << std::endl;
		std::cout << "Size of BOB " << BOB.size() << std::endl;
		std::cout << "Size of MIKE " << MIKE.size() << std::endl;
		// RESIZE
		std::cout << COLOR_BLUE << "test 4" << COLOR_END << std::endl;
		size_t	bob_resize = 2;
		std::cout << "\nRESIZE\n";
		BOB.resize(bob_resize);
		std::cout << "Size of JOHN " << JOHN.size() << std::endl;
		if (JOHN.capacity() >= JOHN.size())
			std::cout << "Capacity of JOHN is sufficient\n";
		else
			std::cerr << "THERE IS A PROBLEM ON LINE 53\n";
		std::cout << "Size of BOB " << BOB.size() << std::endl;
		if (BOB.capacity() >= bob_resize)
			std::cout << "Capacity of BOB is sufficient\n";
		else
			std::cerr << "THERE IS A PROBLEM ON LINE 58\n";
		std::cout << "Size of MIKE " << MIKE.size() << std::endl;
		if (MIKE.capacity() >= MIKE.size())
			std::cout << "Capacity of MIKE is sufficient\n";
		else
			std::cerr << "THERE IS A PROBLEM ON LINE 63\n";

		size_t	mike_resize = 9;
		bob_resize = 0;
	
		BOB.resize(bob_resize);
		std::cout << "BOB is empty now ? " << BOB.empty() << '\n';
		MIKE.resize(mike_resize, test);
		std::cout << "Size of JOHN " << JOHN.size() << std::endl;
		if (JOHN.capacity() >= JOHN.size())
			std::cout << "Capacity of JOHN is sufficient\n";
		else
			std::cerr << "THERE IS A PROBLEM ON LINE 86\n";
		std::cout << "Size of BOB " << BOB.size() << std::endl;
		if (BOB.capacity() >= bob_resize)
			std::cout << "Capacity of BOB is sufficient\n";
		else
			std::cerr << "THERE IS A PROBLEM ON LINE 91\n";
		std::cout << "Size of MIKE " << MIKE.size() << std::endl;
		if (MIKE.capacity() >= mike_resize)
			std::cout << "Capacity of MIKE is sufficient\n";
		else
			std::cerr << "THERE IS A PROBLEM ON LINE 96\n";
		for (size_t i = 0; i < MIKE.size(); i++)
		{
			for (size_t j = 0; j < MIKE[i].size(); j++)
			{
				std::cout << MIKE[i][j] << ' ';
			}
			std::cout << std::endl;
		}
		// RESERVE
		std::cout << COLOR_BLUE << "test 5" << COLOR_END << std::endl;
		std::cout << "\nRESERVE\n";

		size_t	john_reserve = 0;
		size_t	bob_reserve = 3;
		size_t	mike_reserve = 4;

		JOHN.reserve(john_reserve);
		BOB.reserve(bob_reserve);
		MIKE.reserve(mike_reserve);
		std::cout << "Size of JOHN " << JOHN.size() << std::endl;
		if (JOHN.capacity() >= john_reserve)
			std::cout << "Capacity of JOHN is sufficient\n";
		else
			std::cerr << "THERE IS A PROBLEM ON LINE 120\n";
		std::cout << "Size of BOB " << BOB.size() << std::endl;
		if (BOB.capacity() >= bob_reserve)
			std::cout << "Capacity of BOB is sufficient\n";
		else
			std::cerr << "THERE IS A PROBLEM ON LINE 125\n";
		std::cout << "Size of MIKE " << MIKE.size() << std::endl;
		if (MIKE.capacity() >= mike_reserve)
			std::cout << "Capacity of MIKE is sufficient\n";
		else
			std::cerr << "THERE IS A PROBLEM ON LINE 130\n";
		for (size_t i = 0; i < MIKE.size(); i++)
		{
			for (size_t j = 0; j < MIKE[i].size(); j++)
				std::cout << MIKE[i][j] << ' ';
			std::cout << std::endl;
		}
		//AT
		std::cout << COLOR_BLUE << "test 6" << COLOR_END << std::endl;
		std::cout << "\nAT\n";
		
		try
		{
			std::cout << MIKE.at(2).front() << '\n';
			std::cout << MIKE.at(87).back() << '\n';
		}
		catch (std::out_of_range& oor)
		{
			(void)oor;
			std::cout << "OOR error caught\n";
		}
		
	}

	std::cout << COLOR_BLUE << std::endl << "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\" << COLOR_END << std::endl; 
	
	{
		ft::vector<int>			test(3, 3);

		std::cout << "self assignation test\n";
		ft::vector<ft::vector<int> >	self_assign;
		ft::vector<ft::vector<int> >	*ptr = &self_assign;
		ft::vector<ft::vector<int> >	*ptr2 = &self_assign;

		self_assign.assign(4, test);
		*ptr = *ptr2;

		std::cout << COLOR_GREEN << std::boolalpha << (*ptr == *ptr2) << COLOR_END << '\n' ;
		
		//	self_assign = self_assign; //compiler doesn't like it!
		std::cout << COLOR_BLUE << "test 2" << COLOR_END << std::endl;

		ft::vector<ft::vector<int> > JOHN;
		ft::vector<ft::vector<int> > BOB(5, test);
		std::cout << "BOB(5, test(test, 5)) : \n";
		for (size_t i = 0; i < BOB.size(); i++)
		{
			for (size_t j = 0; j < BOB[i].size(); j++)
				std::cout << BOB[i][j] << ' ';
			std::cout << '\n';
		}
		ft::vector<ft::vector<int> > MIKE(BOB);
		// CTORs
		std::cout << COLOR_BLUE << "test 3" << COLOR_END << std::endl;
		std::cout << "\nCTORS\n";
		std::cout << "Empty is empty ? " << std::boolalpha << JOHN.empty() << '\n';
		std::cout << "BOB is empty? " << BOB.empty() << '\n';

		std::cout << "Size of JOHN " << JOHN.size() << std::endl;
		std::cout << "Size of BOB " << BOB.size() << std::endl;
		std::cout << "Size of MIKE " << MIKE.size() << std::endl;
				// RESIZE
		std::cout << COLOR_BLUE << "test 4" << COLOR_END << std::endl;
		size_t	bob_resize = 2;
		std::cout << "\nRESIZE\n";
		BOB.resize(bob_resize);
		std::cout << "Size of JOHN " << JOHN.size() << std::endl;
		if (JOHN.capacity() >= JOHN.size())
			std::cout << "Capacity of JOHN is sufficient\n";
		else
			std::cerr << "THERE IS A PROBLEM ON LINE 53\n";
		std::cout << "Size of BOB " << BOB.size() << std::endl;
		if (BOB.capacity() >= bob_resize)
			std::cout << "Capacity of BOB is sufficient\n";
		else
			std::cerr << "THERE IS A PROBLEM ON LINE 58\n";
		std::cout << "Size of MIKE " << MIKE.size() << std::endl;
		if (MIKE.capacity() >= MIKE.size())
			std::cout << "Capacity of MIKE is sufficient\n";
		else
			std::cerr << "THERE IS A PROBLEM ON LINE 63\n";

		size_t	mike_resize = 9;
		bob_resize = 0;
	
		BOB.resize(bob_resize);
		std::cout << "BOB is empty now ? " << BOB.empty() << '\n';
		MIKE.resize(mike_resize, test);
		std::cout << "Size of JOHN " << JOHN.size() << std::endl;
		if (JOHN.capacity() >= JOHN.size())
			std::cout << "Capacity of JOHN is sufficient\n";
		else
			std::cerr << "THERE IS A PROBLEM ON LINE 86\n";
		std::cout << "Size of BOB " << BOB.size() << std::endl;
		if (BOB.capacity() >= bob_resize)
			std::cout << "Capacity of BOB is sufficient\n";
		else
			std::cerr << "THERE IS A PROBLEM ON LINE 91\n";
		std::cout << "Size of MIKE " << MIKE.size() << std::endl;
		if (MIKE.capacity() >= mike_resize)
			std::cout << "Capacity of MIKE is sufficient\n";
		else
			std::cerr << "THERE IS A PROBLEM ON LINE 96\n";
		for (size_t i = 0; i < MIKE.size(); i++)
		{
			for (size_t j = 0; j < MIKE[i].size(); j++)
			{
				std::cout << MIKE[i][j] << ' ';
			}
			std::cout << std::endl;
		}
		// RESERVE
		std::cout << COLOR_BLUE << "test 5" << COLOR_END << std::endl;
		std::cout << "\nRESERVE\n";

		size_t	john_reserve = 0;
		size_t	bob_reserve = 3;
		size_t	mike_reserve = 4;

		JOHN.reserve(john_reserve);
		BOB.reserve(bob_reserve);
		MIKE.reserve(mike_reserve);
		std::cout << "Size of JOHN " << JOHN.size() << std::endl;
		if (JOHN.capacity() >= john_reserve)
			std::cout << "Capacity of JOHN is sufficient\n";
		else
			std::cerr << "THERE IS A PROBLEM ON LINE 120\n";
		std::cout << "Size of BOB " << BOB.size() << std::endl;
		if (BOB.capacity() >= bob_reserve)
			std::cout << "Capacity of BOB is sufficient\n";
		else
			std::cerr << "THERE IS A PROBLEM ON LINE 125\n";
		std::cout << "Size of MIKE " << MIKE.size() << std::endl;
		if (MIKE.capacity() >= mike_reserve)
			std::cout << "Capacity of MIKE is sufficient\n";
		else
			std::cerr << "THERE IS A PROBLEM ON LINE 130\n";
		for (size_t i = 0; i < MIKE.size(); i++)
		{
			for (size_t j = 0; j < MIKE[i].size(); j++)
				std::cout << MIKE[i][j] << ' ';
			std::cout << std::endl;
		}
		//AT
		std::cout << COLOR_BLUE << "test 6" << COLOR_END << std::endl;
		std::cout << "\nAT\n";
		try
		{
			std::cout << MIKE.at(2).front() << '\n';
			std::cout << MIKE.at(87).back() << '\n';
		}
		catch (std::out_of_range& oor)
		{
			(void)oor;
			std::cout << "OOR error caught\n";
		}
	}
	return (0);
}
*/
/*
void	prepost_incdec(std::vector<TESTED_TYPE> &vct)
{
	std::vector<TESTED_TYPE>::iterator it = vct.begin();
	std::vector<TESTED_TYPE>::iterator it_tmp;

	std::cout << "Pre inc" << std::endl;
	it_tmp = ++it;
	std::cout << *it_tmp << " | " << *it << std::endl;

	std::cout << "Pre dec" << std::endl;
	it_tmp = --it;
	std::cout << *it_tmp << " | " << *it << std::endl;

	std::cout << "Post inc" << std::endl;
	it_tmp = it++;
	std::cout << *it_tmp << " | " << *it << std::endl;

	std::cout << "Post dec" << std::endl;
	it_tmp = it--;
	std::cout << *it_tmp << " | " << *it << std::endl;
	std::cout << "###############################################" << std::endl;
}

void	prepost_incdec2(ft::vector<TESTED_TYPE> &vct)
{
	ft::vector<TESTED_TYPE>::iterator it = vct.begin();
	ft::vector<TESTED_TYPE>::iterator it_tmp;

	std::cout << "Pre inc" << std::endl;
	it_tmp = ++it;
	std::cout << *it_tmp << " | " << *it << std::endl;

	std::cout << "Pre dec" << std::endl;
	it_tmp = --it;
	std::cout << *it_tmp << " | " << *it << std::endl;

	std::cout << "Post inc" << std::endl;
	it_tmp = it++;
	std::cout << *it_tmp << " | " << *it << std::endl;

	std::cout << "Post dec" << std::endl;
	it_tmp = it--;
	std::cout << *it_tmp << " | " << *it << std::endl;
	std::cout << "###############################################" << std::endl;
}
*/

/*
int main()
{
    {
        const int size = 5;
	    std::vector<TESTED_TYPE> vct(size);
	    std::vector<TESTED_TYPE>::iterator it = vct.begin();
	    std::vector<TESTED_TYPE>::const_iterator ite = vct.begin();

	    for (int i = 0; i < size; ++i)
		    it[i] = (size - i) * 5;
	    prepost_incdec(vct);

	    it = it + 5;
	    it = 1 + it;
	    it = it - 4;
	    std::cout << *(it += 2) << std::endl;
	    std::cout << *(it -= 1) << std::endl;

	    *(it -= 2) = 42;
	    *(it += 2) = 21;

	    std::cout << "const_ite +=: " << *(ite += 2) << std::endl;
	    std::cout << "const_ite -=: " << *(ite -= 2) << std::endl;

	    std::cout << "(it == const_it): " << (ite == it) << std::endl;
	    std::cout << "(const_ite - it): " << (ite - it) << std::endl;
	    std::cout << "(ite + 3 == it): " << (ite + 3 == it) << std::endl;

	    std::cout << vct.size() << std::endl;
    }
    std::cout << "//////////////////////////////////////////" << std::endl;
    {
        const int size = 5;
	    ft::vector<TESTED_TYPE> vct(size);
	    ft::vector<TESTED_TYPE>::iterator it = vct.begin();
	    ft::vector<TESTED_TYPE>::const_iterator ite = vct.begin();

	    for (int i = 0; i < size; ++i)
		    it[i] = (size - i) * 5;
	    prepost_incdec2(vct);

	    it = it + 5;
	    it = 1 + it;
	    it = it - 4;
	    std::cout << *(it += 2) << std::endl;
	    std::cout << *(it -= 1) << std::endl;

	    *(it -= 2) = 42;
	    *(it += 2) = 21;

	    std::cout << "const_ite +=: " << *(ite += 2) << std::endl;
	    std::cout << "const_ite -=: " << *(ite -= 2) << std::endl;

	    std::cout << "(it == const_it): " << (ite == it) << std::endl;
	    std::cout << "(const_ite - it): " << (ite - it) << std::endl;
	    std::cout << "(ite + 3 == it): " << (ite + 3 == it) << std::endl;

	    std::cout << vct.size() << std::endl;
    }
    return (0);
}
*/
/*

        void	checkErase(std::vector<TESTED_TYPE> const &vct,
					std::vector<TESTED_TYPE>::const_iterator const &it)
        {
	        static int i = 0;
	        std::cout << "[" << i++ << "] " << "erase: " << it - vct.begin() << std::endl;
	        std::cout << vct.size() << std::endl;
        }
        void	checkErase2(ft::vector<TESTED_TYPE> const &vct,
					ft::vector<TESTED_TYPE>::const_iterator const &it)
        {
	        static int i = 0;
	        std::cout << "[" << i++ << "] " << "erase: " << it - vct.begin() << std::endl;
	        std::cout << vct.size() << std::endl;
        }
*/


/*
int main()
{
    
        {
	    std::vector<TESTED_TYPE> vct(10);

	    for (unsigned long int i = 0; i < vct.size(); ++i)
		    vct[i] = std::string((vct.size() - i), i + 65);

	    //printSize(vct);

	    checkErase(vct, vct.erase(vct.begin() + 2));

	    checkErase(vct, vct.erase(vct.begin()));
	    checkErase(vct, vct.erase(vct.end() + 1));

        
	    checkErase(vct, vct.erase(vct.begin(), vct.begin() + 3));
	    checkErase(vct, vct.erase(vct.end() - 3, vct.end() - 1));

	    vct.push_back("Hello");
	    vct.push_back("Hi there");
	    //printSize(vct);
	    checkErase(vct, vct.erase(vct.end() - 3, vct.end()));

	    vct.push_back("ONE");
	    vct.push_back("TWO");
	    vct.push_back("THREE");
	    vct.push_back("FOUR");
	    //printSize(vct);
	    checkErase(vct, vct.erase(vct.begin(), vct.end()));
        
        }

        std::cout << "////////////////////" << std::endl;
        
        {
	    ft::vector<TESTED_TYPE> vct(10);

	    for (unsigned long int i = 0; i < vct.size(); ++i)
		    vct[i] = std::string((vct.size() - i), i + 65);
            
	    //printSize(vct);
        
	    checkErase2(vct, vct.erase(vct.begin() + 2));

	    checkErase2(vct, vct.erase(vct.begin()));
	    checkErase2(vct, vct.erase(vct.end() + 1));
        
    
	    checkErase2(vct, vct.erase(vct.begin(), vct.begin() + 3));
        
	    checkErase2(vct, vct.erase(vct.end() - 3, vct.end() - 1));

	    vct.push_back("Hello");
	    vct.push_back("Hi there");
	    //printSize(vct);
	    checkErase2(vct, vct.erase(vct.end() - 3, vct.end()));

	    vct.push_back("ONE");
	    vct.push_back("TWO");
	    vct.push_back("THREE");
	    vct.push_back("FOUR");
	    //printSize(vct);
	    checkErase2(vct, vct.erase(vct.begin(), vct.end()));
        
        }
    return (0);
}
*/
/*
int main(void)
{
    */
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
   /*
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
   */
  /*
  {
    {
	ft::vector<int> vct(7);

	for (unsigned long int i = 0; i < vct.size(); ++i)
	{
		vct.at(i) = (vct.size() - i) * 3;
		std::cout << "vct[]: " << vct[i] << std::endl;
	}
	std::cout << vct.size() << std::endl;

	ft::vector<int> const vct_c(vct);

	std::cout << "front(): " << vct.front() << " " << vct_c.front() << std::endl;
	std::cout << "back(): " << vct.back() << " " <<  vct_c.back() << std::endl;

	for (unsigned long int i = 0; i < vct_c.size(); ++i)
		std::cout << "vct_c.at(): " << vct_c.at(i) << std::endl;
	try {
		std::cout << vct_c.at(10) << std::endl;
	}
	catch (std::out_of_range &e) {
		std::cout << "Catch out_of_range exception!" << std::endl;
	}
	catch (std::exception &e) {
		std::cout << "Catch exception: " << e.what() << std::endl;
	}
	std::cout << vct_c.size() << std::endl;
    }
    std::cout << "/////////////////////////////" << std::endl;
    {
	std::vector<int> vct(7);

	for (unsigned long int i = 0; i < vct.size(); ++i)
	{
		vct.at(i) = (vct.size() - i) * 3;
		std::cout << "vct[]: " << vct[i] << std::endl;
	}
	std::cout << vct.size() << std::endl;

	std::vector<int> const vct_c(vct);

	std::cout << "front(): " << vct.front() << " " << vct_c.front() << std::endl;
	std::cout << "back(): " << vct.back() << " " <<  vct_c.back() << std::endl;

	for (unsigned long int i = 0; i < vct_c.size(); ++i)
		std::cout << "vct_c.at(): " << vct_c.at(i) << std::endl;
	try {
		std::cout << vct_c.at(10) << std::endl;
	}
	catch (std::out_of_range &e) {
		std::cout << "Catch out_of_range exception!" << std::endl;
	}
	catch (std::exception &e) {
		std::cout << "Catch exception: " << e.what() << std::endl;
	}
	std::cout << vct_c.size() << std::endl;
    }
  }
  */
 /*

}

*/
//#define TESTED_TYPE int
/*
int		main(void)
{
    {
	std::list<TESTED_TYPE> lst;
	std::list<TESTED_TYPE>::iterator lst_it;
	for (int i = 1; i < 5; ++i)
		lst.push_back(i * 3);

	ft::vector<TESTED_TYPE> vct(lst.begin(), lst.end());
	std::cout << vct.size() << std::endl;

	lst_it = lst.begin();
	for (int i = 1; lst_it != lst.end(); ++i)
		*lst_it++ = i * 5;
	vct.assign(lst.begin(), lst.end());
	std::cout << vct.size() << std::endl;

	vct.insert(vct.end(), lst.rbegin(), lst.rend());
	std::cout << vct.size() << std::endl;
    }

    {
	std::list<TESTED_TYPE> lst;
	std::list<TESTED_TYPE>::iterator lst_it;
	for (int i = 1; i < 5; ++i)
		lst.push_back(i * 3);

	std::vector<TESTED_TYPE> vct(lst.begin(), lst.end());
	std::cout << vct.size() << std::endl;

	lst_it = lst.begin();
	for (int i = 1; lst_it != lst.end(); ++i)
		*lst_it++ = i * 5;
	vct.assign(lst.begin(), lst.end());
	std::cout << vct.size() << std::endl;

	vct.insert(vct.end(), lst.rbegin(), lst.rend());
	std::cout << vct.size() << std::endl;
    }
    return (0);
}
*/
/*
int		main(void)
{
    {
	std::vector<TESTED_TYPE> vct(10);
    std::vector<TESTED_TYPE> vct2;

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = (vct.size() - i) * 3;
	std::cout << vct.size() << std::endl;

	vct2.insert(vct2.end(), 42);
	vct2.insert(vct2.begin(), 2, 21);
	std::cout << vct2.size() << std::endl;

	vct2.insert(vct2.end() - 2, 42);
	std::cout << vct2.size() << std::endl;

	vct2.insert(vct2.end(), 2, 84);
	std::cout << vct2.size() << std::endl;

	vct2.resize(4);
	std::cout << vct2.size() << std::endl;

	vct2.insert(vct2.begin() + 2, vct.begin(), vct.end());
	vct.clear();
	std::cout << vct2.size() << std::endl;

	std::cout << vct.size() << std::endl;
    }

    std::cout << "/////////////////////////////////////////////////////////////////" << std::endl;

    {
    ft::vector<TESTED_TYPE> vct(10);
    ft::vector<TESTED_TYPE> vct2;

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = (vct.size() - i) * 3;
	std::cout << vct.size() << std::endl;

	vct2.insert(vct2.end(), 42);
	vct2.insert(vct2.begin(), 2, 21);
	std::cout << vct2.size() << std::endl;

	vct2.insert(vct2.end() - 2, 42);
	std::cout << vct2.size() << std::endl;

	vct2.insert(vct2.end(), 2, 84);
	std::cout << vct2.size() << std::endl;

	vct2.resize(4);
	std::cout << vct2.size() << std::endl;

	vct2.insert(vct2.begin() + 2, vct.begin(), vct.end());
	vct.clear();
	std::cout << vct2.size() << std::endl;

	std::cout << vct.size() << std::endl;
    }
	return (0);
}
*/
/*
#define TESTED_TYPE int

int		main(void)
{
    {
	const int size = 5;
	std::vector<TESTED_TYPE> vct(size);
	std::vector<TESTED_TYPE>::iterator it(vct.begin());
	std::vector<TESTED_TYPE>::const_iterator ite(vct.end());

	for (int i = 1; it != ite; ++i)
		*it++ = i;
    std::cout << vct.size() << std::endl;

	it = vct.begin();
	ite = vct.begin();

	std::cout << *(++ite) << std::endl;
	std::cout << *(ite++) << std::endl;
	std::cout << *ite++ << std::endl;
	std::cout << *++ite << std::endl;

	//it->m();
	//ite->m();

	std::cout << *(++it) << std::endl;
	std::cout << *(it++) << std::endl;
	std::cout << *it++ << std::endl;
	std::cout << *++it << std::endl;

	std::cout << *(--ite) << std::endl;
	std::cout << *(ite--) << std::endl;
	std::cout << *--ite << std::endl;
	std::cout << *ite-- << std::endl;

	//(*it).m();
	//(*ite).m();

	std::cout << *(--it) << std::endl;
	std::cout << *(it--) << std::endl;
	std::cout << *it-- << std::endl;
	std::cout << *--it << std::endl;
    }

    std::cout << "/////////////////////////////////////" << std::endl;

    {
    const int size = 5;
	ft::vector<TESTED_TYPE> vct(size);
	ft::vector<TESTED_TYPE>::iterator it(vct.begin());
	ft::vector<TESTED_TYPE>::const_iterator ite(vct.end());

	for (int i = 1; it != ite; ++i)
		*it++ = i;
    std::cout << vct.size() << std::endl;

	it = vct.begin();
	ite = vct.begin();

	std::cout << *(++ite) << std::endl;
	std::cout << *(ite++) << std::endl;
	std::cout << *ite++ << std::endl;
	std::cout << *++ite << std::endl;

	//it->m();
	//ite->m();

	std::cout << *(++it) << std::endl;
	std::cout << *(it++) << std::endl;
	std::cout << *it++ << std::endl;
	std::cout << *++it << std::endl;

	std::cout << *(--ite) << std::endl;
	std::cout << *(ite--) << std::endl;
	std::cout << *--ite << std::endl;
	std::cout << *ite-- << std::endl;

	//(*it).m();
	//(*ite).m();

	std::cout << *(--it) << std::endl;
	std::cout << *(it--) << std::endl;
	std::cout << *it-- << std::endl;
	std::cout << *--it << std::endl;
    }
    
	return (0);
}
*/

int main(void)
{
	ft::map<int, int> lala;
	ft::map<int, int> lili;
	lala.insert(ft::pair<int,int>(10,1));
	lala.insert(ft::pair<int,int>(7,1));
	lala.insert(ft::pair<int,int>(18,1));
	lala.insert(ft::pair<int,int>(2,1));
	lala.insert(ft::pair<int,int>(16,1));
	/*lala.insert(ft::pair<int,int>(30,1));
	lala.insert(ft::pair<int,int>(25,1));
	lala.insert(ft::pair<int,int>(40,1));
	lala.insert(ft::pair<int,int>(60,1));
	lala.insert(ft::pair<int,int>(2,1));
	lala.insert(ft::pair<int,int>(1,1));
	lala.insert(ft::pair<int,int>(70,1));
	lala.insert(ft::pair<int,int>(17,1));
	lala.insert(ft::pair<int,int>(65,1));*/
	ft::map<int, int>::iterator it;
	/*
	const ft::map<int, int>::iterator ot = lala.begin();
	if (it != ot)
		return (0);
	for (int i = 0; i < 20; i++)
	{
		std::cout << (*it).first << std::endl;
		it++;
	}
	std::cout << "////////////////////////" << std::endl;
	for (int i = 0; i < 26; i++)
	{
		std::cout << (*it).first << std::endl;
		--it;
	}*/
	lili = lala;
	it = lili.find(85);
	std::cout << it->first << std::endl;
	//lala.display_element();
	//std::cout << "salut" << std::endl;
	return (0);
}
