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
		NAMESPACE::vector<int>				test2(10, 55);
		NAMESPACE::vector<int>				test3(11, 55);
		NAMESPACE::vector<int>				test4(10, 42);
		NAMESPACE::vector<int>				test5;

		std::cout << (test == test2) << " " << (test != test2) << " " << (test < test2) << " " << (test <= test2) << " " << (test > test2) << " " << (test >= test2) << std::endl;

		std::cout << (test == test3) << " " << (test != test3) << " " << (test < test3) << " " << (test <= test3) << " " << (test > test3) << " " << (test >= test3) << std::endl;

		std::cout << (test == test4) << " " << (test != test4) << " " << (test < test4) << " " << (test <= test4) << " " << (test > test4) << " " << (test >= test4) << std::endl;

		std::cout << (test == test5) << " " << (test != test5) << " " << (test < test5) << " " << (test <= test5) << " " << (test > test5) << " " << (test >= test5) << std::endl;
	}
	return (0);
}
