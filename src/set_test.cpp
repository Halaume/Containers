/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_test.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:32:35 by ghanquer          #+#    #+#             */
/*   Updated: 2023/01/27 18:18:10 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/stack.hpp"
#include "../inc/vector.hpp"
#include "../inc/rbTree.hpp"
#include "../inc/set.hpp"
#include "../inc/pair.hpp"

#include <stack>
#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <set>
#include <string>

#ifndef NAMESPACE
#define NAMESPACE ft
#endif

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

typedef ft::RbTree<ft::set<int>::value_type, ft::set<int>::value_compare, ft::set<int>::allocator_type> Tree;

void printnode(Tree::node * & tmp) {
	if (!tmp) {
		std::cout << "Invalide insert" << std::endl;
		return ;
	}
	if (tmp->color)
		std::cout << "\033[0;90m"; 
	else
		std::cout << "\033[0;91m";
	std::cout << "Key : " << *(tmp->value) << "\033[0m" << std::endl;
}

void printTree(Tree::node * root, Trunk *prev, bool isLeft) {
	if (!root || !root->value)
		return ;
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
	std::cout << " " << *(root->value) << "\033[0m" << std::endl;

	if (prev) {
		prev->str = prev_str;
	}
	trunk->str = "         |";

	printTree(root->child[0], trunk, false);
	delete trunk;
}

template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
	o << "key: " << std::endl;
	o << *iterator << std::endl;
	if (nl)
		o << std::endl;
	return ("");
}

template <typename T_set>
void	printSize(T_set const &mp, bool print_content = 1)
{
	std::cout << "size: " << mp.size() << std::endl;
	if (print_content)
	{
		typename T_set::const_iterator it = mp.begin(), ite = mp.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << printPair(it, false) << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}
static int iter = 0;
template <typename set, typename U>
void	ft_insert(set &mp, U param)
{
	NAMESPACE::pair<NAMESPACE::set<int>::iterator, bool>	tmp;

	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	tmp = mp.insert(param);
	//printTree(mp.begin().base(), NULL, false);
	std::cout << "insert return: " << printPair(tmp.first);
	std::cout << "Created new node: " << *(tmp.first) << std::endl;
	printSize(mp);
}

template <typename set, typename U, typename V>
void	ft_insert(set &mp, U param, V param2)
{
	NAMESPACE::set<int>::iterator tmp;

	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	tmp = mp.insert(param, param2);
	std::cout << "insert return: " << printPair(tmp);
	printSize(mp);
}

int		test_mli(void)
{
	NAMESPACE::set<int> mp, mp2;

	ft_insert(mp, NAMESPACE::set<int>::value_type(42));
	ft_insert(mp, NAMESPACE::set<int>::value_type(42));

	ft_insert(mp, NAMESPACE::set<int>::value_type(50));
	ft_insert(mp, NAMESPACE::set<int>::value_type(35));

	ft_insert(mp, NAMESPACE::set<int>::value_type(45));
	ft_insert(mp, NAMESPACE::set<int>::value_type(21));
	ft_insert(mp, NAMESPACE::set<int>::value_type(38));

	ft_insert(mp, mp.begin(), NAMESPACE::set<int>::value_type(55));

	ft_insert(mp2, mp2.begin(), NAMESPACE::set<int>::value_type(1337));
	ft_insert(mp2, mp2.end(), NAMESPACE::set<int>::value_type(1000));
	ft_insert(mp2, mp2.end(), NAMESPACE::set<int>::value_type(1500));

	return (0);
}


void    do_set( void )
{
	NAMESPACE::set<int>		my_set;
	NAMESPACE::vector<int>	v;

	for (size_t i = 0; i < 20; i++)
		v.push_back(i);
	std::random_shuffle(v.begin(), v.end());
	for (size_t i = 0; i < 20; i++)
	{
		std::cout << "size = " << my_set.size() << std::endl;
		std::cout << v[i] << std::endl << "-------------------------" << std::endl;
		my_set.insert(v[i]);
		//printTree(my_set.begin().base(), NULL, false);
		std::cout << "-------------------------" << std::endl;
	}
	std::cout << "size = " << my_set.size() << std::endl;
	NAMESPACE::set<int>::iterator it = my_set.end();
	for (; it != my_set.begin(); it--)
	{
		if (it != my_set.end())
			std::cout << *it << std::endl;

	}
	it = my_set.end();
	it--;

	NAMESPACE::set<int>::reverse_iterator it3 = my_set.rend();
	std::cout << "-----------REVERSE---------" << std::endl;
	for (; it3 != my_set.rbegin(); it3--)
	{
		if (it3 != my_set.rend())
			std::cout << *it3 << std::endl;
	}
	std::cout << "-----------END--REVERSE-----" << std::endl;

	std::cout << "---------COPY---------" << std::endl;


	std::cout << "----------------Base Tree----------" << std::endl;
	//printTree(my_set.begin().base(), NULL, false);

	std::cout << "----------------Copied Tree----------" << std::endl;
	NAMESPACE::set<int>		my_set2(my_set);
	//printTree(my_set2.begin().base(), NULL, false);

	std::cout << "----------------Copied = Tree----------" << std::endl;

	NAMESPACE::set<int>		my_set3 = my_set;
	//printTree(my_set3.begin().base(), NULL, false);

	std::cout << "----------------Base Tree ERASE BEGIN----------" << std::endl;

	my_set.erase(my_set.begin());
	//printTree(my_set.begin().base(), NULL, false);
	
	std::cout << "----------------Copied Tree----------" << std::endl;
	
	//printTree(my_set2.begin().base(), NULL, false);

	std::cout << "----------------Copied = Tree----------" << std::endl;
	
	//printTree(my_set3.begin().base(), NULL, false);
	
	std::cout << "---------COPIED---------" << std::endl;


	std::cout << "---------GET THIS ITERATOR CONSTRUCTOR BABY---------" << std::endl;
	NAMESPACE::set<int>		my_set4(my_set.begin(), my_set.end());
	//printTree(my_set4.begin().base(), NULL, false);

	std::cout << "---------Bound----------" << std::endl;
	std::cout << "---------UPPER----------" << std::endl;
	std::cout << "Upper Bound de 5 : ";
	(my_set.upper_bound(5) == my_set.end() ? std::cout << "Not found" : std::cout << *(my_set.upper_bound(5))) << std::endl;
	std::cout << "Upper Bound de 50 : ";
	(my_set.upper_bound(50) == my_set.end() ? std::cout << "Not found" : std::cout << *(my_set.upper_bound(50))) << std::endl;
	std::cout << "Upper Bound de -5 : ";
	(my_set.upper_bound(-5) == my_set.end() ? std::cout << "Not found" : std::cout << *(my_set.upper_bound(-5))) << std::endl;
	std::cout << "---------LOWER----------" << std::endl;
	std::cout << "Lower Bound de 5 : ";
	(my_set.lower_bound(5) == my_set.end() ? std::cout << "Not found" : std::cout << *(my_set.lower_bound(5))) << std::endl;
	std::cout << "Lower Bound de 50 : ";
	(my_set.lower_bound(50) == my_set.end() ? std::cout << "Not found" : std::cout << *(my_set.lower_bound(50))) << std::endl;
	std::cout << "Lower Bound de -5 : ";
	(my_set.lower_bound(-5) == my_set.end() ? std::cout << "Not found" : std::cout << *(my_set.lower_bound(-5))) << std::endl;
	std::cout << "---------End Bound----------" << std::endl;
	NAMESPACE::pair<NAMESPACE::set<int>::iterator, NAMESPACE::set<int>::iterator>	eqr = my_set.equal_range(5);
	if (eqr.first != my_set.lower_bound(5) || eqr.second != my_set.upper_bound(5))
		std::cout << "Wrong equal range" << std::endl;
	std::cout << "-----------ERASE---------" << std::endl;
	
	while (my_set.size())
	{
		NAMESPACE::set<int>::iterator it2(my_set.begin());
		std::cout << "size = " << my_set.size() << std::endl;
		my_set.erase(it2);
		//printTree(my_set.begin().base(), NULL, false);
	}
	std::cout << "size = " << my_set.size() << std::endl;

	//printTree(my_set.begin().base(), NULL, false);
	std::cout << "-----------ERASED---------" << std::endl;

	test_mli();

}
