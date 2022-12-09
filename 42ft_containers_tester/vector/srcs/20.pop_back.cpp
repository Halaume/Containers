#if ISFT == 1
# define NAMESPACE ft
# include "vector.hpp"
#else
# define NAMESPACE std
# include <vector>
#endif
#include <iostream>
#include <string>
#include "ConstClass.hpp"
#include "itPrint.hpp"

int	main(void)
{
	std::cout << "*******   Testing int vector   *******" << std::endl;;
	for (volatile int i = 0; i < 100; i++)
	{
		NAMESPACE::vector<int>	test;
		test.reserve(100);
		test.assign(99, 5);
		std::cout << test.capacity() << std::endl;
		std::cout << test.size() << std::endl;
		itPrint<NAMESPACE::vector<int>::iterator>(test.begin(), test.end());
		test.pop_back();
		std::cout << test.capacity() << std::endl;
		std::cout << test.size() << std::endl;
		while (test.begin() != test.end())
			test.pop_back();
		itPrint<NAMESPACE::vector<int>::iterator>(test.begin(), test.end());
		std::cout << test.capacity() << std::endl;
		std::cout << test.size() << std::endl;
	}
	std::cout << "*******   Testing std::string vector   *******" << std::endl;;
	for (volatile int i = 0; i < 100; i++)
	{
		std::cout << i << std::endl;
		NAMESPACE::vector<std::string>	test;

		test.reserve(50);
		test.assign(50, std::string("Hello"));
		std::cout << test.capacity() << std::endl;
		std::cout << test.size() << std::endl;
		for (NAMESPACE::vector<std::string>::iterator start = test.begin(); start != test.end(); start++)
		{
			std::cout << *start << std::endl;
		}
		test.pop_back();
		std::cout << test.capacity() << std::endl;
		std::cout << test.size() << std::endl;
		while (test.begin() != test.end())
			test.pop_back();
		for (NAMESPACE::vector<std::string>::iterator start = test.begin(); start != test.end(); start++)
		{
			std::cout << *start << std::endl;
		}
		std::cout << test.capacity() << std::endl;
		std::cout << test.size() << std::endl;

	}
	std::cout << "*******   Testing ConstClass vector   *******" << std::endl;;
	for (volatile int i = 0; i < 100; i++)
	{
		std::cout << i << std::endl;
		NAMESPACE::vector<ConstClass>	test;

		test.reserve(15);
		test.assign(10, ConstClass(10));
		test.push_back(ConstClass(3));
		std::cout << test.size() << std::endl;
		std::cout << test.capacity() << std::endl;
		for (NAMESPACE::vector<ConstClass>::iterator start = test.begin(); start != test.end(); start++)
		{
			std::cout << *start << std::endl;
		}
		test.pop_back();
		std::cout << test.size() << std::endl;
		std::cout << test.capacity() << std::endl;
		for (NAMESPACE::vector<ConstClass>::iterator start = test.begin(); start != test.end(); start++)
		{
			std::cout << *start << std::endl;
		}
		while (test.begin() != test.end())
			test.pop_back();
		for (NAMESPACE::vector<ConstClass>::iterator start = test.begin(); start != test.end(); start++)
		{
			std::cout << *start << std::endl;
		}
		std::cout << test.capacity() << std::endl;
		std::cout << test.size() << std::endl;
	}
	return (0);
}
