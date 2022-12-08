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
		NAMESPACE::vector<int>				test;

		for (NAMESPACE::vector<int>::iterator start = test.begin(); start != test.end(); start++)
		{
			std::cout << *start << std::endl;
		}
	}
	std::cout << "*******   Testing int vector   *******" << std::endl;
	{
		NAMESPACE::vector<int>				test(25, 5);
		NAMESPACE::vector<int>::iterator	tmp;

		for (NAMESPACE::vector<int>::iterator start = test.begin(); start != test.end(); start++)
		{
			std::cout << *start << std::endl;
		}
		tmp = test.begin();
		tmp++;
		*tmp = 0;
		++tmp;
		*tmp = -1;
		tmp+= 2;
		*tmp = 6;
		std::cout << *(tmp - 1) << " - " << *(tmp + 1) << std::endl;
		std::cout << *((--tmp)--) << " & " << *tmp << std::endl;
		std::cout << (test.end() - tmp) << std::endl;
		std::cout << (tmp > tmp ? "true" : "false") << " " << (tmp <= tmp ? "true" : "false") << " " << (tmp == test.begin() ? "true" : "false") << std::endl;
	}

	std::cout << "*******   Testing std::string vector   *******" << std::endl;
	{
		NAMESPACE::vector<std::string>					test(9, std::string("Hello"));
		NAMESPACE::vector<std::string>::iterator		it = test.begin();
		NAMESPACE::vector<std::string>::const_iterator	it_const = test.end();

		it_const = it;
		std::cout << (it > it_const ? "true" : "false") << " " << (it_const <= it ? "true" : "false") << " " << (it == it_const ? "true" : "false") << std::endl;
		for (; it_const != test.end(); it_const++)
		{
			std::cout << *it_const << std::endl;
		}
		*it = std::string("Bye");
		while (--it_const >= test.begin())
		{
			std::cout << *it_const << std::endl;
		}
		std::cout << *(it_const + 1) << std::endl;
		std::cout << it_const[1] << std::endl;
		it[1] = std::string("Oups");
		std::cout << it_const[2] << std::endl;
	}
	return (0);
}
