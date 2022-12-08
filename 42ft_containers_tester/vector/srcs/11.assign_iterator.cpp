#if ISFT == 1
# define NAMESPACE ft
# include "vector.hpp"
#else
# define NAMESPACE std
# include <vector>
#endif
#include <list>
#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include "ConstClass.hpp"

int	main(void)
{
	std::cout << "*******   Testing int vector   *******" << std::endl;
	{
		int	tab[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		for (volatile int i = 0; i < 100; i++)
		{
			std::cout << i << std::endl;
			NAMESPACE::vector<int>	test;
			
			test.reserve(12);
			test.assign(tab, tab+10);
			std::cout << test.capacity() << std::endl;
			std::cout << test.size() << std::endl;
			for (NAMESPACE::vector<int>::iterator start = test.begin();  start != test.end(); start++)
			{
				std::cout << *start << std::endl;
			}
			test.assign(tab+3, tab+5);
			std::cout << test.capacity() << std::endl;
			std::cout << test.size() << std::endl;
			for (NAMESPACE::vector<int>::iterator start = test.begin();  start != test.end(); start++)
			{
				std::cout << *start << std::endl;
			}
			test.assign(tab+9, tab+9);
			std::cout << test.capacity() << std::endl;
			std::cout << test.size() << std::endl;
			for (NAMESPACE::vector<int>::iterator start = test.begin();  start != test.end(); start++)
			{
				std::cout << *start << std::endl;
			}
		}
	}
	std::cout << "*******   Testing std::string vector   *******" << std::endl;
	{

		for (volatile int i = 0; i < 100; i++)
		{
			std::istringstream	str("0.0 0.1 1.2 5.3 6.4 8.9 10.4");
			std::cout << i << std::endl;
			NAMESPACE::vector<double>	test;
			
			test.assign((std::istream_iterator<double>(str)), (std::istream_iterator<double>()));
			std::cout << test.size() << std::endl;
			if (test.capacity() < test.size())
				std::cout << "Wrong capacity after input iterator" << std::endl;
			for (NAMESPACE::vector<double>::iterator start = test.begin();  start != test.end(); start++)
			{
				std::cout << *start << std::endl;
			}
		}
	}
	std::cout << "*******   Testing ConstClass vector   *******" << std::endl;
	{
		ConstClass	tab[] = {ConstClass(), ConstClass(2), ConstClass(10)};
		ConstClass	tab2[] = {ConstClass(52), ConstClass(21), ConstClass(8)};
		std::list<ConstClass>	filler(tab, tab+3);
		for (volatile int i = 0; i < 100; i++)
		{
			std::cout << i << std::endl;
			NAMESPACE::vector<ConstClass>	test;
			test.assign(filler.begin(), filler.end());
			std::cout << test.size() << std::endl;
			for (NAMESPACE::vector<ConstClass>::iterator start = test.begin();  start != test.end(); start++)
			{
				std::cout << *start << std::endl;
			}
			test.assign(tab2, tab2+2);
			std::cout << test.size() << std::endl;
			for (NAMESPACE::vector<ConstClass>::iterator start = test.begin();  start != test.end(); start++)
			{
				std::cout << *start << std::endl;
			}
		}
	}
	return (0);
}
