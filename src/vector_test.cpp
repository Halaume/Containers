/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_test.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:41:02 by ghanquer          #+#    #+#             */
/*   Updated: 2022/11/16 13:43:02 by ghanquer         ###   ########.fr       */
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

void	do_vector()
{
	std::cout << std::endl << "---VECTOR---" << std::endl << std::endl;
	NAMESPACE::vector<int> v2;

	v2.push_back(5);

	std::cout << "BEFORE" << std::endl;
	for (size_t i = 0; i < v2.size(); i++)
		std::cout << v2[i] << std::endl;
	std::cout << v2.size() << std::endl;
	std::cout << v2.capacity() << std::endl;
	std::cout << "AFTER" << std::endl;

	NAMESPACE::vector<int>::iterator it = v2.erase(v2.begin());

	for (size_t i = 0; i < v2.size(); i++)
		std::cout << v2[i] << std::endl;
	std::cout << v2.size() << std::endl;
	std::cout << v2.capacity() << std::endl;

	(void)it;
}
