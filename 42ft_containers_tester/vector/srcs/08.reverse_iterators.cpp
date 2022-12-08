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
		NAMESPACE::vector<int>						test;
		NAMESPACE::vector<int>::reverse_iterator	tmp = test.rbegin();

		for (NAMESPACE::vector<int>::const_reverse_iterator start = test.rbegin(); start != test.rend(); start++)
		{
			std::cout << *start << std::endl;
		}
		std::cout << ( tmp == test.rend() ? "true" : "false") << std::endl;
	}
	std::cout << "*******   Testing int vector   *******" << std::endl;
	{
		NAMESPACE::vector<int>						test(25, 5);
		NAMESPACE::vector<int>::iterator			tmp = test.begin();
		NAMESPACE::vector<int>::reverse_iterator	rtmp(tmp);

		for (NAMESPACE::vector<int>::reverse_iterator start = test.rbegin(); start != test.rend(); start++)
		{
			std::cout << *start << std::endl;
		}
		std::cout << ( rtmp == test.rend() ? "true" : "false") << std::endl;
		rtmp--;
		*rtmp = 0;
		--rtmp;
		*rtmp = -1;
		rtmp-= 2;
		*rtmp = 6;
		std::cout << *(rtmp + 1) << " - " << *(rtmp - 1) << std::endl;
		std::cout << *((++rtmp)++) << " & " << *rtmp << std::endl;
		std::cout << (test.rend() - rtmp) << std::endl;
		std::cout << (rtmp > rtmp ? "true" : "false") << " " << (rtmp <= rtmp ? "true" : "false") << " " << (rtmp == test.rbegin() ? "true" : "false") << std::endl;
	}

	std::cout << "*******   Testing std::string vector   *******" << std::endl;
	{
		NAMESPACE::vector<std::string>							test(9, std::string("Hello"));
		NAMESPACE::vector<std::string>::reverse_iterator		it = test.rbegin();
		NAMESPACE::vector<std::string>::const_reverse_iterator	it_const = test.rend();

		it_const = it;
		std::cout << (it > it_const ? "true" : "false") << " " << (it_const <= it ? "true" : "false") << " " << (it == it_const ? "true" : "false") << std::endl;
		for (; it_const != test.rend(); it_const++)
		{
			std::cout << *it_const << std::endl;
		}
		*it = std::string("Bye");
		while (--it_const >= test.rbegin())
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
