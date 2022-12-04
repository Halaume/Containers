/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_test.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 17:40:05 by ghanquer          #+#    #+#             */
/*   Updated: 2022/12/04 11:17:17 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/stack.hpp"
#include "../inc/vector.hpp"
#include "../inc/rbTree.hpp"
#include "../inc/pair.hpp"

#include <stack>
#include <iostream>
#include <vector>
#include <algorithm>

#ifndef NAMESPACE
#define NAMESPACE ft
#endif

void printHelper(ft::RbTree<int, int>::node* root, std::string indent, bool last)
{
	if (root)
	{
		std::cout << indent;
		if (last)
		{
			std::cout << "R----";
			indent += "   ";
		}
		else
		{
			std::cout << "L----";
			indent += "|  ";
		}
		std::string sColor = root->color ? "RED" : "BLACK";
		std::cout << root->value->first << "(" << sColor << ")" << std::endl;
		printHelper(root->lchild, indent, false);
		printHelper(root->rchild, indent, true);
	}
}

void    do_map( void )
{
	ft::RbTree<int, int>    tree;
	NAMESPACE::vector<int>    v;
	for (size_t i = 0; i < 20; i++)
		v.push_back(i);
	std::random_shuffle(v.begin(), v.end());
	for (size_t i = 0; i < 20; i++)
	{
//		std::cout << v[i] << std::endl;
		tree.insert(ft::make_pair(v[i], v[i]));
	}
	printHelper(tree._start, "", true);
}
