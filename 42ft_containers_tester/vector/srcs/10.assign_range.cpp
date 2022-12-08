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

int	main(void)
{
	std::cout << "*******   Testing int vector   *******" << std::endl;;
	for (volatile int i = 0; i < 100; i++)
	{
		NAMESPACE::vector<int>	test;
		test.reserve(10);
		test.assign(8, 5);
		std::cout << test.capacity() << std::endl;
		std::cout << test.size() << std::endl;
		for (NAMESPACE::vector<int>::iterator start = test.begin(); start != test.end(); start++)
		{
			std::cout << *start << std::endl;
		}
		test.assign(6, 2);
		std::cout << test.capacity() << std::endl;
		std::cout << test.size() << std::endl;
		for (NAMESPACE::vector<int>::iterator start = test.begin(); start != test.end(); start++)
		{
			std::cout << *start << std::endl;
		}
		test.assign(18, 9);
		std::cout << test.size() << std::endl;
		for (NAMESPACE::vector<int>::iterator start = test.begin(); start != test.end(); start++)
		{
			std::cout << *start << std::endl;
		}
	}
	std::cout << "*******   Testing std::string vector   *******" << std::endl;;
	for (volatile int i = 0; i < 100; i++)
	{
		std::cout << i << std::endl;
		NAMESPACE::vector<std::string>	test;

		test.assign(50, std::string("Hello"));
		std::cout << test.size() << std::endl;
		for (NAMESPACE::vector<std::string>::iterator start = test.begin(); start != test.end(); start++)
		{
			std::cout << *start << std::endl;
		}
		test.assign(5, std::string("Bye"));
		std::cout << test.size() << std::endl;
		for (NAMESPACE::vector<std::string>::iterator start = test.begin(); start != test.end(); start++)
		{
			std::cout << *start << std::endl;
		}
	}
	std::cout << "*******   Testing ConstClass vector   *******" << std::endl;;
	for (volatile int i = 0; i < 100; i++)
	{
		std::cout << i << std::endl;
		NAMESPACE::vector<ConstClass>	test;

		test.reserve(15);
		test.assign(10, ConstClass(10));
		std::cout << test.size() << std::endl;
		std::cout << test.capacity() << std::endl;
		for (NAMESPACE::vector<ConstClass>::iterator start = test.begin(); start != test.end(); start++)
		{
			std::cout << *start << std::endl;
		}
		test.assign(3, ConstClass(2));
		std::cout << test.size() << std::endl;
		std::cout << test.capacity() << std::endl;
		for (NAMESPACE::vector<ConstClass>::iterator start = test.begin(); start != test.end(); start++)
		{
			std::cout << *start << std::endl;
		}
		test.assign(20, ConstClass(5));
		std::cout << test.size() << std::endl;
		for (NAMESPACE::vector<ConstClass>::iterator start = test.begin(); start != test.end(); start++)
		{
			std::cout << *start << std::endl;
		}
	}
	return (0);
}
