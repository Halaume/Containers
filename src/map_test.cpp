/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_test.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 17:40:05 by ghanquer          #+#    #+#             */
/*   Updated: 2022/12/15 17:20:41 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/stack.hpp"
#include "../inc/vector.hpp"
#include "../inc/rbTree.hpp"
#include "../inc/map.hpp"
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

void printnode(ft::map<int, int>::Tree::node * & tmp) {
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

void printTree(ft::map<int, int>::Tree::node * root, Trunk *prev, bool isLeft) {
	if (!root || !root->value)
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

void    do_map( void )
{
	ft::map<int, int>		my_map;
	NAMESPACE::vector<int>	v;

	for (size_t i = 0; i < 20; i++)
		v.push_back(i);
	std::random_shuffle(v.begin(), v.end());
	for (size_t i = 0; i < 20; i++)
	{
		std::cout << "size = " << my_map.size() << std::endl;
		std::cout << v[i] << std::endl << "-------------------------" << std::endl;
		my_map.insert(ft::make_pair<int, int>(v[i], v[i]));
		printTree(my_map.base()._start, NULL, false);
		std::cout << "-------------------------" << std::endl;
	}
	std::cout << "size = " << my_map.size() << std::endl;
	ft::map<int, int>::iterator it = my_map.end();
	for (; it != my_map.begin(); it--)
	{
		if (it != my_map.end())
			std::cout << (*it).first << std::endl;

	}
	it = my_map.end();
	it--;

	ft::map<int, int>::reverse_iterator it3 = my_map.rend();
	std::cout << "-----------REVERSE---------" << std::endl;
	for (; it3 != my_map.rbegin(); it3--)
	{
		if (it3 != my_map.rend())
			std::cout << it3->first << std::endl;
	}
	std::cout << "-----------END--REVERSE-----" << std::endl;

	std::cout << "---------COPY---------" << std::endl;


	std::cout << "----------------Base Tree----------" << std::endl;
	printTree(my_map.base()._start, NULL, false);

	std::cout << "----------------Copied Tree----------" << std::endl;
	ft::map<int, int>		my_map2(my_map);
	printTree(my_map2.base()._start, NULL, false);

	std::cout << "----------------Copied = Tree----------" << std::endl;

	ft::map<int, int>		my_map3 = my_map;
	printTree(my_map3.base()._start, NULL, false);

	std::cout << "----------------Base Tree ERASE BEGIN----------" << std::endl;

	my_map.erase(my_map.begin());
	printTree(my_map.base()._start, NULL, false);
	
	std::cout << "----------------Copied Tree----------" << std::endl;
	
	printTree(my_map2.base()._start, NULL, false);

	std::cout << "----------------Copied = Tree----------" << std::endl;
	
	printTree(my_map3.base()._start, NULL, false);
	
	std::cout << "---------COPIED---------" << std::endl;


	std::cout << "---------GET THIS ITERATOR CONSTRUCTOR BABY---------" << std::endl;
	ft::map<int, int>		my_map4(my_map.begin(), my_map.end());
	printTree(my_map4.base()._start, NULL, false);

	std::cout << "---------Bound----------" << std::endl;
	std::cout << "---------UPPER----------" << std::endl;
	std::cout << "Upper Bound de 5 : ";
	(my_map.upper_bound(5) == my_map.end() ? std::cout << "Not found" : std::cout << (my_map.upper_bound(5))->first) << std::endl;
	std::cout << "Upper Bound de 50 : ";
	(my_map.upper_bound(50) == my_map.end() ? std::cout << "Not found" : std::cout << (my_map.upper_bound(50))->first) << std::endl;
	std::cout << "Upper Bound de -5 : ";
	(my_map.upper_bound(-5) == my_map.end() ? std::cout << "Not found" : std::cout << (my_map.upper_bound(-5))->first) << std::endl;
	std::cout << "---------LOWER----------" << std::endl;
	std::cout << "Lower Bound de 5 : ";
	(my_map.lower_bound(5) == my_map.end() ? std::cout << "Not found" : std::cout << (my_map.lower_bound(5))->first) << std::endl;
	std::cout << "Lower Bound de 50 : ";
	(my_map.lower_bound(50) == my_map.end() ? std::cout << "Not found" : std::cout << (my_map.lower_bound(50))->first) << std::endl;
	std::cout << "Lower Bound de -5 : ";
	(my_map.lower_bound(-5) == my_map.end() ? std::cout << "Not found" : std::cout << (my_map.lower_bound(-5))->first) << std::endl;
	std::cout << "---------End Bound----------" << std::endl;

	std::cout << "-----------ERASE---------" << std::endl;
	while (my_map.size())
	{
		ft::map<int, int>::iterator it2(my_map.begin());
		std::cout << "size = " << my_map.size() << std::endl;
		my_map.erase(it2);
		printTree(my_map.base()._start, NULL, false);
	}
	std::cout << "size = " << my_map.size() << std::endl;

	printTree(my_map.base()._start, NULL, false);
	std::cout << "-----------ERASED---------" << std::endl;
}
