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
	for (int i = 0; i < 100; i++)
	{
		NAMESPACE::vector<int>				test(100, i);
		NAMESPACE::vector<int>::size_type	capacity;
		NAMESPACE::vector<int>::iterator	it = test.begin();

		capacity = test.capacity();
		std::cout << test.size() << std::endl;
		*(test.begin()) = -1;
		*(test.end() - 1) = 666;
		for (NAMESPACE::vector<int>::iterator start = it; start != test.end(); start++)
		{
			std::cout << *start << std::endl;
		}
		test.erase((test.begin() + 1), (test.begin() + 10));
		std::cout << test.size() << std::endl;
		test.erase((test.end() - 1), test.end());
		test.erase((test.begin(), test.begin()));
		for (NAMESPACE::vector<int>::iterator start = it; start != test.end(); start++)
		{
			std::cout << *start << std::endl;
		}
		test.erase((test.end() + 1), (test.end() + 1));
		std::cout << test.size() << std::endl;
		test.erase(test.begin(), test.end());
		std::cout << test.size() << std::endl;
		if (capacity != test.capacity())
			std::cout << "Wrong capacity detected" << std::endl;
	}
	std::cout << "*******   Testing std::string vector   *******" << std::endl;;
	for (int i = 0; i < 100; i++)
	{
		NAMESPACE::vector<std::string>	test(100, std::string("Hello"));
		NAMESPACE::vector<std::string>::size_type	capacity;
		NAMESPACE::vector<std::string>::iterator	it = test.begin();

		capacity = test.capacity();
		std::cout << test.size() << std::endl;
		*(test.begin()) = std::string("Youhou");
		*(test.end() - 1) = std::string("Bye");
		for (NAMESPACE::vector<std::string>::iterator start = it; start != test.end(); start++)
		{
			std::cout << *start << std::endl;
		}
		test.erase((test.begin() + 1), (test.begin() + 10));
		std::cout << test.size() << std::endl;
		test.erase((test.end() - 1), test.end());
		test.erase((test.begin(), test.begin()));
		for (NAMESPACE::vector<std::string>::iterator start = it; start != test.end(); start++)
		{
			std::cout << *start << std::endl;
		}
		test.erase((test.end() + 1), (test.end() + 1));
		std::cout << test.size() << std::endl;
		test.erase(test.begin(), test.end());
		std::cout << test.size() << std::endl;
		if (capacity != test.capacity())
			std::cout << "Wrong capacity detected" << std::endl;

	}
	std::cout << "*******   Testing ConstClass vector   *******" << std::endl;
	for (int i = 0; i < 100; i++)
	{
		NAMESPACE::vector<ConstClass>	test(100, ConstClass(i -1));
		NAMESPACE::vector<ConstClass>::size_type	capacity;
		NAMESPACE::vector<ConstClass>::iterator	it = test.begin();

		capacity = test.capacity();
		std::cout << test.size() << std::endl;
		*(test.begin()) = ConstClass(-42);
		*(test.end() - 1) = ConstClass(666);
		for (NAMESPACE::vector<ConstClass>::iterator start = it; start != test.end(); start++)
		{
			std::cout << *start << std::endl;
		}
		test.erase((test.begin() + 1), (test.begin() + 10));
		std::cout << test.size() << std::endl;
		test.erase((test.end() - 1), test.end());
		test.erase((test.begin(), test.begin()));
		for (NAMESPACE::vector<ConstClass>::iterator start = it; start != test.end(); start++)
		{
			std::cout << *start << std::endl;
		}
		test.erase((test.end() + 1), (test.end() + 1));
		std::cout << test.size() << std::endl;
		test.erase(test.begin(), test.end());
		std::cout << test.size() << std::endl;
		if (capacity != test.capacity())
			std::cout << "Wrong capacity detected" << std::endl;
	}
	return (0);
}
