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
		std::cout << i << std::endl;
		volatile NAMESPACE::vector<int>	test(i);
		volatile NAMESPACE::vector<int>	test1(i, (i - 1));
	}
	std::cout << "*******   Testing std::string vector   *******" << std::endl;;
	for (volatile int i = 0; i < 100; i++)
	{
		std::cout << i << std::endl;
		volatile NAMESPACE::vector<std::string>	test(i, std::string("Hello"));
	}
	std::cout << "*******   Testing ConstClass vector   *******" << std::endl;;
	for (volatile int i = 0; i < 100; i++)
	{
		std::cout << i << std::endl;
		volatile NAMESPACE::vector<ConstClass>	test(i);
		volatile NAMESPACE::vector<ConstClass>	test1(i, ConstClass(i -1));
	}
	return (0);
}
