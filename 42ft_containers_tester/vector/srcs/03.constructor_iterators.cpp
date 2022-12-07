#if ISFT == 1
# define NAMESPACE ft
# include "vector.hpp"
#else
# define NAMESPACE std
# include <vector>
#endif
#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include "ConstClass.hpp"

int	main(void)
{
	std::cout << "*******   Testing int vector   *******" << std::endl;
	{
		int	tab[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		for (volatile int i = 0; i < 100; i++)
		{
			std::cout << i << std::endl;
			volatile NAMESPACE::vector<int>	test(tab, tab+10);
		}
	}
	std::cout << "*******   Testing std::string vector   *******" << std::endl;
	{

		for (volatile int i = 0; i < 100; i++)
		{
			std::istringstream	str("0.0 0.1 1.2 5.3 6.4 8.9 10.4");
			std::cout << i << std::endl;
			volatile NAMESPACE::vector<double>	test((std::istream_iterator<double>(str)), (std::istream_iterator<double>()));
		}
	}
	std::cout << "*******   Testing ConstClass vector   *******" << std::endl;
	{
		ConstClass	tab[] = {ConstClass(), ConstClass(2), ConstClass(10)};
		for (volatile int i = 0; i < 100; i++)
		{
			std::cout << i << std::endl;
			volatile NAMESPACE::vector<ConstClass>	test(tab, tab+3);
		}
	}
	return (0);
}
