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
	std::cout << "*******   Testing int vector   *******" << std::endl;
	for (volatile int i = 0; i < 100; i++)
	{
		NAMESPACE::vector<int>				test;
		NAMESPACE::vector<int>::iterator	it;
		NAMESPACE::vector<int>::size_type	capacity;

		test.resize(21);
		test.resize(21);
		std::cout << test.size() << std::endl;
		itPrint<NAMESPACE::vector<int>::iterator >(test.begin(), test.end()); 
		test.resize(2000, 42);
		it = test.begin();
		capacity = test.capacity();
		test.resize(1, 6);
		test.resize(500);
		itPrint<NAMESPACE::vector<int>::iterator >(it, test.end()); 
		std::cout << test.size() << std::endl;
		std::cout << (capacity == test.capacity() ? "true" : " false") << std::endl;
	}
	std::cout << "*******   Testing std::string vector   *******" << std::endl;;
	for (volatile int i = 0; i < 100; i++)
	{
		NAMESPACE::vector<std::string>				test;
		NAMESPACE::vector<std::string>::iterator	it;
		NAMESPACE::vector<std::string>::size_type	capacity;

		test.resize(21);
		test.resize(21);
		std::cout << test.size() << std::endl;
		itPrint<NAMESPACE::vector<std::string>::iterator >(test.begin(), test.end()); 
		test.resize(2000, std::string("Hi"));
		it = test.begin();
		capacity = test.capacity();
		test.resize(1, std::string("Bye"));
		itPrint<NAMESPACE::vector<std::string>::iterator >(test.begin(), test.end()); 
		test.resize(500);
		itPrint<NAMESPACE::vector<std::string>::iterator >(it, test.end()); 
		std::cout << test.size() << std::endl;
		std::cout << (capacity == test.capacity() ? "true" : " false") << std::endl;
	}
	std::cout << "*******   Testing ConstClass vector   *******" << std::endl;;
	for (volatile int i = 0; i < 100; i++)
	{
		std::cout << i << std::endl;
		NAMESPACE::vector<ConstClass>	test;

		test.reserve(50);
		test.resize(10, ConstClass(10));
		std::cout << test.size() << std::endl;
		std::cout << test.capacity() << std::endl;
		itPrint<NAMESPACE::vector<ConstClass>::iterator >(test.begin(), test.end()); 
		test.resize(1, ConstClass(2));
		test.resize(33, ConstClass(42));
		std::cout << test.size() << std::endl;
		std::cout << test.capacity() << std::endl;
		itPrint<NAMESPACE::vector<ConstClass>::iterator >(test.begin(), test.end()); 
		test.resize(0, ConstClass(21));
		std::cout << test.size() << std::endl;
		std::cout << test.capacity() << std::endl;
		itPrint<NAMESPACE::vector<ConstClass>::iterator >(test.begin(), test.end()); 
	}
	return (0);
}
