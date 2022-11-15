/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:23:53 by ghanquer          #+#    #+#             */
/*   Updated: 2022/11/15 15:59:17 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/stack.hpp"

#include <vector>
#include <iostream>
#include <stack>

#ifndef NAMESPACE
#define NAMESPACE ft
#endif

int main(void)
{
	NAMESPACE::stack<int, std::vector<int> > c1;
	c1.push(5);
	c1.push(4);
	c1.push(3);
	std::cout << c1.size() << std::endl;
	std::cout << c1.top() << std::endl;
	std::cout << c1.empty() << std::endl;
	c1.pop();
	std::cout << c1.size() << std::endl;

	NAMESPACE::stack<int, std::vector<int> > c2 = c1;
	std::cout << "-------------------" << std::endl;
	for (size_t i = 0; i <= c2.size(); i++)
	{
		std::cout << c2.top() << std::endl;
		c2.pop();
	}
	std::cout << "-------------------" << std::endl;
	std::cout << c1.size() << std::endl;
	std::cout << c2.size() << std::endl;

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

	return (0);
}
