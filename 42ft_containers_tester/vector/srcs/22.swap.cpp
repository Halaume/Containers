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
		NAMESPACE::vector<int>				test(10, 55);
		NAMESPACE::vector<int>				cpy(21, 42);
		NAMESPACE::vector<int>				cpy2;
		NAMESPACE::vector<int>::iterator	it;

		test.reserve(50);
		cpy.reserve(100);
		itPrint<NAMESPACE::vector<int>::iterator >(test.begin(), test.end()); 
		itPrint<NAMESPACE::vector<int>::iterator >(cpy.begin(), cpy.end());
		it = test.begin();
		test.swap(cpy);
		itPrint<NAMESPACE::vector<int>::iterator >(test.begin(), test.end()); 
		itPrint<NAMESPACE::vector<int>::iterator >(it, cpy.end()); 
		std::cout << test.size() << std::endl;
		std::cout << test.capacity() << std::endl;
		std::cout << cpy.size() << std::endl;
		std::cout << cpy.capacity() << std::endl;
		cpy.swap(cpy2);
		itPrint<NAMESPACE::vector<int>::iterator >(cpy.begin(), cpy.end()); 
		itPrint<NAMESPACE::vector<int>::iterator >(cpy2.begin(), cpy2.end()); 
		std::cout << cpy.size() << std::endl;
		std::cout << cpy.capacity() << std::endl;
		std::cout << cpy2.size() << std::endl;
		std::cout << cpy2.capacity() << std::endl;
	}
	std::cout << "*******   Testing ConstClass vector   *******" << std::endl;;
	for (volatile int i = 0; i < 100; i++)
	{
		NAMESPACE::vector<ConstClass>			test(10, ConstClass(55));
		NAMESPACE::vector<ConstClass>			cpy(21, ConstClass(42));
		NAMESPACE::vector<ConstClass>			cpy2;
		NAMESPACE::vector<ConstClass>::iterator	it;

		test.reserve(50);
		cpy.reserve(100);
		itPrint<NAMESPACE::vector<ConstClass>::iterator >(test.begin(), test.end()); 
		itPrint<NAMESPACE::vector<ConstClass>::iterator >(cpy.begin(), cpy.end()); 
		it = test.begin();
		NAMESPACE::swap(test, cpy);
		itPrint<NAMESPACE::vector<ConstClass>::iterator >(test.begin(), test.end()); 
		itPrint<NAMESPACE::vector<ConstClass>::iterator >(it, cpy.end()); 
		std::cout << test.size() << std::endl;
		std::cout << test.capacity() << std::endl;
		std::cout << cpy.size() << std::endl;
		std::cout << cpy.capacity() << std::endl;
		NAMESPACE::swap(cpy, cpy2);
		itPrint<NAMESPACE::vector<ConstClass>::iterator >(cpy.begin(), cpy.end()); 
		itPrint<NAMESPACE::vector<ConstClass>::iterator >(cpy2.begin(), cpy2.end()); 
		std::cout << cpy.size() << std::endl;
		std::cout << cpy.capacity() << std::endl;
		std::cout << cpy2.size() << std::endl;
		std::cout << cpy2.capacity() << std::endl;
	}
	return (0);
}
