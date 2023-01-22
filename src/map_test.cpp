/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_test.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 17:40:05 by ghanquer          #+#    #+#             */
/*   Updated: 2023/01/22 17:33:57 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/stack.hpp"
#include "../inc/vector.hpp"
#include "../inc/rbTree.hpp"
#include "../inc/map.hpp"
#include "../inc/pair.hpp"

#include "../../bdetune_42ftcontainers_tester/map/includes/customCompare.hpp"
#include "../../bdetune_42ftcontainers_tester/map/includes/ConstClass.hpp"

#include <stack>
#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <map>

#ifndef NAMESPACE
#define NAMESPACE ft
#endif

/* TRYING TNATON DISPLAY */

struct Trunk
{
	Trunk *prev;
	std::string str;

	Trunk(Trunk *previ, std::string stri)
	{
		this->prev = previ;
		this->str = stri;
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
template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
	o << "key: " << iterator->first << " | value: " << iterator->second;
	if (nl)
		o << std::endl;
	return ("");
}

template <typename T_MAP>
void	printSize(T_MAP const &mp, bool print_content = 1)
{
	std::cout << "size: " << mp.size() << std::endl;
	std::cout << "max_size: " << mp.max_size() << std::endl;
	if (print_content)
	{
		typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << printPair(it, false) << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}
static int iter = 0;
template <typename MAP, typename U>
void	ft_insert(MAP &mp, U param)
{
	ft::pair<ft::map<int, std::string>::iterator, bool> tmp;

	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	tmp = mp.insert(param);
	std::cout << "insert return: " << printPair(tmp.first);
	std::cout << "Created new node: " << tmp.second << std::endl;
	printSize(mp);
}

template <typename MAP, typename U, typename V>
void	ft_insert(MAP &mp, U param, V param2)
{
	ft::map<int, std::string>::iterator tmp;

	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	tmp = mp.insert(param, param2);
	std::cout << "insert return: " << printPair(tmp);
	printSize(mp);
}

int		test_mli(void)
{
	ft::map<int, std::string> mp, mp2;

	ft_insert(mp, ft::map<int, std::string>::value_type(42, "lol"));
	ft_insert(mp, ft::map<int, std::string>::value_type(42, "mdr"));

	ft_insert(mp, ft::map<int, std::string>::value_type(50, "mdr"));
	ft_insert(mp, ft::map<int, std::string>::value_type(35, "funny"));

	ft_insert(mp, ft::map<int, std::string>::value_type(45, "bunny"));
	ft_insert(mp, ft::map<int, std::string>::value_type(21, "fizz"));
	ft_insert(mp, ft::map<int, std::string>::value_type(38, "buzz"));

	ft_insert(mp, mp.begin(), ft::map<int, std::string>::value_type(55, "fuzzy"));

	ft_insert(mp2, mp2.begin(), ft::map<int, std::string>::value_type(1337, "beauty"));
	ft_insert(mp2, mp2.end(), ft::map<int, std::string>::value_type(1000, "Hello"));
	ft_insert(mp2, mp2.end(), ft::map<int, std::string>::value_type(1500, "World"));

	return (0);
}


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
	ft::pair<ft::map<int, int>::iterator, ft::map<int, int>::iterator>	eqr = my_map.equal_range(5);
	if (eqr.first != my_map.lower_bound(5) || eqr.second != my_map.upper_bound(5))
		std::cout << "Wrong equal range" << std::endl;
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

	test_mli();

}
