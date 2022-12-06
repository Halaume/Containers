/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:41:09 by ghanquer          #+#    #+#             */
/*   Updated: 2022/12/06 17:03:17 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
#define RBTREE_HPP

#define RED true
#define BLACK false
#define LEFT 0
#define RIGHT 1

#include <cassert>
#include <cstddef>
#include <functional>
#include <memory>
#include "pair.hpp"
#include "bidirectional_iterator.hpp"
#include "reverse_bidirectional_iterator.hpp"
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
				typedef ft::bIterator<T, RbTree>				iterator;
				typedef ft::bIterator<const T, RbTree>			const_iterator;
				typedef ft::rbIterator<iterator>				reverse_iterator;
				typedef ft::rbIterator<const_iterator>			const_reverse_iterator;



				struct node
				{
					node(void): color(BLACK), value(), parent(NULL)
					{
						child[LEFT] = NULL;
						child[RIGHT] = NULL;
					}
					node(const node & copy): parent(copy.parent), color(copy.color), value(copy.value)
					{
						child[LEFT] = NULL;
						child[RIGHT] = NULL;
					}
					node(const value_type & val, const Allocator & alloc = Allocator()): parent(NULL), color(RED)
					{
						child[LEFT] = NULL;
						child[RIGHT] = NULL;
						this->_alloc = alloc;
						value = this->_alloc.allocate(1);
						this->_alloc.construct(value, val);
					}
					~node(void)
					{
						//						this->_alloc.destroy(value);
						//						this->_alloc.deallocate(value, 1);
					}
					/*					node &	operator=(const node & src)
										{
					//TODO C dla merde
					//
					//
					if (this == &src)
					return (*this);
					this->parent = src.parent;
					this->child = src.child;
					this->color = src.color;
					this->value = src.value;
					this->dir = src.dir;
					}*/
					//					bool operator==(const node & rhs)
					//					{
					//						return (this->value->first == rhs.value->first);
					//					}
					node*		parent;
					node*		child[2];
					bool		color;
					pointer		value;
					int			dir;
					private:
						Allocator	_alloc;
				};

				typedef node *		nodePTR;


				RbTree(void)
				{
					this->_nodealloc = std::allocator<node>();
					this->_start = NULL;
					this->_alloc = Allocator();
					this->_comp = Compare();
					this->_size = 0;
				}
				explicit RbTree(const Compare & comp, const Allocator & alloc = Allocator())
				{
					this->_nodealloc = std::allocator<node>();
					this->_start = NULL;
					this->_alloc = alloc;
					this->_comp = comp;
					this->_size = 0;
				}
				RbTree(const RbTree & copy): _alloc(copy._alloc), _start(copy._start), _comp(copy._comp), _nodealloc(copy._nodealloc), _size(copy._size)
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
					//					this->clear();
				}
				RbTree& operator=(const RbTree & other)
				{
					if (this == &other)
						return (*this);
//					if (this->_start)
//						this->clear();
					this->_start = other._start;
					this->_size = other._size;
				}
				allocator_type get_allocator() const
				{
					return (this->_alloc);
				}
				T& at( const Key& key );
				T& operator[]( const Key& key );
				iterator begin()
				{
					node * tmp = this->_start;
					while (tmp && tmp->child[LEFT])
						tmp = tmp->child[LEFT];
					return (iterator(tmp));
				}
				const_iterator begin() const
				{
					node * tmp = this->_start;
					while (tmp && tmp->child[LEFT])
						tmp = tmp->child[LEFT];
					return (const_iterator(tmp));
				}
				iterator end()
				{
					node * tmp = this->_start;
					while (tmp && tmp->child[RIGHT])
						tmp = tmp->child[RIGHT];
					return (iterator(tmp));
				}
				const_iterator end() const
				{
					node * tmp = this->_start;
					while (tmp && tmp->child[RIGHT])
						tmp = tmp->child[RIGHT];
					return (const_iterator(tmp));
				}
				reverse_iterator rbegin()
				{
					return (reverse_iterator(this->end()));
				}
				const_reverse_iterator rbegin() const
				{
					return (const_reverse_iterator(this->end()));
				}
				reverse_iterator rend()
				{
					return (reverse_iterator(this->begin()));
				}
				const_reverse_iterator rend() const
				{
					return (const_reverse_iterator(this->begin()));
				}
				bool empty() const
				{
					return (!this->_start);
				}
				void clear(void)
				{
					node*	tmp = this->_start;
					node*	tmp2;

					while (this->_start)
					{
						if (tmp->child[LEFT])
							tmp = tmp->child[LEFT];
						else if (!tmp->child[RIGHT])
						{
							tmp2 = tmp;
							if (tmp->parent)
							{
								tmp = tmp->parent;
								this->_nodealloc.destroy(tmp2);
								this->_nodealloc.deallocate(tmp2, 1);
								tmp2 = NULL;
							}
							else
							{
								this->_nodealloc.destroy(tmp2);
								this->_nodealloc.deallocate(tmp2, 1);
								this->_start = NULL;
							}
						}
						else
							tmp = tmp->child[RIGHT];
					}
				}
				value_type	insert(const value_type & value)
				{
					node* tmp = this->_start;
					node* tmpp = NULL;
					if (!tmp)
					{
						this->_start = this->_nodealloc.allocate(1);
						this->_nodealloc.construct(this->_start, value);
						this->_start->color = BLACK;
						return (*this->_start->value);
					}
					while (tmp)
					{
						tmpp = tmp;
						if (value.first > tmp->value->first)
							tmp = tmp->child[RIGHT];
						else
							tmp = tmp->child[LEFT];
					}
					tmp = this->_nodealloc.allocate(1);
					this->_nodealloc.construct(tmp, value);
					tmp->parent = tmpp;
					if (tmp->value->first > tmpp->value->first)
					{
						tmp->parent->child[RIGHT] = tmp;
						tmp->dir = RIGHT;
					}
					else
					{
						tmp->parent->child[LEFT] = tmp;
						tmp->dir = LEFT;
					}
					//					std::cout << tmp->value->first << std::endl;
					this->_balance(tmp, tmp->parent);
					this->_size++;
					return (*tmp->value);
				}
				/*				iterator insert( iterator pos, const value_type& value )
								{
								return (iterator(this->insert(value)));
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
				iterator erase(iterator pos)
				{
					return (pos);
				}
				iterator erase(iterator first, iterator last)
				{
				}
				size_type erase(const Key & key)
				{
					return (this->_size);
				}
				node*					_start;
			private:
				Allocator				_alloc;
				Compare					_comp;
				std::allocator<node>	_nodealloc;
				size_type				_size;
				/*				void	_swapDatAss(node * n1, node * n2)
								{
								node * tmp(n1);
								n1->color = n2->color;
								n1->parent = n2->parent;
								n1->dir = n2->dir;
								n1->child[0] = n2->child[0];
								n1->child[1] = n2->child[1];
								n1->value = n2->value;
								n2->color = tmp->color;
								n2->parent = tmp->parent;
								n2->dir = tmp->dir;
								n2->child[0] = tmp->child[0];
								n2->child[1] = tmp->child[1];
								n2->value = tmp->value;
								}
								*/				node * _rotateDirRoot(node * P, int dir)
				{
					node * G = P->parent;
					node * S = P->child[1 - dir];
					node * C;
					assert(S != NULL);
					C = S->child[dir];

					P->child[1 - dir] = C;
					if (C != NULL)
						C->parent = P;
					S->child[dir] = P;
					P->parent = S;
					S->parent = G;
					if (G != NULL)
						G->child[ P == G->child[RIGHT] ? RIGHT : LEFT ] = S;
					else
						this->_start = S;
					return (S);
				}
				void	_do_case_56(node * my_node, node * parent, node * gparent, int dir)
				{
					if (my_node == parent->child[1 - dir])
					{
						this->_rotateDirRoot(parent, dir);
						my_node = parent;
						parent = gparent->child[dir];
					}
					this->_rotateDirRoot(gparent, 1 - dir);
					parent->color = BLACK;
					gparent->color = RED;
				}
				void	_balance(node * my_node, node * parent)
				{
					int dir = my_node->parent->dir;
					node * uncle = NULL;
					node * gparent = NULL;
					do 
					{
						if (parent)
							gparent = parent->parent;
						if (parent->color == BLACK)
						{
							return ;
						}
						if (gparent == NULL)
						{
							parent->color = BLACK;
							std::cout << "COLOR" << parent->color << std::endl;
							return ;
						}
						dir = parent == gparent->child[RIGHT] ? RIGHT : LEFT;
//						dir = my_node->parent->dir;
						uncle = gparent->child[1 - dir];
/*						if (parent)
							std::cout << "parent = " << parent->value->first << " color = " << parent->color << std::endl;
						if (gparent)
							std::cout << "gparent = " << gparent->value->first << " color = " << gparent->color << std::endl;
						if (gparent && gparent->parent)
							std::cout << "ggparent = " << gparent->parent->value->first << " color = " << gparent->parent->color << std::endl;
						if (uncle)
							std::cout << "uncle value = " << uncle->value->first << " color = " << uncle->color << std::endl;
						std::cout << "-----------------------------" << std::endl;
*/						if (uncle == NULL || uncle->color == BLACK)
						{
							_do_case_56(my_node, parent, gparent, dir);
							return ;
						}
						parent->color = BLACK;
						uncle->color = BLACK;
						if (gparent != _start)
							gparent->color = RED;
						my_node = gparent;
					}
					while ((parent = my_node->parent) != NULL);
//					if (parent->parent == NULL && parent->color == RED)
//						parent->color = BLACK;
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
