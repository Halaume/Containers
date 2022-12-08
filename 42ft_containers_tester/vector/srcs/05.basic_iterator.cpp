#if ISFT == 1
# define NAMESPACE ft
# include "vector.hpp"
#else
# define NAMESPACE std
# include <vector>
#endif
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include "ConstClass.hpp"

int	main(void)
{
	std::cout << "*******   Testing int vector   *******" << std::endl;
	{
		NAMESPACE::vector<int>	test;

		for (NAMESPACE::vector<int>::iterator start = test.begin(); start != test.end(); start++)
		{
			std::cout << *start << std::endl;
		}
	}
	std::cout << "*******   Testing ConstClass vector   *******" << std::endl;
	for (volatile int i = 0; i < 100; i++)
	{
		std::cout << i << std::endl;
		NAMESPACE::vector<ConstClass>	test(i);
		NAMESPACE::vector<ConstClass>	test1(i, ConstClass(i -1));
		for (NAMESPACE::vector<ConstClass>::iterator start = test.begin(); start != test.end(); start++)
		{
			std::cout << *start << std::endl;
		}
		for (NAMESPACE::vector<ConstClass>::iterator start = test1.begin(); start != test1.end(); start++)
		{
			std::cout << *start << std::endl;
		}
		for (NAMESPACE::vector<ConstClass>::iterator start = test1.begin(); start != test1.end(); start++)
		{
			std::cout << start->getValue() << std::endl;
		}
	}
	std::cout << "*******   Testing std::string vector   *******" << std::endl;
	{
		std::istringstream	str("0 1 2 3 4 8 4");
		NAMESPACE::vector<int>	test((std::istream_iterator<int>(str)), (std::istream_iterator<int>()));
		for (NAMESPACE::vector<int>::iterator start = test.begin(); start != test.end(); start++)
		{
			std::cout << *start << std::endl;
		}
	}
	return (0);
}
