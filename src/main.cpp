/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:23:53 by ghanquer          #+#    #+#             */
/*   Updated: 2023/01/25 18:01:05 by ghanquer         ###   ########.fr       */
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
void	do_set(void);

#include <iostream>
#include <string>
#include <deque>
#if 1 //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
//	namespace NAMESPACE = std;
#else
	#include <map.hpp>
	#include <stack.hpp>
	#include <vector.hpp>
#endif

#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};


#define COUNT (MAX_RAM / (int)sizeof(Buffer))

template<typename T>
class MutantStack : public NAMESPACE::stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename NAMESPACE::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};

int intra_main(int argc, char** argv) {
	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		return 1;
	}
	const int seed = atoi(argv[1]);
	srand(seed);

	NAMESPACE::vector<std::string> vector_str;
	NAMESPACE::vector<int> vector_int;
	NAMESPACE::stack<int> stack_int;
	NAMESPACE::vector<Buffer> vector_buffer;
	NAMESPACE::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
	NAMESPACE::map<int, int> map_int;

	for (int i = 0; i < COUNT; i++)
	{
		vector_buffer.push_back(Buffer());
	}

	for (int i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		vector_buffer[idx].idx = 5;
	}
	NAMESPACE::vector<Buffer>().swap(vector_buffer);

	try
	{
		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
		}
	}
	catch(const std::exception& e)
	{
		//NORMAL ! :P
	}
	
	for (int i = 0; i < COUNT; ++i)
	{
		map_int.insert(NAMESPACE::make_pair(rand(), rand()));
	}

	int sum = 0;
	for (int i = 0; i < 10000; i++)
	{
		int access = rand();
		sum += map_int[access];
	}
	std::cout << "should be constant with the same seed: " << sum << std::endl;

	{
		NAMESPACE::map<int, int> copy = map_int;
	}
	MutantStack<char> iterable_stack;
	for (char letter = 'a'; letter <= 'z'; letter++)
		iterable_stack.push(letter);
	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
	{
		std::cout << *it;
	}
	std::cout << std::endl;
	return (0);
}

int main(int argc, char **argv)
{
	std::cout << "----------STACK---------" << std::endl << std::endl;
	do_stack();
	std::cout << "----------END---------" << std::endl << std::endl;
	std::cout << "----------VECTOR---------" << std::endl << std::endl;
	do_vector();
	std::cout << "----------END---------" << std::endl << std::endl;
	std::cout << "----------MAP---------" << std::endl << std::endl;
	do_map();
	std::cout << "----------END---------" << std::endl << std::endl;
	std::cout << "----------SET---------" << std::endl << std::endl;
	do_set();
	std::cout << "----------END---------" << std::endl << std::endl;

	intra_main(argc, argv);
	return (0);
}
