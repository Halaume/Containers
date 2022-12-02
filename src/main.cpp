/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:23:53 by ghanquer          #+#    #+#             */
/*   Updated: 2022/12/02 17:18:23 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/stack.hpp"
#include "../inc/vector.hpp"
#include "../inc/map.hpp"

#include <vector>
#include <iostream>
#include <stack>
#include <list>
#include <typeinfo>
#include <string>
#include <sys/time.h>
#include <limits>

#ifndef NAMESPACE
#define NAMESPACE ft
#endif

void	do_stack(void);
void	do_vector(void);
void	do_map(void);

int main(void)
{
//	do_stack();
//	do_vector();
	do_map();

	return (0);
}

/*
#ifndef PREC
# define PREC 1
#endif

#define MAXSIZE (((std::size_t)std::numeric_limits<int>::max() / sizeof(int))/4)

#define ROUND(x) ((x - 1 < 0)? 1 : (int)x)

class	Clock {
	public:
		Clock(void) {gettimeofday(&_time, NULL);};
		long time(void) {struct timeval now; gettimeofday(&now, NULL); return (((now.tv_sec * 1000) - (_time.tv_sec * 1000)) + (now.tv_usec / 1000) - (_time.tv_usec / 1000));}
		void p(void) {long tmp = time(); std::cout << tmp/1000 << "." << tmp%1000 << "s ";}
	private:
		struct timeval _time;
};

int main () {
	{
		std::cerr << "### TEST CONSTRUCTOR VECTOR ###" << std::endl;
		std::cerr << std::endl;
		{
			Clock test;
			for (int i = 0; i < 100000 * PREC; i++) {
				for (int j = 0; j < 50000; j++)
					NAMESPACE::vector<std::string> v;
				std::cerr << (i+1)/(1000 * PREC) << "." << (i+1)%(1000 * PREC) << "%   " << '\r';
				std::cout.clear();
			}
			test.p();
			std::cout << "vector default constructor" << std::endl;
		}
		std::cerr << std::endl;
		{
			Clock test;
			for (int i = 0; i < 1 * PREC; i++) {
				NAMESPACE::vector<int> v1(MAXSIZE, 1);
				std::cerr << (i+1)/(0.01 * PREC) << "." << (i+1)%(ROUND(0.01 * PREC)) << "%   " << '\r';
			}
			test.p();
			std::cout << "vector value constructor" << std::endl;
		}
		std::cerr << std::endl;
		{
			NAMESPACE::vector<int> vec(MAXSIZE, 42);
			Clock test;
			for (int i = 0; i < 1 * PREC; i++) {
				NAMESPACE::vector<int> v1(vec.begin(), vec.end());
				std::cerr << (i+1)/(0.01 * PREC) << "." << (i+1)%(ROUND(0.01 * PREC)) << "%   " << '\r';
				std::cout.clear();
			}
			test.p();
			std::cout << "vector iterator constructor" << std::endl;
		}
		std::cerr << std::endl;
		{
			Clock test;

			NAMESPACE::vector<int> v1(MAXSIZE, 21);
			NAMESPACE::vector<NAMESPACE::vector<int> >v2 (1, v1);
			NAMESPACE::vector<NAMESPACE::vector<NAMESPACE::vector<int> > > v3(1, v2);
			for (int i = 0; i < 1 * PREC; i++) {
				NAMESPACE::vector<NAMESPACE::vector<NAMESPACE::vector<int> > > vector1(v3);

				std::cerr << (i+1)/(0.01 * PREC) << "." << (i+1)%(ROUND(0.01 * PREC)) << "%   " << '\r';
				std::cout.clear();
			}
			test.p();
			std::cout << "vector copy constructor" << std::endl;
		}
		std::cerr << std::endl;
	}
	{
		std::cerr << "### TEST OPERATOR= ###" << std::endl;
		std::cerr << std::endl;
		{
			Clock test;

			NAMESPACE::vector<int> v1(MAXSIZE, 24);
			NAMESPACE::vector<int> v2;
			for (int i = 0; i < 1 * PREC; i++) {
				v2 = v1;
				v1 = v2;
				std::cerr << (i+1)/(0.01 * PREC) << "." << (i+1)%(ROUND(0.01 * PREC)) << "%   " << '\r';
			}
			test.p();
			std::cout << "vector operator =" << std::endl;
		}
		std::cerr << std::endl;
	}
	{
		std::cerr << "### TEST ASSIGN ###" << std::endl;
		std::cerr << std::endl;
		{
			Clock test;

			NAMESPACE::vector<int> v;
			for (int i = 0; i < 1 * PREC; i++) {
				v.assign(MAXSIZE, 42);
				std::cerr << (i+1)/(0.01 * PREC) << "." << (i+1)%(ROUND(0.01 * PREC)) << "%   " << '\r';
			}
			test.p();
			std::cout << "vector assign value" << std::endl;
		}
		std::cerr << std::endl;
		{
			Clock test;

			NAMESPACE::vector<int> v(MAXSIZE, 2147483647);
			NAMESPACE::vector<int> v2;
			for (int i = 0; i < 1 * PREC; i++) {
				v2.assign(v.begin(), v.end());
				std::cerr << (i+1)/(0.01 * PREC) << "." << (i+1)%(ROUND(0.01 * PREC)) << "%   " << '\r';
			}
			test.p();
			std::cout << "vector assign iterator" << std::endl;
		}
		std::cerr << std::endl;
		{
			Clock test;

			int	lst[1000000];
			for (int i = 0; i < 1000000; i++)
				lst[i] = 42;
			NAMESPACE::vector<int> v;
			for (int i = 0; i < 1 * PREC; i++) {
				v.assign(lst, lst + 1000000);
				std::cerr << (i+1)/(0.01 * PREC) << "." << (i+1)%(ROUND(0.01 * PREC)) << "%   " << '\r';
			}
			test.p();
			std::cout << "vector assign InputIterator" << std::endl;
		}
		std::cerr << std::endl;
	}
	{
		std::cerr << "### TEST RESERVE ###" << std::endl;
		std::cerr << std::endl;
		{
			Clock test;

			for (int i = 0; i < 1 * PREC; i++) {
				NAMESPACE::vector<int> v(MAXSIZE, 42);
				v.reserve(MAXSIZE);
				std::cerr << (i+1)/(0.01 * PREC) << "." << (i+1)%(ROUND(0.01 * PREC)) << "%   " << '\r';
			}
			test.p();
			std::cout << "vector reserve capacity" << std::endl;
		}
		std::cerr << std::endl;
	}
	{
		std::cerr << "### TEST CLEAR ###" << std::endl;
		std::cerr << std::endl;
		{
			Clock test;

			for (int i = 0; i < 1 * PREC; i++) {
				NAMESPACE::vector<int> v(MAXSIZE, 42);
				v.clear();
				std::cerr << (i+1)/(0.01 * PREC) << "." << (i+1)%(ROUND(0.01 * PREC)) << "%   " << '\r';
			}
			test.p();
			std::cout << "vector create clear" << std::endl;
		}
		std::cerr << std::endl;
	}
	{
		std::cerr << "### TEST INSERT ###" << std::endl;
		std::cerr << std::endl;
		{
			Clock test;

			for (int i = 0; i < 1 * PREC; i++) {
				NAMESPACE::vector<int> v(MAXSIZE, 42);
				v.insert(v.begin() + MAXSIZE/2, 41);
				std::cerr << (i+1)/(0.01 * PREC) << "." << (i+1)%(ROUND(0.01 * PREC)) << "%   " << '\r';
			}
			test.p();
			std::cout << "vector insert val" << std::endl;
		}
		std::cerr << std::endl;
		{
			Clock test;

			for (int i = 0; i < 1 * PREC; i++) {
				NAMESPACE::vector<int> v(1000, 42);
				v.insert(v.begin(), MAXSIZE/4, 21);
				std::cerr << (i+1)/(0.01 * PREC) << "." << (i+1)%(ROUND(0.01 * PREC)) << "%   " << '\r';
			}
			test.p();
			std::cout << "vector insert count" << std::endl;
		}
		std::cerr << std::endl;
		{
			Clock test;

			NAMESPACE::vector<int> v2(MAXSIZE, 42);
			for (int i = 0; i < 1 * PREC; i++) {
				NAMESPACE::vector<int> v(1000, 42);
				v.insert(v.begin() + 500, v2.begin(), v2.end());
				std::cerr << (i+1)/(0.01 * PREC) << "." << (i+1)%(ROUND(0.01 * PREC)) << "%   " << '\r';
			}
			test.p();
			std::cout << "vector insert iterator" << std::endl;
		}
		std::cerr << std::endl;
		{
			Clock test;

			std::list<int> v2(MAXSIZE/40, 42);
			for (int i = 0; i < 1 * PREC; i++) {
				NAMESPACE::vector<int> v(1000, 42);
				v.insert(v.begin() + 500, v2.begin(), v2.end());
				std::cerr << (i+1)/(0.01 * PREC) << "." << (i+1)%(ROUND(0.01 * PREC)) << "%   " << '\r';
			}
			test.p();
			std::cout << "vector insert InputIterator" << std::endl;
		}
		std::cerr << std::endl;
	}
	{
		std::cerr << "### TEST ERASE ###" << std::endl;
		std::cerr << std::endl;
		{
			Clock test;

			for (int i = 0; i < 1 * PREC; i++) {
				NAMESPACE::vector<int> v(10000, 42);
				while (v.size()) {
					v.erase(v.begin());
				}
				std::cerr << (i+1)/(0.01 * PREC) << "." << (i+1)%(ROUND(0.01 * PREC)) << "%   " << '\r';
			}
			test.p();
			std::cout << "vector erase value" << std::endl;
		}
		std::cerr << std::endl;
		{
			Clock test;

			for (int i = 0; i < 1 * PREC; i++) {
				NAMESPACE::vector<int> v(1000000, 42);
				while (v.size()) {
					if (v.size() > 1000) {
						v.erase(v.begin(), v.begin() + 1000);
					} else {
						v.erase(v.begin());
					}
				}
				std::cerr << (i+1)/(0.01 * PREC) << "." << (i+1)%(ROUND(0.01 * PREC)) << "%   " << '\r';
			}
			test.p();
			std::cout << "vector erase range" << std::endl;
		}
		std::cerr << std::endl;
	}
	{
		std::cerr << "### TEST PUSH_BACK ###" << std::endl;
		std::cerr << std::endl;
		{
			Clock test;

			for (int i = 0; i < 1 * PREC; i++) {
				NAMESPACE::vector<int> v;
				while (v.size() < 10000000) {
					v.push_back(42);
				}
				std::cerr << (i+1)/(0.01 * PREC) << "." << (i+1)%(ROUND(0.01 * PREC)) << "%   " << '\r';
			}
			test.p();
			std::cout << "vector push_back value" << std::endl;
		}
		std::cerr << std::endl;
	}
	{
		std::cout << "### TEST POP_BACK ###" << std::endl;
		std::cerr << std::endl;
		{
			Clock test;

			for (int i = 0; i < 1 * PREC; i++) {
				NAMESPACE::vector<int> v(10000000, 42);
				while (v.size()) {
					v.pop_back();
				}
				std::cerr << (i+1)/(0.01 * PREC) << "." << (i+1)%(ROUND(0.01 * PREC)) << "%   " << '\r';
			}
			test.p();
			std::cout << "vector pop_back value" << std::endl;
		}
		std::cerr << std::endl;
	}
	{
		std::cerr << "### TEST RESIZE ###" << std::endl;
		std::cerr << std::endl;
		{
			Clock test;

			for (int i = 0; i < 1 * PREC; i++) {
				NAMESPACE::vector<int> v;
				v.resize(MAXSIZE);
				v.resize(MAXSIZE/100);
				std::cerr << (i+1)/(0.01 * PREC) << "." << (i+1)%(ROUND(0.01 * PREC)) << "%   " << '\r';
			}
			test.p();
			std::cout << "vector resize range" << std::endl;
		}
		std::cerr << std::endl;
	}
	{
		std::cerr << "### TEST SWAP ###" << std::endl;
		std::cerr << std::endl;
		{
			Clock test;

			NAMESPACE::vector<int> v(MAXSIZE, 42);
			NAMESPACE::vector<int> v2(MAXSIZE, 21);

			for (int i = 0; i < 1 * PREC; i++) {
				v.swap(v2);
				v2.swap(v);
				std::cerr << (i+1)/(0.01 * PREC) << "." << (i+1)%(ROUND(0.01 * PREC)) << "%   " << '\r';
			}
			test.p();
			std::cout << "vector swap member" << std::endl;
		}
		std::cerr << std::endl;
		{
			Clock test;

			NAMESPACE::vector<int> v(MAXSIZE, 42);
			NAMESPACE::vector<int> v2(MAXSIZE, 21);

			for (int i = 0; i < 1 * PREC; i++) {
				NAMESPACE::swap(v, v2);
				std::cerr << (i+1)/(0.01 * PREC) << "." << (i+1)%(ROUND(0.01 * PREC)) << "%   " << '\r';
			}
			test.p();
			std::cout << "vector swap namespace" << std::endl;
		}
	}
}
*/
