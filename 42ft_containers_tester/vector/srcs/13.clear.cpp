#if ISFT == 1
# define NAMESPACE ft
# include "vector.hpp"
#else
# define NAMESPACE std
# include <vector>
#endif
#include <exception>
#include <ctime>
#include <cstdlib>
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
		NAMESPACE::vector<int>	test;
		std::cout << test.size() << std::endl;
		std::cout << test.capacity() << std::endl;
		std::cout << test.empty() << std::endl;
		
		test.clear();

		std::cout << test.size() << std::endl;
		std::cout << test.capacity() << std::endl;
		std::cout << test.empty() << std::endl;
	}
	std::cout << "*******   Testing ConstClass vector   *******" << std::endl;
	for (volatile int i = 0; i < 100; i++)
	{
		std::cout << i << std::endl;
		NAMESPACE::vector<ConstClass>	test(i);
		std::cout << test.size() << std::endl;
		std::cout << test.empty() << std::endl;
		test.clear();
		std::cout << test.empty() << std::endl;
	}
	std::cout << "*******   Testing std::string vector   *******" << std::endl;
	{
		NAMESPACE::vector<int>	test(10, 1);
		std::cout << test.size() << std::endl;
		std::cout << test.empty() << std::endl;
		for (NAMESPACE::vector<int>::const_iterator start = test.begin(); start != test.end() ; start++)
		{
			std::cout << *start << std::endl;
		}
		test.clear();
		std::cout << test.size() << std::endl;
		std::cout << test.empty() << std::endl;
		for (NAMESPACE::vector<int>::const_iterator start = test.begin(); start != test.end() ; start++)
		{
			std::cout << *start << std::endl;
		}
	}
	return (0);
}
