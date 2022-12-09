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
	for (volatile int i = 0; i < 1; i++)
	{
		std::cout << i << std::endl;
		NAMESPACE::vector<int>	test;

		test.insert(test.begin(), 5, 42);
		test.insert(test.begin(), 10, 24);
		test.insert(test.end(), 2, 420);
		test.insert((test.begin() + 1), 1, 666);
		for (NAMESPACE::vector<int>::iterator start = test.begin(); start != test.end(); start++)
		{
			std::cout << *start << std::endl;
		}
		test.insert((test.begin() + 1), 1000, 666);
		test.insert((test.begin() + 1), 1000, 666);
		test.insert((test.begin() + 1), 1000, 666);
		test.insert((test.begin() + 1), 1000, 666);
		test.insert((test.begin() + 1), 1000, 666);
		for (NAMESPACE::vector<int>::iterator start = test.begin(); start != test.end(); start++)
		{
			std::cout << *start << std::endl;
		}
	}
	std::cout << "*******   Testing std::string vector   *******" << std::endl;
	for (volatile int i = 0; i < 1; i++)
	{
		std::cout << i << std::endl;
		NAMESPACE::vector<std::string>	test;

		test.insert(test.end(), 5, std::string("Bye"));
		test.insert(test.end(), 7, std::string("Re-bye"));
		test.insert(test.begin(),1 , std::string("Hello"));
		test.insert((test.begin() + 1), 2, std::string("How are you?"));
		for (NAMESPACE::vector<std::string>::iterator start = test.begin(); start != test.end(); start++)
		{
			std::cout << *start << std::endl;
		}
		test.insert(test.end(), 1000, std::string("Re-bye"));
		test.insert(test.end(), 1000, std::string("Re-bye"));
		test.insert(test.end(), 1000, std::string("Re-bye"));
		test.insert(test.end(), 1000, std::string("Re-bye"));
		test.insert(test.end(), 1000, std::string("Re-bye"));
		for (NAMESPACE::vector<std::string>::iterator start = test.begin(); start != test.end(); start++)
		{
			std::cout << *start << std::endl;
		}
	}
	std::cout << "*******   Testing ConstClass vector   *******" << std::endl;
	for (volatile int i = 0; i < 1; i++)
	{
		std::cout << i << std::endl;
		NAMESPACE::vector<ConstClass>			test;
		NAMESPACE::vector<ConstClass>::iterator	it;

		test.reserve(50);
		test.insert(test.begin(), 3, ConstClass(42));
		test.insert(test.begin(), 2, ConstClass(24));
		it = test.begin();
		test.insert(test.end(), 4, ConstClass(420));
		test.insert((test.begin() + 1), 13, ConstClass(666));
		for (; it != test.end(); it++)
		{
			std::cout << *it << std::endl;
		}
		test.insert((test.begin()), 50, ConstClass(888));
		for (it = test.begin(); it != test.end(); it++)
		{
			std::cout << *it << std::endl;
		}
	}
	return (0);
}
