#include "stack.hpp"
#include "map.hpp"
#include "pair.hpp"
#include "vector.hpp"
#include "lexicographical_compare.hpp"
#include "iterator.hpp"
#include "enable_if.hpp"
#include "is_integral.hpp"
#include "reverse_iterator.hpp"
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
#define COLOR_RED "\e[0;31m"

int main(void)
{
	std::cout << COLOR_GREEN << "/////////////////////////" COLOR_END << std::endl;
	std::cout << COLOR_BLUE << "main de test pour stack" << COLOR_END << std::endl;
	std::cout << COLOR_GREEN << "/////////////////////////" COLOR_END << std::endl;

	
	{
		std::cout << COLOR_RED << "constructing stacks" << COLOR_END << std::endl;
  		ft::vector<int> myvector (2,200);        // vector with 2 elements
  		ft::stack<int> first;                    // empty stack
		ft::stack<int,ft::vector<int> > second;  // empty stack using vector
  		ft::stack<int,ft::vector<int> > third (myvector);
		std::cout << COLOR_BLUE << "ft " << std::endl;
		std::cout << "size of first: " << first.size() << '\n';
  		std::cout << "size of third: " << second.size() << '\n';
  		std::cout << "size of fourth: " << third.size() << '\n';
		std::cout << "-----------------" << COLOR_END << std::endl;
	}
	{
  		std::vector<int> myvector (2,200);        // vector with 2 elements
  		std::stack<int> first;                    // empty stack
		std::stack<int,std::vector<int> > second;  // empty stack using vector
  		std::stack<int,std::vector<int> > third (myvector);
		std::cout << COLOR_GREEN << "std " << std::endl;
		std::cout << "size of first: " << first.size() << '\n';
  		std::cout << "size of third: " << second.size() << '\n';
  		std::cout << "size of fourth: " << third.size() << '\n';
		std::cout << "-----------------" << COLOR_END << std::endl;
	}
	{
		std::cout << COLOR_RED << "stack::empty" << COLOR_END << std::endl;
		ft::stack<int> mystack;
  		int sum (0);
  		for (int i=1;i<=10;i++) mystack.push(i);
  		while (!mystack.empty())
  		{
     		sum += mystack.top();
     		mystack.pop();
  		}
		std::cout << COLOR_BLUE << "ft " << std::endl;
  		std::cout << COLOR_BLUE << "total:" << sum << '\n';
		std::cout << "-----------------" << COLOR_END << std::endl;
	}
	{
		std::stack<int> mystack;
  		int sum (0);
  		for (int i=1;i<=10;i++) mystack.push(i);
  		while (!mystack.empty())
  		{
     		sum += mystack.top();
     		mystack.pop();
  		}
		std::cout << COLOR_GREEN << "std" << std::endl;
  		std::cout << COLOR_GREEN << "total:" <<  sum <<'\n';
		std::cout << "-----------------" << COLOR_END << std::endl;
	}
	{
		std::cout << COLOR_RED << "stack::size" << COLOR_END << std::endl;
		ft::stack<int> myints;
		std::cout << COLOR_BLUE << "ft" << std::endl;
  		std::cout << "0. size: " << myints.size() << '\n';
  		for (int i=0; i<5; i++) myints.push(i);
  		std::cout << "1. size: " << myints.size() << '\n';
		myints.pop();
		std::cout << "2. size: " << myints.size() << '\n';
		std::cout << "-----------------" << COLOR_END << std::endl;
	}
	{
		std::stack<int> myints;
		std::cout << COLOR_GREEN << "std" << std::endl;
  		std::cout << "0. size: " << myints.size() << '\n';
  		for (int i=0; i<5; i++) myints.push(i);
  		std::cout << "1. size: " << myints.size() << '\n';
		myints.pop();
		std::cout << "2. size: " << myints.size() << '\n';
		std::cout << "-----------------" << COLOR_END << std::endl;
	}
	{
		std::cout << COLOR_RED << "stack::top" << COLOR_END << std::endl;
		std::cout << COLOR_BLUE << "ft" << std::endl;
		ft::stack<int> mystack;
		mystack.push(10);
  		mystack.push(20);
  		mystack.top() -= 5;
  		std::cout << "mystack.top() is now " << mystack.top() << '\n';
		std::cout << "-----------------" << COLOR_END << std::endl;
	}
	{
		std::cout << COLOR_GREEN << "std" << std::endl;
		std::stack<int> mystack;
		mystack.push(10);
  		mystack.push(20);
  		mystack.top() -= 5;
  		std::cout << "mystack.top() is now " << mystack.top() << '\n';
		std::cout << "-----------------" << COLOR_END << std::endl;
	}
	{
		std::cout << COLOR_RED << "stack::push/pop" << COLOR_END << std::endl;
		std::cout << COLOR_BLUE << "ft" << std::endl;
		ft::stack<int> mystack;
		for (int i=0; i<5; ++i) mystack.push(i);
  		std::cout << "Popping out elements...";
  		while (!mystack.empty())
  		{
     		std::cout << ' ' << mystack.top();
     		mystack.pop();
  		}
  		std::cout << '\n';
		std::cout << "-----------------" << COLOR_END << std::endl;
	}
	{
		std::cout << COLOR_GREEN << "std" << std::endl;
		std::stack<int> mystack;
		for (int i=0; i<5; ++i) mystack.push(i);
  		std::cout << "Popping out elements...";
  		while (!mystack.empty())
  		{
     		std::cout << ' ' << mystack.top();
     		mystack.pop();
  		}
  		std::cout << '\n';
		std::cout << "-----------------" << COLOR_END << std::endl;
	}

	std::cout << COLOR_GREEN << "/////////////////////////" COLOR_END << std::endl;
	std::cout << COLOR_BLUE << "main de test pour vector" << COLOR_END << std::endl;
	std::cout << COLOR_GREEN << "/////////////////////////" COLOR_END << std::endl;

	{
		std::cout << COLOR_RED << "constructing vectors" << COLOR_END << std::endl;
		std::cout << COLOR_BLUE << "ft" << std::endl;
		ft::vector<int> first;
  		ft::vector<int> second (4,100);                      
  		ft::vector<int> third (second.begin(),second.end());  
  		ft::vector<int> fourth (third);                       
  		int myints[] = {16,2,77,29};
  		ft::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );
  		std::cout << "The contents of fifth are:";
  		for (ft::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
    		std::cout << ' ' << *it;
  		std::cout << '\n';
		std::cout << "-----------------" << COLOR_END << std::endl;
	}
	{
		std::cout << COLOR_GREEN << "std" << std::endl;
		std::vector<int> first;
  		std::vector<int> second (4,100);                      
  		std::vector<int> third (second.begin(),second.end());  
  		std::vector<int> fourth (third);                       
  		int myints[] = {16,2,77,29};
  		std::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );
  		std::cout << "The contents of fifth are:";
  		for (std::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
    		std::cout << ' ' << *it;
  		std::cout << '\n';
		std::cout << "-----------------" << COLOR_END << std::endl;
	}
	{
		std::cout << COLOR_RED << "vector assignment" << COLOR_END << std::endl;
		std::cout << COLOR_BLUE << "ft" << std::endl;
		ft::vector<int> foo (3,0);
		ft::vector<int> bar (5,0);
		bar = foo;
		foo = ft::vector<int>();
		std::cout << "Size of foo: " << int(foo.size()) << '\n';
		std::cout << "Size of bar: " << int(bar.size()) << '\n';
		std::cout << "-----------------" << COLOR_END << std::endl;
	}
	{
		std::cout << COLOR_GREEN << "std" << std::endl;
		std::vector<int> foo (3,0);
		std::vector<int> bar (5,0);
		bar = foo;
		foo = std::vector<int>();
		std::cout << "Size of foo: " << int(foo.size()) << '\n';
		std::cout << "Size of bar: " << int(bar.size()) << '\n';
		std::cout << "-----------------" << COLOR_END << std::endl;
	}
	{
		std::cout << COLOR_RED << "vector::begin/end" << COLOR_END << std::endl;
		std::cout << COLOR_BLUE << "ft" << std::endl;
		ft::vector<int> myvector;
		for (int i=1; i<=5; i++) myvector.push_back(i);
  		std::cout << "myvector contains:";
		for (ft::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
		std::cout << ' ' << *it;
		std::cout << '\n';
		std::cout << "------------------" << COLOR_END << std::endl;
	}
	{
		std::cout << COLOR_GREEN << "std" << std::endl;
		std::vector<int> myvector;
		for (int i=1; i<=5; i++) myvector.push_back(i);
  		std::cout << "myvector contains:";
		for (std::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
		std::cout << ' ' << *it;
		std::cout << '\n';
		std::cout << "------------------" << COLOR_END << std::endl;
	}
	{
		std::cout << COLOR_RED << "vector::rbegin/rend" << COLOR_END << std::endl;
		std::cout << COLOR_BLUE << "ft" << std::endl;
		ft::vector<int> myvector (5);
		int i=0;
		ft::vector<int>::reverse_iterator rit = myvector.rbegin();
		for (; rit!= myvector.rend(); ++rit)
			*rit = ++i;
		std::cout << "myvector contains:";
		for (ft::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
		std::cout << "------------------" << COLOR_END << std::endl;
	}
	{
		std::cout << COLOR_GREEN << "std" << std::endl;
		std::vector<int> myvector (5);
		int i=0;
		std::vector<int>::reverse_iterator rit = myvector.rbegin();
		for (; rit!= myvector.rend(); ++rit)
			*rit = ++i;
		std::cout << "myvector contains:";
		for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
		std::cout << "------------------" << COLOR_END << std::endl;
	}
	{
		std::cout << COLOR_RED << "vector::size" << COLOR_END << std::endl;
		std::cout << COLOR_BLUE << "ft" << std::endl;
		ft::vector<int> myints;
		std::cout << "0. size: " << myints.size() << '\n';
  		for (int i=0; i<10; i++) myints.push_back(i);
		std::cout << "1. size: " << myints.size() << '\n';
		myints.insert (myints.end(),10,100);
		std::cout << "2. size: " << myints.size() << '\n';
		myints.pop_back();
		std::cout << "3. size: " << myints.size() << '\n';
		std::cout << "------------------" << COLOR_END << std::endl;
	}
	{
		std::cout << COLOR_GREEN << "std" << std::endl;
		std::vector<int> myints;
		std::cout << "0. size: " << myints.size() << '\n';
  		for (int i=0; i<10; i++) myints.push_back(i);
		std::cout << "1. size: " << myints.size() << '\n';
		myints.insert (myints.end(),10,100);
		std::cout << "2. size: " << myints.size() << '\n';
		myints.pop_back();
		std::cout << "3. size: " << myints.size() << '\n';
		std::cout << "------------------" << COLOR_END << std::endl;
	}
	{
		std::cout << COLOR_RED << "comparing size, capacity and max_size" << COLOR_END << std::endl;
		ft::vector<int> myvector;
		std::cout << COLOR_BLUE << "ft" << std::endl;
		for (int i=0; i<100; i++) myvector.push_back(i);
		std::cout << "size: " << myvector.size() << "\n";
		std::cout << "capacity: " << myvector.capacity() << "\n";
		std::cout << "max_size: " << myvector.max_size() << "\n";
		std::cout << "------------------" << COLOR_END << std::endl;
	}
	{
		std::vector<int> myvector;
		std::cout << COLOR_GREEN << "std" << std::endl;
		for (int i=0; i<100; i++) myvector.push_back(i);
		std::cout << "size: " << myvector.size() << "\n";
		std::cout << "capacity: " << myvector.capacity() << "\n";
		std::cout << "max_size: " << myvector.max_size() << "\n";
		std::cout << "------------------" << COLOR_END << std::endl;
	}
	{
		std::cout << COLOR_RED << "resizing vector" << COLOR_END << std::endl;
		std::cout << COLOR_BLUE << "ft" << std::endl;
		ft::vector<int> myvector;
		for (int i=1;i<10;i++) myvector.push_back(i);
  		myvector.resize(5);
  		myvector.resize(8,100);
  		myvector.resize(12);
		std::cout << "myvector contains:";
		for (unsigned int i=0;i < myvector.size();i++)
    		std::cout << ' ' << myvector[i];
		std::cout << '\n';
		std::cout << "------------------" << COLOR_END << std::endl;
	}
	{
		std::cout << COLOR_GREEN << "std" << std::endl;
		std::vector<int> myvector;
		for (int i=1;i<10;i++) myvector.push_back(i);
  		myvector.resize(5);
  		myvector.resize(8,100);
  		myvector.resize(12);
		std::cout << "myvector contains:";
		for (unsigned int i=0;i<myvector.size();i++)
    		std::cout << ' ' << myvector[i];
		std::cout << '\n';
		std::cout << "------------------" << COLOR_END << std::endl;
	}
	{
		std::cout << COLOR_RED << "vector::empty" << COLOR_END << std::endl;
		std::cout << COLOR_BLUE << "ft" << std::endl;
		ft::vector<int> myvector;
		int sum (0);
		for (int i=1;i<=10;i++) myvector.push_back(i);
		while (!myvector.empty())
		{
			sum += myvector.back();
			myvector.pop_back();
		}
  		std::cout << "total: " << sum << '\n';
		std::cout << "------------------" << COLOR_END << std::endl;
	}
	{
		std::cout << COLOR_GREEN << "std" << std::endl;
		std::vector<int> myvector;
		int sum (0);
		for (int i=1;i<=10;i++) myvector.push_back(i);
		while (!myvector.empty())
		{
			sum += myvector.back();
			myvector.pop_back();
		}
  		std::cout << "total: " << sum << '\n';
		std::cout << "------------------" << COLOR_END << std::endl;
	}
	{
		std::cout << COLOR_RED << "vector::reserve" << COLOR_END << std::endl;
		std::cout << COLOR_BLUE << "ft" << std::endl;
		ft::vector<int>::size_type sz;
  		ft::vector<int> foo;
		sz = foo.capacity();
		std::cout << "making foo grow:\n";
		for (int i=0; i<100; ++i) {
		foo.push_back(i);
		if (sz!=foo.capacity()) {
			sz = foo.capacity();
		std::cout << "capacity changed: " << sz << '\n';
    		}
		}
		ft::vector<int> bar;
		sz = bar.capacity();
		bar.reserve(100);   // this is the only difference with foo above
		std::cout << "making bar grow:\n";
		for (int i=0; i<100; ++i) {
			bar.push_back(i);
			if (sz!=bar.capacity()) {
			sz = bar.capacity();
			std::cout << "capacity changed: " << sz << '\n';
    		}
  		}
		std::cout << "------------------" << COLOR_END << std::endl;
	}
	{
		std::cout << COLOR_GREEN << "std" << std::endl;
		std::vector<int>::size_type sz;
  		std::vector<int> foo;
		sz = foo.capacity();
		std::cout << "making foo grow:\n";
		for (int i=0; i<100; ++i) {
		foo.push_back(i);
		if (sz!=foo.capacity()) {
			sz = foo.capacity();
		std::cout << "capacity changed: " << sz << '\n';
    		}
		}
		std::vector<int> bar;
		sz = bar.capacity();
		bar.reserve(100);   // this is the only difference with foo above
		std::cout << "making bar grow:\n";
		for (int i=0; i<100; ++i) {
			bar.push_back(i);
			if (sz!=bar.capacity()) {
			sz = bar.capacity();
			std::cout << "capacity changed: " << sz << '\n';
    		}
  		}
		std::cout << "------------------" << COLOR_END << std::endl;
	}
	{
		std::cout << COLOR_RED << "vector::operator[]" << COLOR_END << std::endl;
		std::cout << COLOR_BLUE << "ft" << std::endl;
		ft::vector<int> myvector (10);   // 10 zero-initialized elements
		ft::vector<int>::size_type sz = myvector.size();
  		for (unsigned i=0; i<sz; i++) myvector[i]=i;
  		for (unsigned i=0; i<sz/2; i++)
  		{
    		int temp;
    		temp = myvector[sz-1-i];
    		myvector[sz-1-i]=myvector[i];
    		myvector[i]=temp;
		}
  		std::cout << "myvector contains:";
  		for (unsigned i=0; i<sz; i++)
    		std::cout << ' ' << myvector[i];
		std::cout << '\n';
		std::cout << "------------------" << COLOR_END << std::endl;
	}
	{
		std::cout << COLOR_GREEN << "std" << std::endl;
		std::vector<int> myvector (10);   // 10 zero-initialized elements
		std::vector<int>::size_type sz = myvector.size();
  		for (unsigned i=0; i<sz; i++) myvector[i]=i;
  		for (unsigned i=0; i<sz/2; i++)
  		{
    		int temp;
    		temp = myvector[sz-1-i];
    		myvector[sz-1-i]=myvector[i];
    		myvector[i]=temp;
		}
  		std::cout << "myvector contains:";
  		for (unsigned i=0; i<sz; i++)
    		std::cout << ' ' << myvector[i];
		std::cout << '\n';
		std::cout << "------------------" << COLOR_END << std::endl;
	}
	{
		std::cout << COLOR_RED << "vector::at" << COLOR_END << std::endl;
		std::cout << COLOR_BLUE << "ft" << std::endl;
		ft::vector<int> myvector (10);   // 10 zero-initialized ints
		for (unsigned i=0; i<myvector.size(); i++)
			myvector.at(i)=i;
		std::cout << "myvector contains:";
		for (unsigned i=0; i<myvector.size(); i++)
			std::cout << ' ' << myvector.at(i);
		std::cout << '\n';
		std::cout << "------------------" << COLOR_END << std::endl;
	}
	{
		std::cout << COLOR_GREEN << "std" << std::endl;
		std::vector<int> myvector (10);   // 10 zero-initialized ints
		for (unsigned i=0; i<myvector.size(); i++)
			myvector.at(i)=i;
		std::cout << "myvector contains:";
		for (unsigned i=0; i<myvector.size(); i++)
			std::cout << ' ' << myvector.at(i);
		std::cout << '\n';
		std::cout << "------------------" << COLOR_END << std::endl;
	}
	{
		std::cout << COLOR_RED << "vector::front" << COLOR_END << std::endl;
		std::cout << COLOR_BLUE << "ft" << std::endl;
		ft::vector<int> myvector;
		myvector.push_back(78);
		myvector.push_back(16);
		myvector.front() -= myvector.back();
		std::cout << "myvector.front() is now " << myvector.front() << '\n';
		std::cout << "------------------" << COLOR_END << std::endl;
	}
	{
		std::cout << COLOR_GREEN << "std" << std::endl;
		std::vector<int> myvector;
		myvector.push_back(78);
		myvector.push_back(16);
		myvector.front() -= myvector.back();
		std::cout << "myvector.front() is now " << myvector.front() << '\n';
		std::cout << "------------------" << COLOR_END << std::endl;
	}
	{
		std::cout << COLOR_RED << "vector::back" << COLOR_END << std::endl;
		std::cout << COLOR_BLUE << "ft" << std::endl;
		ft::vector<int> myvector;
		myvector.push_back(10);
		while (myvector.back() != 0)
		{
			myvector.push_back ( myvector.back() -1 );
		}
		std::cout << "myvector contains:";
		for (unsigned i=0; i<myvector.size() ; i++)
			std::cout << ' ' << myvector[i];
		std::cout << '\n';
		std::cout << "------------------" << COLOR_END << std::endl;
	}
	{
		std::cout << COLOR_GREEN << "std" << std::endl;
		std::vector<int> myvector;
		myvector.push_back(10);
		while (myvector.back() != 0)
		{
			myvector.push_back ( myvector.back() -1 );
		}
		std::cout << "myvector contains:";
		for (unsigned i=0; i<myvector.size() ; i++)
			std::cout << ' ' << myvector[i];
		std::cout << '\n';
		std::cout << "------------------" << COLOR_END << std::endl;
	}
	{
		std::cout << COLOR_RED << "vector assign" << COLOR_END << std::endl;
		std::cout << COLOR_BLUE << "ft" << std::endl;
		ft::vector<int> first;
		ft::vector<int> second;
		ft::vector<int> third;
		first.assign (7,100);             // 7 ints with a value of 100
		ft::vector<int>::iterator it;
		it=first.begin()+1;
		second.assign (it,first.end()-1); // the 5 central values of first
		int myints[] = {1776,7,4};
		third.assign (myints,myints+3);   // assigning from array.
		std::cout << "Size of first: " << int (first.size()) << '\n';
		std::cout << "Size of second: " << int (second.size()) << '\n';
		std::cout << "Size of third: " << int (third.size()) << '\n';
		std::cout << "------------------" << COLOR_END << std::endl;
	}
	{
		std::cout << COLOR_GREEN << "std" << std::endl;
		std::vector<int> first;
		std::vector<int> second;
		std::vector<int> third;
		first.assign (7,100);             // 7 ints with a value of 100
		std::vector<int>::iterator it;
		it=first.begin()+1;
		second.assign (it,first.end()-1); // the 5 central values of first
		int myints[] = {1776,7,4};
		third.assign (myints,myints+3);   // assigning from array.
		std::cout << "Size of first: " << int (first.size()) << '\n';
		std::cout << "Size of second: " << int (second.size()) << '\n';
		std::cout << "Size of third: " << int (third.size()) << '\n';
		std::cout << "------------------" << COLOR_END << std::endl;
	}
	{
		std::cout << COLOR_RED << "vector::push_back" << COLOR_END << std::endl;
		std::cout << COLOR_BLUE << "ft" << std::endl;
		ft::vector<int> myvector;
		for (int myint = 0; myint < 100; myint++)
			myvector.push_back (myint);
		std::cout << "myvector stores " << int(myvector.size()) << " numbers.\n";
		std::cout << "------------------" << COLOR_END << std::endl;
	}
	{
		std::cout << COLOR_GREEN << "std" << std::endl;
		std::vector<int> myvector;
		for (int myint = 0; myint < 100; myint++)
			myvector.push_back (myint);
		std::cout << "myvector stores " << int(myvector.size()) << " numbers.\n";
		std::cout << "------------------" << COLOR_END << std::endl;
	}
	{
		std::cout << COLOR_RED << "vector::pop_back" << COLOR_END << std::endl;
		std::cout << COLOR_BLUE << "ft" << std::endl;
		ft::vector<int> myvector;
		int sum (0);
		myvector.push_back (100);
		myvector.push_back (200);
		myvector.push_back (300);
		while (!myvector.empty())
		{
			sum+=myvector.back();
			myvector.pop_back();
		}
		std::cout << "The elements of myvector add up to " << sum << '\n';
		std::cout << "------------------" << COLOR_END << std::endl;
	}
	{
		std::cout << COLOR_GREEN << "std" << std::endl;
		std::vector<int> myvector;
		int sum (0);
		myvector.push_back (100);
		myvector.push_back (200);
		myvector.push_back (300);
		while (!myvector.empty())
		{
			sum+=myvector.back();
			myvector.pop_back();
		}
		std::cout << "The elements of myvector add up to " << sum << '\n';
		std::cout << "------------------" << COLOR_END << std::endl;
	}
	{
		std::cout << COLOR_RED << "inserting into a vector" << COLOR_END << std::endl;
		std::cout << COLOR_BLUE << "ft" << std::endl;
		ft::vector<int> myvector (3,100);
		ft::vector<int>::iterator it;
		it = myvector.begin();
		it = myvector.insert ( it , 200 );
		myvector.insert (it,2,300);
		it = myvector.begin();
		ft::vector<int> anothervector (2,400);
		myvector.insert (it+2,anothervector.begin(),anothervector.end());
		int myarray [] = { 501,502,503 };
		myvector.insert (myvector.begin(), myarray, myarray+3);
		std::cout << "myvector contains:";
		for (it=myvector.begin(); it<myvector.end(); it++)
    		std::cout << ' ' << *it;
  		std::cout << '\n';
		std::cout << "------------------" << COLOR_END << std::endl;
	}
	{
		std::cout << COLOR_GREEN << "std" << std::endl;
		std::vector<int> myvector (3,100);
		std::vector<int>::iterator it;
		it = myvector.begin();
		it = myvector.insert ( it , 200 );
		myvector.insert (it,2,300);
		it = myvector.begin();
		std::vector<int> anothervector (2,400);
		myvector.insert (it+2,anothervector.begin(),anothervector.end());
		int myarray [] = { 501,502,503 };
		myvector.insert (myvector.begin(), myarray, myarray+3);
		std::cout << "myvector contains:";
		for (it=myvector.begin(); it<myvector.end(); it++)
    		std::cout << ' ' << *it;
  		std::cout << '\n';
		std::cout << "------------------" << COLOR_END << std::endl;
	}
	{
		std::cout << COLOR_RED << "erasing from vector" << COLOR_END << std::endl;
		std::cout << COLOR_BLUE << "ft" << std::endl;
		ft::vector<int> myvector;
		for (int i=1; i<=10; i++) myvector.push_back(i);
		myvector.erase (myvector.begin()+5);
		myvector.erase (myvector.begin(),myvector.begin()+3);
		std::cout << "myvector contains:";
		for (unsigned i=0; i<myvector.size(); ++i)
    		std::cout << ' ' << myvector[i];
		std::cout << '\n';
		std::cout << "------------------" << COLOR_END << std::endl;
	}
	{
		std::cout << COLOR_GREEN << "std" << std::endl;
		std::vector<int> myvector;
		for (int i=1; i<=10; i++) myvector.push_back(i);
		myvector.erase (myvector.begin()+5);
		myvector.erase (myvector.begin(),myvector.begin()+3);
		std::cout << "myvector contains:";
		for (unsigned i=0; i<myvector.size(); ++i)
    		std::cout << ' ' << myvector[i];
		std::cout << '\n';
		std::cout << "------------------" << COLOR_END << std::endl;
	}
	{
		std::cout << COLOR_RED << "swap vectors" << COLOR_END << std::endl;
		std::cout << COLOR_BLUE << "ft" << std::endl;
		ft::vector<int> foo (3,100);
		ft::vector<int> bar (5,200);
		foo.swap(bar);
		std::cout << "foo contains:";
		for (unsigned i=0; i<foo.size(); i++)
			std::cout << ' ' << foo[i];
		std::cout << '\n';
		std::cout << "bar contains:";
		for (unsigned i=0; i<bar.size(); i++)
			std::cout << ' ' << bar[i];
		std::cout << '\n';
		std::cout << "------------------" << COLOR_END << std::endl;
	}
	{
		std::cout << COLOR_GREEN << "std" << std::endl;
		std::vector<int> foo (3,100);
		std::vector<int> bar (5,200);
		foo.swap(bar);
		std::cout << "foo contains:";
		for (unsigned i=0; i<foo.size(); i++)
			std::cout << ' ' << foo[i];
		std::cout << '\n';
		std::cout << "bar contains:";
		for (unsigned i=0; i<bar.size(); i++)
			std::cout << ' ' << bar[i];
		std::cout << '\n';
		std::cout << "------------------" << COLOR_END << std::endl;
	}
	{
		std::cout << COLOR_RED << "clearing vectors" << COLOR_END << std::endl;
		std::cout << COLOR_BLUE << "ft" << std::endl;
		ft::vector<int> myvector;
		myvector.push_back (100);
		myvector.push_back (200);
		myvector.push_back (300);
		std::cout << "myvector contains:";
		for (unsigned i=0; i<myvector.size(); i++)
    		std::cout << ' ' << myvector[i];
		std::cout << '\n';
  		myvector.clear();
  		myvector.push_back (1101);
  		myvector.push_back (2202);
  		std::cout << "myvector contains:";
  		for (unsigned i=0; i<myvector.size(); i++)
			std::cout << ' ' << myvector[i];
		std::cout << '\n';
		std::cout << "------------------" << COLOR_END << std::endl;
	}
	{
		std::cout << COLOR_GREEN << "std" << std::endl;
		std::vector<int> myvector;
		myvector.push_back (100);
		myvector.push_back (200);
		myvector.push_back (300);
		std::cout << "myvector contains:";
		for (unsigned i=0; i<myvector.size(); i++)
    		std::cout << ' ' << myvector[i];
		std::cout << '\n';
  		myvector.clear();
  		myvector.push_back (1101);
  		myvector.push_back (2202);
  		std::cout << "myvector contains:";
  		for (unsigned i=0; i<myvector.size(); i++)
			std::cout << ' ' << myvector[i];
		std::cout << '\n';
		std::cout << "------------------" << COLOR_END << std::endl;
	}
	{
		std::cout << COLOR_RED << "vector::get_allocator" << COLOR_END << std::endl;
		std::cout << COLOR_BLUE << "ft" << std::endl;
		ft::vector<int> myvector;
		int * p;
		unsigned int i;
		p = myvector.get_allocator().allocate(5);
		for (i=0; i<5; i++) myvector.get_allocator().construct(&p[i],i);
		std::cout << "The allocated array contains:";
		for (i=0; i<5; i++) std::cout << ' ' << p[i];
		std::cout << '\n';
		for (i=0; i<5; i++) myvector.get_allocator().destroy(&p[i]);
		myvector.get_allocator().deallocate(p,5);
		std::cout << "------------------" << COLOR_END << std::endl;
	}
	{
		std::cout << COLOR_GREEN << "std" << std::endl;
		std::vector<int> myvector;
		int * p;
		unsigned int i;
		p = myvector.get_allocator().allocate(5);
		for (i=0; i<5; i++) myvector.get_allocator().construct(&p[i],i);
		std::cout << "The allocated array contains:";
		for (i=0; i<5; i++) std::cout << ' ' << p[i];
		std::cout << '\n';
		for (i=0; i<5; i++) myvector.get_allocator().destroy(&p[i]);
		myvector.get_allocator().deallocate(p,5);
		std::cout << "------------------" << COLOR_END << std::endl;
	}
	{
		std::cout << COLOR_RED << "swap (vector overload)" << COLOR_END << std::endl;
		std::cout << COLOR_BLUE << "ft" << std::endl;
		unsigned int i; (void)i;
		ft::vector<int> foo (3,100);   // three ints with a value of 100
		ft::vector<int> bar (5,200);   // five ints with a value of 200
		foo.swap(bar);
		std::cout << "foo contains:";
		for (ft::vector<int>::iterator it = foo.begin(); it!=foo.end(); ++it)
    		std::cout << ' ' << *it;
		std::cout << '\n';
		std::cout << "bar contains:";
		for (ft::vector<int>::iterator it = bar.begin(); it!=bar.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
		std::cout << "------------------" << COLOR_END << std::endl;
	}
	{
		std::cout << COLOR_GREEN << "std" << std::endl;
		unsigned int i; (void)i;
		std::vector<int> foo (3,100);   // three ints with a value of 100
		std::vector<int> bar (5,200);   // five ints with a value of 200
		foo.swap(bar);
		std::cout << "foo contains:";
		for (std::vector<int>::iterator it = foo.begin(); it!=foo.end(); ++it)
    		std::cout << ' ' << *it;
		std::cout << '\n';
		std::cout << "bar contains:";
		for (std::vector<int>::iterator it = bar.begin(); it!=bar.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
		std::cout << "------------------" << COLOR_END << std::endl;
	}
	{
		std::cout << COLOR_RED << "swap (vector overload)" << COLOR_END << std::endl;
		std::cout << COLOR_BLUE << "ft" << std::endl;
		ft::vector<int> foo (3,100);   // three ints with a value of 100
		ft::vector<int> bar (2,200);   // two ints with a value of 200

		if (foo==bar) std::cout << "foo and bar are equal\n";
		if (foo!=bar) std::cout << "foo and bar are not equal\n";
		if (foo< bar) std::cout << "foo is less than bar\n";
		if (foo> bar) std::cout << "foo is greater than bar\n";
		if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
		if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
		std::cout << "------------------" << COLOR_END << std::endl;
	}
	{
		std::cout << COLOR_GREEN << "std" << std::endl;
		std::vector<int> foo (3,100);   // three ints with a value of 100
		std::vector<int> bar (2,200);   // two ints with a value of 200

		if (foo==bar) std::cout << "foo and bar are equal\n";
		if (foo!=bar) std::cout << "foo and bar are not equal\n";
		if (foo< bar) std::cout << "foo is less than bar\n";
		if (foo> bar) std::cout << "foo is greater than bar\n";
		if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
		if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
		std::cout << "------------------" << COLOR_END << std::endl;
	}
	std::cout << COLOR_GREEN << "/////////////////////////" COLOR_END << std::endl;
	std::cout << COLOR_BLUE << "main de test pour map" << COLOR_END << std::endl;
	std::cout << COLOR_GREEN << "/////////////////////////" COLOR_END << std::endl;
	return (0);
}