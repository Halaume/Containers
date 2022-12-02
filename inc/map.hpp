/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:59:23 by ghanquer          #+#    #+#             */
/*   Updated: 2022/12/02 17:23:04 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <cstddef>
#include <functional>
#include <memory>
#include "pair.hpp"
#include "iterator.hpp"
#include "reverse_iterator.hpp"
#include "rbTree.hpp"

namespace ft
{
	template<class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
		class map
		{
			public:
				typedef Key										key_type;
				typedef T										mapped_type;
				typedef ft::pair<const Key, T>					value_type;
				typedef Allocator								allocator_type;
				typedef std::size_t								size_type;
				typedef Compare									key_compare;
				typedef std::ptrdiff_t							difference_type;
				typedef value_type &							reference;
				typedef const value_type &						const_reference;
				typedef typename Allocator::pointer				pointer;
				typedef typename Allocator::const_pointer		const_pointer;
				//TODO Make bidirectionnal iterator for this bad boy
				typedef ft::Iterator<T>							iterator;
				typedef ft::Iterator<const T>					const_iterator;
				typedef ft::Reverse_iterator<iterator>			reverse_iterator;
				typedef ft::Reverse_iterator<const_iterator>	const_reverse_iterator;
				class value_compare : public std::binary_function<key_type, value_type, key_compare>
				{
					public:
						bool	operator()(const value_type & lhs, const value_type & rhs) const 
						{
							return (this->comp(lhs.first, rhs.first));
						}
					protected:
						value_compare(Compare c)
						{
							this->comp = c;
						}
						Compare	comp;
				};
				map(void)
				{
					this->_tree = RbTree<Key, T>();
				}
				explicit map(const Compare & comp, const Allocator & alloc = Allocator())
				{
					this->_tree = RbTree<Key, T>(comp, alloc);
				}
/*				template<class InputIt>
					map(InputIt first, InputIt last, const Compare & comp = Compare(), const Allocator & alloc = Allocator())
					{
					}
*/				map(const map & copy)
				{
					this->_tree = copy._tree;
				}
				~map(void)
				{
				}
				bool empty() const
				{
					return (this->_tree.empty());
				}
				value_type	insert(const value_type & value)
				{
					return (this->_tree.insert(value));
				}
				iterator	insert(iterator pos, const value_type & value)
				{
					return (this->_tree.insert(pos, value));
				}
				template<class InputIt>
					void insert(InputIt first, InputIt last)
					{
						this->_tree.insert(first, last);
					}
			private:
				RbTree<Key, T>	_tree;
		};
}

#endif
