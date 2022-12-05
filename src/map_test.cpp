/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_test.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 17:40:05 by ghanquer          #+#    #+#             */
/*   Updated: 2022/12/05 17:41:41 by ghanquer         ###   ########.fr       */
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

/* TRYING TNATON DISPLAY */

struct Trunk
{
	Trunk *prev;
	std::string str;

	Trunk(Trunk *prev, std::string str)
	{
		this->prev = prev;
		this->str = str;
	}
};

void showTrunks(Trunk *p)
{
	if (p == NULL) {
		return;
	}

	showTrunks(p->prev);
	std::cout << p->str;
}

void printnode(ft::RbTree<int, int>::node * & tmp) {
	if (!tmp) {
		std::cout << "Invalide insert" << std::endl;
		return ;
	}
	if (tmp->color)
		std::cout << "\033[0;90m"; 
	else
		std::cout << "\033[0;91m";
	std::cout << "Key : " << tmp->value->first << " | Val : " << tmp->value->second << "\033[0m" << std::endl;
}

void printTree(ft::RbTree<int, int>::node * root, Trunk *prev, bool isLeft) {
	if (root == NULL)
		return ;
	//    std::cout << "root : " << root->val.first << std::endl;
	std::string prev_str = "         ";
	Trunk *trunk = new Trunk(prev, prev_str);

	printTree(root->child[1], trunk, true);

	if (!prev) {
		trunk->str = "—————————";
	}
	else if (isLeft)
	{
		trunk->str = ".—————————";
		prev_str = "         |";
	}
	else {
		trunk->str = "`—————————";
		prev->str = prev_str;
	}

	showTrunks(trunk);
	if (!root->color)
		std::cout << "\033[0;90m"; 
	else
		std::cout << "\033[0;91m";
	std::cout << " " << root->value->first << "\033[0m" << std::endl;

	if (prev) {
		prev->str = prev_str;
	}
	trunk->str = "         |";

	printTree(root->child[0], trunk, false);
	delete trunk;
}

/* END */

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
		printHelper(root->child[0], indent, false);
		printHelper(root->child[1], indent, true);
	}
}

void    do_map( void )
{
	ft::RbTree<int, int>    tree;
	NAMESPACE::vector<int>    v;
/*	std::cout << 10 << std::endl << "-------------------------" << std::endl;
		tree.insert(ft::make_pair(10, 10));
		printTree(tree._start, NULL, false);
		std::cout << "-------------------------" << std::endl;
	std::cout << 11 << std::endl << "-------------------------" << std::endl;
		tree.insert(ft::make_pair(11, 11));
		printTree(tree._start, NULL, false);
		std::cout << "-------------------------" << std::endl;
	std::cout << 12 << std::endl << "-------------------------" << std::endl;
		tree.insert(ft::make_pair(12, 12));
		printTree(tree._start, NULL, false);
		std::cout << "-------------------------" << std::endl;
	std::cout << 13 << std::endl << "-------------------------" << std::endl;
		tree.insert(ft::make_pair(13, 13));
		printTree(tree._start, NULL, false);
		std::cout << "-------------------------" << std::endl;
*/


	for (size_t i = 0; i < 20; i++)
		v.push_back(i);
	std::random_shuffle(v.begin(), v.end());
	for (size_t i = 0; i < 20; i++)
	{
		//		std::cout << v[i] << std::endl;
		std::cout << v[i] << std::endl << "-------------------------" << std::endl;
		tree.insert(ft::make_pair(v[i], v[i]));
		printTree(tree._start, NULL, false);
		std::cout << "-------------------------" << std::endl;
	}
//	printHelper(tree._start, "", true);
//	printTree(tree._start, NULL, false);
}
