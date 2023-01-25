/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:23:53 by ghanquer          #+#    #+#             */
/*   Updated: 2023/01/25 16:17:31 by ghanquer         ###   ########.fr       */
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

int main(void)
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

	return (0);
}
