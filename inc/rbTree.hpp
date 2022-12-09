/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:41:09 by ghanquer          #+#    #+#             */
/*   Updated: 2022/12/09 19:33:05 by ghanquer         ###   ########.fr       */
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
#include "reverse_iterator.hpp"
#include "lexicographical_compare.hpp"
#include "is_same.hpp"

namespace ft
{

	template <class Key, class T, class value_type = ft::pair<const Key, T>, class Compare = std::less<Key>, class Allocator = std::allocator<value_type> >
		class RbTree
		{
			public:
				typedef Key										key_type;
				typedef T										mapped_type;
				typedef Allocator								allocator_type;
				typedef std::size_t								size_type;
				typedef Compare									key_compare;
				typedef std::ptrdiff_t							difference_type;
				typedef value_type &							reference;
				typedef const value_type &						const_reference;
				typedef typename Allocator::pointer				pointer;
				typedef typename Allocator::const_pointer		const_pointer;

				struct node
				{
					node(void): color(BLACK), value(), parent(NULL)
					{
						child[LEFT] = NULL;
						child[RIGHT] = NULL;
					}
					node(const node & copy): parent(copy.parent), color(copy.color)
					{
						child[LEFT] = NULL;
						child[RIGHT] = NULL;
						if (copy.value)
						{
							value = this->_alloc.allocate(1);
							this->_alloc.construct(value, *copy.value);
						}
						else
							this->value = NULL;
					}
					node(pointer val, const Allocator & alloc = Allocator()): parent(NULL), color(RED)
					{
						child[LEFT] = NULL;
						child[RIGHT] = NULL;
						this->_alloc = alloc;
						this->value = val;
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
						if (value)
						{
							this->_alloc.destroy(value);
							this->_alloc.deallocate(value, 1);
						}
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
					private:
						Allocator	_alloc;
				};

				typedef node *							nodePTR;
				typedef ft::bIterator<nodePTR, value_type>			iterator;
				typedef ft::bIterator<const nodePTR, value_type>	const_iterator;
				typedef ft::Reverse_iterator<iterator>				reverse_iterator;
				typedef ft::Reverse_iterator<const_iterator>		const_reverse_iterator;

