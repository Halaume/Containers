/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_test.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:41:02 by ghanquer          #+#    #+#             */
/*   Updated: 2022/11/17 16:21:25 by ghanquer         ###   ########.fr       */
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
void	print_vec(T	v)
{
	std::cout << "-----------" << std::endl;
	for (typename T::size_type i = 0; i < v.size(); i++)
		std::cout << v[i] << " add -> " << &v[i] << " | ";
	std::cout << std::endl << "-----------" << std::endl;
	std::cout << "Size : " << v.size() << std::endl;
	std::cout << "Capacity : " << v.capacity() << std::endl;
}

template<typename T>
void	print_comp_vec(T	v1, T	v2)
{
	std::cout << "v1 == v2" << (v1 == v2 ? "true" : "false") << std::endl;
	std::cout << "v1 != v2" << (v1 != v2 ? "true" : "false") << std::endl;
	std::cout << "v1 < v2" << (v1 < v2 ? "true" : "false") << std::endl;
	std::cout << "v1 <= v2" << (v1 <= v2 ? "true" : "false") << std::endl;
	std::cout << "v1 > v2" << (v1 > v2 ? "true" : "false") << std::endl;
	std::cout << "v1 >= v2" << (v1 >= v2 ? "true" : "false") << std::endl;
}

void	do_vector()
{
	std::cout << std::endl << "---VECTOR---" << std::endl << std::endl;
	NAMESPACE::vector<int> v1;
	NAMESPACE::vector<int> v2;

//	print_comp_vec(v1, v2);

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

	
	std::cout << std::endl << "---Erase---" << std::endl << std::endl;
	std::cout << "BEFORE" << std::endl;
	print_vec(v2);
	v2.erase(v2.begin());
	std::cout << "AFTER" << std::endl;
	print_vec(v2);
}
