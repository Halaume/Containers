/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_test.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:41:02 by ghanquer          #+#    #+#             */
/*   Updated: 2023/01/27 18:21:30 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/stack.hpp"
#include "../inc/vector.hpp"

#include <stack>
#include <iostream>
#include <vector>

#ifndef NAMESPACE
#define NAMESPACE ft
#endif

	template<typename T>
void	print_vec(T &	v)
{
	std::cout << "-----------" << std::endl;
	for (typename T::size_type i = 0; i < v.size(); i++)
		std::cout << v[i] << " | ";
	std::cout << std::endl << "-----------" << std::endl;
	std::cout << "Size : " << v.size() << std::endl;
	std::cout << "Capacity : " << v.capacity() << std::endl << std::endl;
}

	template<typename T>
void	print_comp_vec(T	v1, T	v2)
{
	std::cout << "v1 == v2 : " << (v1 == v2 ? "true" : "false") << std::endl;
	std::cout << "v1 != v2 : " << (v1 != v2 ? "true" : "false") << std::endl;
	std::cout << "v1 < v2 : " << (v1 < v2 ? "true" : "false") << std::endl;
	std::cout << "v1 <= v2 : " << (v1 <= v2 ? "true" : "false") << std::endl;
	std::cout << "v1 > v2 : " << (v1 > v2 ? "true" : "false") << std::endl;
	std::cout << "v1 >= v2 : " << (v1 >= v2 ? "true" : "false") << std::endl;
}

void	test_freestyle(void)
{
			NAMESPACE::vector<int>	test;

			test.reserve(15);
			test.assign(10, 10);
			std::cout << test.size() << std::endl;
			std::cout << test.capacity() << std::endl;
			for (NAMESPACE::vector<int>::iterator start = test.begin(); start != test.end(); start++)
				std::cout << *start << std::endl;
			test.assign(3, (2));
			std::cout << test.size() << std::endl;
			std::cout << test.capacity() << std::endl;
			for (NAMESPACE::vector<int>::iterator start = test.begin(); start != test.end(); start++)
				std::cout << *start << std::endl;
			test.assign(20, (5));
			std::cout << test.size() << std::endl;
			for (NAMESPACE::vector<int>::iterator start = test.begin(); start != test.end(); start++)
				std::cout << *start << std::endl;
}

void	do_vector()
{
	std::cout << std::endl << "---VECTOR---" << std::endl << std::endl;
	std::cout << std::endl << "---Constructor---" << std::endl << std::endl;

	NAMESPACE::vector<int> v1;
	NAMESPACE::vector<int> v2;
	NAMESPACE::vector<int> v3;

	v3.push_back(5);
	v3.push_back(10);
	v3.push_back(15);

	NAMESPACE::vector<int> v4(v3.begin(), v3.end());
	NAMESPACE::vector<int> v5(10, 5);
	print_vec(v4);
	print_vec(v5);

	print_comp_vec(v1, v2);

	std::cout << std::endl << "---Push_back---" << std::endl << std::endl;
	std::cout << "BEFORE" << std::endl;
	print_vec(v2);
	v2.push_back(5);
	v2.push_back(10);
	v2.push_back(15);
	std::cout << "AFTER" << std::endl;
	print_vec(v2);

	std::cout << std::endl << "---Pop_back---" << std::endl << std::endl;
	std::cout << "BEFORE" << std::endl;
	print_vec(v2);
	v2.pop_back();
	std::cout << "AFTER" << std::endl;
	print_vec(v2);


	v2.push_back(15);
	v2.push_back(15);
	v2.push_back(15);
	v2.push_back(15);
	v2.push_back(15);
	v2.push_back(17);
	v2.push_back(17);
	v2.push_back(17);
	v2.push_back(17);
	v2.push_back(17);
	std::cout << std::endl << "---Erase---" << std::endl << std::endl;
	std::cout << "BEFORE" << std::endl;
	print_vec(v2);
	v2.erase(v2.end() - 1);
	v2.erase(v2.end() - 5);
	v2.erase(v2.begin() + 1, v2.end() - 3);
	std::cout << "AFTER" << std::endl;
	print_vec(v2);


	std::cout << std::endl << "---Assign---" << std::endl << std::endl;
	std::cout << "BEFORE" << std::endl;
	print_vec(v2);
	v2.assign(v2.begin() + 2, v2.end() - 1);
	v2.assign(20, 4);
	std::cout << "AFTER" << std::endl;
	print_vec(v2);

	v2.assign(10, 4);
	std::cout << std::endl << "---Insert---" << std::endl << std::endl;
	std::cout << "BEFORE" << std::endl;
	print_vec(v2);
	v2.insert(v2.begin() + 4, 6);
	print_vec(v2);
	v2.insert(v2.begin() + 4, 2, 5);
	print_vec(v2);
	v2.insert(v2.begin() + 4, 5, 9);
	print_vec(v2);
	v2.insert(v2.begin(), v2.begin() + 2, v2.begin() + 3);
	print_vec(v2);
	v2.insert(v2.begin(), v2.begin(), v2.begin() + 1);
	print_vec(v2);
	std::cout << "AFTER" << std::endl;
	print_vec(v2);

	std::cout << std::endl << "-----TEST BDETUNE-----" << std::endl << std::endl;

	test_freestyle();
}
