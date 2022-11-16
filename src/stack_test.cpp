/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_test.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:38:17 by ghanquer          #+#    #+#             */
/*   Updated: 2022/11/16 13:40:46 by ghanquer         ###   ########.fr       */
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

void	do_stack()
{
	std::cout << std::endl << "---STACK---" << std::endl << std::endl;

	NAMESPACE::stack<int, NAMESPACE::vector<int> > c1;
	c1.push(5);
	c1.push(4);
	c1.push(3);
	std::cout << c1.size() << std::endl;
	std::cout << c1.top() << std::endl;
	std::cout << c1.empty() << std::endl;
	c1.pop();
	std::cout << c1.size() << std::endl;

	NAMESPACE::stack<int, NAMESPACE::vector<int> > c2 = c1;
	std::cout << "-------------------" << std::endl;
	for (size_t i = 0; i <= c2.size(); i++)
	{
		std::cout << c2.top() << std::endl;
		c2.pop();
	}
	std::cout << "-------------------" << std::endl;
	std::cout << c1.size() << std::endl;
	std::cout << c2.size() << std::endl;
}