				RbTree(void)
				{
					this->_nodealloc = std::allocator<node>();
					this->_start = NULL;
					this->_alloc = Allocator();
					this->_comp = Compare();
					this->_size = 0;
					this->_Nil = this->_nodealloc.allocate(1);
					this->_nodealloc.construct(this->_Nil, NULL);
				}
				explicit RbTree(const Compare & comp, const Allocator & alloc = Allocator())
				{
					this->_nodealloc = std::allocator<node>();
					this->_start = NULL;
					this->_alloc = alloc;
					this->_comp = comp;
					this->_size = 0;
					this->_Nil = this->_nodealloc.allocate(1);
					this->_nodealloc.construct(this->_Nil, NULL);
				}
				RbTree(const RbTree & copy): _alloc(copy._alloc), _start(copy._start), _comp(copy._comp), _nodealloc(copy._nodealloc), _size(copy._size), _Nil(copy._Nil)
			{
			}
				RbTree(value_type & value, const Compare & comp = Compare(), const Allocator & alloc = Allocator())
				{
					this->_nodealloc = std::allocator<node>();
					this->_comp = comp;
					this->_alloc = alloc;
					this->_start = this->_nodealloc.allocate(1);
					this->_nodealloc.construct(this->_start, value);
					this->_Nil = this->_nodealloc.allocate(1);
					this->_nodealloc.construct(this->_Nil, NULL);
					this->_Nil = this->_start;
				}
				~RbTree(void)
				{
					this->clear();
					node * to_del;
					to_del = this->_Nil;
					this->_Nil = NULL;
					this->_nodealloc.destroy(to_del);
					this->_nodealloc.deallocate(to_del, 1);
				}
				RbTree& operator=(const RbTree & other)
				{
					if (this == &other)
						return (*this);
					if (this->_start)
						this->clear();
					this->_start = other._start;
					this->_size = other._size;
				}
				allocator_type get_allocator() const
				{
					return (this->_alloc);
				}
				T& at( const Key& key );
				T& operator[]( const Key& key );
				iterator begin(void)
				{
					if (!this->_start)
						return (iterator(this->_Nil));
					node * tmp = this->_start;
					while (tmp && tmp->child[LEFT])
						tmp = tmp->child[LEFT];
					return (iterator(tmp));
				}
				const_iterator begin(void) const
				{
					if (!this->_start)
						return (const_iterator(this->_Nil));
					node * tmp = this->_start;
					while (tmp && tmp->child[LEFT])
						tmp = tmp->child[LEFT];
					return (const_iterator(tmp));
				}
				iterator end(void)
				{
					return (iterator(this->_Nil));
				}
				const_iterator end(void) const
				{
					return (const_iterator(this->_Nil));
				}
				reverse_iterator rbegin(void)
				{
					return (reverse_iterator(this->end()));
				}
				const_reverse_iterator rbegin(void) const
				{
					return (const_reverse_iterator(this->end()));
				}
				reverse_iterator rend(void)
				{
					return (reverse_iterator(this->begin()));
				}
				const_reverse_iterator rend(void) const
				{
					return (const_reverse_iterator(this->begin()));
				}
				bool empty(void) const
				{
					return (!this->_start);
				}
				void clear(void)
				{
					node*	tmp = this->_start;
					node*	to_del;

					while (tmp->value)
					{
						if (tmp->child[LEFT])
							tmp = tmp->child[LEFT];
						else if (tmp->child[RIGHT])
							tmp = tmp->child[RIGHT];
						else
						{

							if (tmp->parent->value)
							{

								to_del = tmp;
								tmp = tmp->parent;
								if (to_del == tmp->child[LEFT])
									tmp->child[LEFT] = NULL;
								else
									tmp->child[RIGHT] = NULL;
								this->_nodealloc.destroy(to_del);
								this->_nodealloc.deallocate(to_del, 1);
							}
							else
							{
								to_del = tmp;
								tmp = tmp->parent;
								this->_nodealloc.destroy(to_del);
								this->_nodealloc.deallocate(to_del, 1);
							}
						}
					}
					to_del = tmp;
					tmp = NULL;
					this->_nodealloc.destroy(to_del);
					this->_nodealloc.deallocate(to_del, 1);
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
						this->_start->parent = this->_Nil;
						this->_Nil = this->_nodealloc.allocate(1);
						this->_nodealloc.construct(this->_Nil, NULL);
						this->_Nil->parent = this->_start;
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
					}
					else
					{
						tmp->parent->child[LEFT] = tmp;
					}
					this->_balance(tmp, tmp->parent);
					this->_size++;
					return (*tmp->value);
				}
				iterator insert( iterator pos, const value_type& value )
				{
					(void)pos;
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
					}
			private:
				node * _rotateDirRoot(node * P, int dir)
				{
					node * G = P->parent;
					node * S = P->child[1 - dir];
					node * C;
					assert(S != NULL);
					C = S->child[dir];

					P->child[1 - dir] = C;
					if (C != NULL && C->value != NULL)
						C->parent = P;
					S->child[dir] = P;
					P->parent = S;
					S->parent = G;
					if (G != NULL && G->value != NULL)
						G->child[ P == G->child[RIGHT] ? RIGHT : LEFT ] = S;
					else
					{
						this->_start = S;
						this->_start->parent->parent = S;
					}
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
					int dir = 0;
					node * uncle = NULL;
					node * gparent = NULL;
					do 
					{
						if (parent->value)
							gparent = parent->parent;
						if (parent->color == BLACK)
						{
							return ;
						}
						if (gparent->value == NULL)
						{
							parent->color = BLACK;
							return ;
						}
						dir = parent == gparent->child[RIGHT] ? RIGHT : LEFT;
						uncle = gparent->child[1 - dir];
						if (uncle == NULL || uncle->color == BLACK)
						{
							_do_case_56(my_node, parent, gparent, dir);
							return ;
						}
						parent->color = BLACK;
						uncle->color = BLACK;
						if (gparent != this->_start)
							gparent->color = RED;
						my_node = gparent;
						parent = my_node->parent;
					}
					while (parent->value != NULL);
				}
			public:
				void erase(iterator pos)
				{
					node * to_del = *pos;
					if (to_del == this->_start && !this->_start->child[RIGHT] && !this->_start->child[LEFT])
					{
						this->_Nil->parent = this->_Nil;
						this->_delnode(this->_start);
						return ;
					}
					else if (to_del->child[LEFT] && to_del->child[RIGHT])
					{
						node * tmp = to_del->child[RIGHT];
						while (tmp->child[LEFT])
							tmp = tmp->child[LEFT];
						this->_swaaaaaap(to_del, tmp);
					}
					if (to_del->child[LEFT] || to_del->child[RIGHT])
					{
						if (to_del->child[LEFT])
						{
							to_del->child[LEFT];
							this->_swaaaaaap(to_del, to_del->child[LEFT]);
						}
						else
						{
							to_del->child[RIGHT];
							this->_swaaaaaap(to_del, to_del->child[RIGHT]);
						}
					}
					else if (to_del->color == BLACK)
					{
						//TODO Delete cringe code wikipedia
						int	dir = to_del->parent->child[RIGHT] == to_del ? RIGHT : LEFT;
						int did = 0;
						node * parent = to_del->parent;
						node * sib;
						node * D;
						node * C;
						parent->child[dir] = NULL;
						do
						{
							if (did == 1)
								dir = to_del->parent->child[RIGHT] == to_del ? RIGHT : LEFT;
							did = 1;
							sib = parent->child[1-dir];
							D = sib->child[1-dir];
							C = sib->child[dir];
							if (sib->color == RED)
							{
								this->_case_3(to_del, parent, sib, D, C, dir);
								this->_delnode(to_del);
								return ;
							}
							if (D && D->color == RED)
							{
								this->_case_6(to_del, parent, sib, D, C, dir);
								this->_delnode(to_del);
								return ;
							}
							if (C && C->color == RED)
							{
								this->_case_5(to_del, parent, sib, D, C, dir);
								this->_delnode(to_del);
								return ;
							}
							if (parent->color == RED)
							{
								this->case_4(to_del, parent, sib, D, C);
								this->_delnode(to_del);
								return ;
							}
							sib->color = RED;
							to_del = parent;
						}
						while ((parent = to_del->parent) != NULL);
						this->_delnode(to_del);
						return ;
					}
					else
						this->_delnode(to_del);
				}
				void erase(iterator first, iterator last)
				{
					while (first != last)
					{
						this->erase(*first);
						first++;
					}
				}
				size_type erase(const Key & key)
				{
					if (this->find(key) != this->end())
						return (erase(iterator(key)), 1);
					return (0);
				}
			private:
				void	_swaaaaaap(node * node1, node * node2)
				{
					node * tmp;

					tmp->child = node1->child;
					tmp->parent = node1->parent;
					tmp->value = node1->value;
					tmp->color = node1->color;


					node1->child = node2->child;
					node1->parent = node2->parent;
					node1->value = node2->value;
					node1->color = node2->color;


					node2->child = node1->child;
					node2->parent = node1->parent;
					node2->value = node1->value;
					node2->color = node1->color;

				}
				void	_delnode(node * to_del)
				{
					this->_nodealloc.destroy(to_del);
					this->_nodealloc.deallocate(to_del, 1);
				}
				void	_case_3(node * to_del, node * parent, node * sib, node * D, node * C, int dir)
				{
					this->_rotateDirRoot(parent, dir);
					parent->color = RED;
					sib->color = BLACK;
					sib = C;
					D = sib->child[1 - dir];
					if (D && D->color == RED)
					{
						this->_case_6(to_del, parent, sib, D, C, dir);
						return ;
					}
					C = sib->child[dir];
					if (C && C->color == RED)
					{
						this->_case_5(to_del, parent, sib, D, C, dir);
						return ;
					}
					sib->color = RED;
					parent->color = BLACK;
				}
				void	_case_5(node * to_del, node * parent, node * sib, node * D, node * C, int dir)
				{
					this->_rotateDirRoot*(sib, 1 - dir);
					sib->color = RED;
					C->color = BLACK;
					D = sib;
					sib = C;
					this->_case_6(to_del, parent, sib, D, C, dir);
				}
				void	_case_6(node * to_del, node * parent, node * sib, node * D, node * C, int dir)
				{
					this->_rotateDirRoot(parent, dir);
					sib->color = parent->color;
					parent->color = BLACK;
					D->color = BLACK;
				}
/*				void	_shift_node(node * U, node * C)
				{
					if (U->parent == this->_Nil)
						this->_start = C;
					else if (U == U->parent->child[LEFT])
						U->parent->child[LEFT] = C;
					else
						U->parent->child[RIGHT] = C;
					if (C != NULL)
						C->parent = U->parent;
				}
				void	_basic_delete(iterator pos)
				{
					if (pos->child[LEFT] == NULL)
						this->_shift_node(*pos, pos->child[RIGHT]);
					else if (pos->child[RIGHT] == NULL)
						this->_shift_node(*pos, pos->child[LEFT]);
					else
					{
						node * U;
						if (pos->child[RIGHT])
						{
							U = pos->child[RIGHT];
							while (U->child[LEFT])
								U = U->child[LEFT];
						}
						else
						{
							U = pos->child[LEFT];
							while (U->child[RIGHT])
								U = U->child[RIGHT];
						}
						if (U->parent != *pos)
						{
							this->_shift_node(U, U->child[RIGHT]);
							U->child[RIGHT] = pos->child[RIGHT];
							U->child[RIGHT]->parent = U;
						}
						this->_shift_node(*pos, U);
						U->child[LEFT] = pos->child[LEFT];
						U->chilf[LEFT]->parent = U;
					}
				}*/
			public:
				node*					_start;
			private:
				Allocator				_alloc;
				Compare					_comp;
				std::allocator<node>	_nodealloc;
				size_type				_size;
				node *					_Nil;
				
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
