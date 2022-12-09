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
	for (volatile int i = 0; i < 100; i++)
	{
		std::cout << i << std::endl;
		NAMESPACE::vector<int>	test;

		test.insert(test.begin(), 42);
		test.insert(test.begin(), 24);
		test.insert(test.end(), 420);
		test.insert((test.begin() + 1), 666);
		for (NAMESPACE::vector<int>::iterator start = test.begin(); start != test.end(); start++)
		{
			std::cout << *start << std::endl;
		}
	}
	std::cout << "*******   Testing std::string vector   *******" << std::endl;
	for (volatile int i = 0; i < 100; i++)
	{
		std::cout << i << std::endl;
		NAMESPACE::vector<std::string>	test;

		test.insert(test.end(), std::string("Bye"));
		test.insert(test.end(), std::string("Re-bye"));
		test.insert(test.begin(), std::string("Hello"));
		test.insert((test.begin() + 1), std::string("How are you?"));
		for (NAMESPACE::vector<std::string>::iterator start = test.begin(); start != test.end(); start++)
		{
			std::cout << *start << std::endl;
		}

	}
	std::cout << "*******   Testing ConstClass vector   *******" << std::endl;
	for (volatile int i = 0; i < 100; i++)
	{
		std::cout << i << std::endl;
		NAMESPACE::vector<ConstClass>			test;
		NAMESPACE::vector<ConstClass>::iterator	it;

		test.reserve(20);
		test.insert(test.begin(), ConstClass(42));
		test.insert(test.begin(), ConstClass(24));
		it = test.begin();
		test.insert(test.end(), ConstClass(420));
		test.insert((test.begin() + 1), ConstClass(666));
		for (; it != test.end(); it++)
		{
			std::cout << *it << std::endl;
		}

	}
	return (0);
}
