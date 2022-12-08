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
		NAMESPACE::vector<int>	test(25, 10);
		int*					data;

		std::cout << test.front() << std::endl;
		std::cout << test.back() << std::endl;
		std::cout << test[0] << std::endl;
		data = test.data();
		for (int i = 0; i < 25; i++)
		{
			std::cout << data[i] << std::endl;
		}
		try
		{
			std::cout << test.at(1) << std::endl;
			std::cout << test.at(50) << std::endl;
		}
		catch (std::out_of_range const & e)
		{
			std::cout << "Exception caught" << std::endl;
		}
	}
	std::cout << "*******   Testing ConstClass vector   *******" << std::endl;
	for (volatile int i = 1; i < 100; i++)
	{
		std::cout << i << std::endl;
		NAMESPACE::vector<ConstClass>	test1(i, ConstClass(i -1));
		std::cout << (test1[0].getValue() == test1.front().getValue() ? "true" : "false") << std::endl;
		std::cout << (test1[i - 1].getValue() == test1.back().getValue() ? "true" : "false") << std::endl;
		std::cout << (test1.data() == &(*(test1.begin())) ? "true" : "false") << std::endl;
	}
	return (0);
}
