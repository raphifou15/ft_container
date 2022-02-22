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
#include <string>
//#include <type_traits>
#include <iostream>
# include <stdexcept>
#define TESTED_TYPE int

#define COLOR_GRAY  "\e[1;30m"
#define COLOR_GREEN  "\e[0;32m"
#define COLOR_BLUE	"\e[0;34m"
#define COLOR_END  "\e[0m"

int main ()
{
	{
 	 std::map<char,std::string> mymap;

  	mymap['a']="an element";
  	mymap['b']="another element";
 	mymap['c']=mymap['b'];

  	std::cout << "mymap['a'] is " << mymap['a'] << '\n';
  	std::cout << "mymap['b'] is " << mymap['b'] << '\n';
  	std::cout << "mymap['c'] is " << mymap['c'] << '\n';
  	std::cout << "mymap['d'] is " << mymap['d'] << '\n';

  	std::cout << "mymap now contains " << mymap.size() << " elements.\n";
	}

	{
 	ft::map<char,std::string> mymap;

  	mymap['a']="an element";
  	/*mymap['b']="another element";
 	mymap['c']=mymap['b'];

  	std::cout << "mymap['a'] is " << mymap['a'] << '\n';
  	std::cout << "mymap['b'] is " << mymap['b'] << '\n';
  	std::cout << "mymap['c'] is " << mymap['c'] << '\n';
  	std::cout << "mymap['d'] is " << mymap['d'] << '\n';

  	std::cout << "mymap now contains " << mymap.size() << " elements.\n";*/
	}
  return 0;
}