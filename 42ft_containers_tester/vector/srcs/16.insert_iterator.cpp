#if ISFT == 1
# define NAMESPACE ft
# include "vector.hpp"
#else
# define NAMESPACE std
# include <vector>
#endif
#include <list>
#include <exception>
#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <memory>
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
			std::list<int>			filler(1000, 1);

			test.insert(test.begin(), tab, tab+10);
			test.insert(test.end(), tab+3, tab+4);
			test.insert(test.begin(), tab+10, tab+10);
			test.insert((test.begin() + 3), tab+1, tab+4);
			for (NAMESPACE::vector<int>::iterator start = test.begin(); start != test.end(); start++)
			{
				std::cout << *start << std::endl;
			}
			test.insert(test.begin(), filler.begin(), filler.end());
			test.insert(test.begin(), filler.begin(), filler.end());
			test.insert(test.end(), filler.begin(), filler.end());
			test.insert(test.begin(), filler.begin(), filler.end());
			test.insert(test.begin(), filler.begin(), filler.end());
		}
	}
	std::cout << "*******   Testing Input iterator   *******" << std::endl;
	{

		for (volatile int i = 0; i < 100; i++)
		{
			double	tab[]= {3.2, 5.5};
			std::istringstream	str("0.0 0.1 1.2 5.3 6.4 8.9 10.4");
			std::cout << i << std::endl;
			NAMESPACE::vector<double>	test;
			
			test.insert(test.begin(), tab, tab+2);
			test.insert(test.begin(), (std::istream_iterator<double>(str)), (std::istream_iterator<double>()));
			test.insert(test.end(), (std::istream_iterator<double>(str)), (std::istream_iterator<double>()));
			for (NAMESPACE::vector<double>::iterator start = test.begin(); start != test.end(); start++)
			{
				std::cout << *start << std::endl;
			}
		}
		for (volatile int i = 0; i < 100; i++)
		{
			double	tab[]= {3.2, 5.5};
			std::istringstream	str("0.0 0.1 1.2 5.3 6.4 8.9 10.4");
			std::cout << i << std::endl;
			NAMESPACE::vector<double>			test;
			NAMESPACE::vector<double>::iterator	start;
			
			test.reserve(100);
			test.insert(test.begin(), tab, tab+2);
			test.insert(test.begin(), (std::istream_iterator<double>(str)), (std::istream_iterator<double>()));
			start = test.begin();
			test.insert(test.end(), (std::istream_iterator<double>(str)), (std::istream_iterator<double>()));
			for (; start != test.end(); start++)
			{
				std::cout << *start << std::endl;
			}
			std::cout << "Capacity: " << test.capacity() << std::endl;
		}

	}
	std::cout << "*******   Testing ConstClass vector   *******" << std::endl;
	{
		ConstClass	tab[] = {ConstClass(), ConstClass(2), ConstClass(10)};
		ConstClass	tab2[] = {ConstClass(666), ConstClass(42)};
		for (volatile int i = 0; i < 100; i++)
		{
			std::cout << i << std::endl;
			NAMESPACE::vector<ConstClass>	test;


			test.reserve(50);
			test.insert(test.begin(), tab, tab+3);
			test.insert(test.begin(), tab2, tab2+2);
			test.insert(test.end(), tab2, tab2+1);
			for (NAMESPACE::vector<ConstClass>::iterator it = test.begin(); it != test.end(); it++)
			{
				std::cout << *it << std::endl;
			}
			test.insert((test.begin() + 3), tab, tab);
			test.insert((test.begin() + 5), tab2, tab2+2);
			for (NAMESPACE::vector<ConstClass>::iterator it = test.begin(); it != test.end(); it++)
			{
				std::cout << *it << std::endl;
			}
			std::cout << "Capacity: " << test.capacity() << std::endl;
		}
	}
	return (0);
}

