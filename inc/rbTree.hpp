/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:41:09 by ghanquer          #+#    #+#             */
/*   Updated: 2022/12/02 18:45:49 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
#define RBTREE_HPP

#define RED true
#define BLACK false

#include <cstddef>
#include <functional>
#include <memory>
#include "pair.hpp"
#include "iterator.hpp"
#include "reverse_iterator.hpp"
#include "lexicographical_compare.hpp"

namespace ft
{

	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
		class RbTree
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



				struct node
				{
					node(void): color(BLACK), value(), parent(NULL), rchild(NULL), lchild(NULL)
					{
					}
					node(const node & copy): parent(copy.parent), lchild(copy.lchild), rchild(copy.rchild), color(copy.color), value(copy.value)
					{
					}
					node(const value_type & val, const Allocator & alloc = Allocator()): parent(NULL), rchild(NULL), lchild(NULL), color(RED)
					{
						this->_alloc = alloc;
						value = this->_alloc.allocate(1);
						this->_alloc.construct(value, val);
					}
					~node(void)
					{
						this->_alloc.destroy(value);
						this->_alloc.deallocate(value, 1);
					}
					node &	operator=(const node & src);
					node*		parent;
					node*		lchild;
					node*		rchild;
					bool		color;
					pointer		value;
					private:
						Allocator	_alloc;
				};
				RbTree(void)
				{
					this->_nodealloc = std::allocator<node>();
					this->_start = NULL;
					this->_alloc = Allocator();
					this->_comp = Compare();
				}
				explicit RbTree(const Compare & comp, const Allocator & alloc = Allocator())
				{
					this->_nodealloc = std::allocator<node>();
					this->_start = NULL;
					this->_alloc = alloc;
					this->_comp = comp;
				}
				RbTree(const RbTree & copy): _alloc(copy._alloc), _start(copy._start), _comp(copy._comp)
				{
				}
				RbTree(Key & key, T & value, const Compare & comp = Compare(), const Allocator & alloc = Allocator())
				{
					this->_nodealloc = std::allocator<node>();
					this->_comp = comp;
					this->_alloc = alloc;
					this->_start = node(make_pair(key, value), NULL, comp, alloc);
				}
				~RbTree(void)
				{
					this->clear();
				}
				void clear(void)
				{
					node*	tmp = this->_start;
					node*	tmp2;

					while (this->_start)
					{
						if (tmp->lchild)
							tmp = tmp->lchild;
						else if (!tmp->rchild)
						{
							tmp2 = tmp;
							if (tmp->parent)
								tmp = tmp->parent;
							this->_nodealloc.destroy(tmp2);
							this->_nodealloc.deallocate(tmp2, 1);
						}
						else
							tmp = tmp->rchild;
					}
				}
				bool empty() const
				{
					return (!this->_start);
				}
				value_type	insert(const value_type & value)
				{
					node* tmp = this->_start;
					node* tmpp;
					while (tmp)
					{
						tmpp = tmp;
						if (value.first > tmp->value->first)
							tmp = tmp->lchild;
						else
							tmp = tmp->rchild;
					}
					tmp = this->_nodealloc.allocate(1);
					pointer const tmp2 = &value;
					this->_nodealloc.construct(tmp, tmp2);
					tmp->parent = tmpp;
					return (*tmp->value);
				}
/*				iterator insert( iterator pos, const value_type& value )
				{
					this->insert(value);
					return (iterator(pos));
				}
				template< class InputIt >
					void insert( InputIt first, InputIt last )
				{
					while (first != last)
					{
						this->insert(*first);
						first++;
					}
				}*/
				node*					_start;
			private:
				Allocator				_alloc;
				Compare					_comp;
				std::allocator<node>	_nodealloc;
				void	_balance(void)
				{
				}
		};
	template< class Key, class T, class Compare, class Alloc >
		bool operator==( const RbTree<Key,T,Compare,Alloc>& lhs, const RbTree<Key,T,Compare,Alloc>& rhs );
	template< class Key, class T, class Compare, class Alloc >
		bool operator!=( const RbTree<Key,T,Compare,Alloc>& lhs, const RbTree<Key,T,Compare,Alloc>& rhs )
		{
			return (!(lhs == rhs));
		}
	template< class Key, class T, class Compare, class Alloc >
		bool operator<( const RbTree<Key,T,Compare,Alloc>& lhs, const RbTree<Key,T,Compare,Alloc>& rhs )
		{
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) && lhs != rhs);
		}
	template< class Key, class T, class Compare, class Alloc >
		bool operator<=( const RbTree<Key,T,Compare,Alloc>& lhs, const RbTree<Key,T,Compare,Alloc>& rhs )
		{
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) || lhs == rhs);
		}
	template< class Key, class T, class Compare, class Alloc >
		bool operator>( const RbTree<Key,T,Compare,Alloc>& lhs, const RbTree<Key,T,Compare,Alloc>& rhs )
		{
			return (!(ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())) && lhs != rhs);
		}
	template< class Key, class T, class Compare, class Alloc >
		bool operator>=( const RbTree<Key,T,Compare,Alloc>& lhs, const RbTree<Key,T,Compare,Alloc>& rhs )
		{
			return (!(ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())) || lhs == rhs);
		}

	template< class Key, class T, class Compare, class Alloc >
		void swap( RbTree<Key,T,Compare,Alloc>& lhs, RbTree<Key,T,Compare,Alloc>& rhs )
		{
			lhs.swap(rhs);
		}
}

#endif
