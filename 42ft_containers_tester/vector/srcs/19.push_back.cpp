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
	std::cout << "*******   Testing int vector   *******" << std::endl;
	for (int i = 0; i < 100; i++)
	{
		NAMESPACE::vector<int>				test;
		NAMESPACE::vector<int>::iterator	start;

		for (int j = 0; j > -200; j--)
		{
			test.push_back(j);
		}
		std::cout << test.size() << std::endl;
		for (start = test.begin(); start != test.end(); start++)
		{
			std::cout << *start << std::endl;
		}
	}
	std::cout << "*******   Testing std::string vector   *******" << std::endl;
	for (int i = 0; i < 100; i++)
	{
		NAMESPACE::vector<std::string>				test;
		NAMESPACE::vector<std::string>::iterator	start;
		std::string									base;

		test.reserve(500);
		start = test.begin();
		base = "a";
		for (int j = 0; j > -200; j--)
		{
			test.push_back((base + std::string("a")));
		}
		std::cout << test.size() << test.capacity() << std::endl;
		for (; start != test.end(); start++)
		{
			std::cout << *start << std::endl;
		}
	}
	std::cout << "*******   Testing ConstClass vector   *******" << std::endl;
	for (int i = 0; i < 100; i++)
	{
		NAMESPACE::vector<ConstClass>	test;


		for (int j = 0; j > -200; j--)
		{
			test.push_back(ConstClass(j));
		}
		std::cout << test.size() << std::endl;
		for (NAMESPACE::vector<ConstClass>::iterator start = test.begin(); start != test.end(); start++)
		{
			std::cout << *start << std::endl;
		}
	}
	return (0);
}
