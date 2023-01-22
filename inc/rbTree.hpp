/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:41:09 by ghanquer          #+#    #+#             */
/*   Updated: 2023/01/22 17:03:20 by ghanquer         ###   ########.fr       */
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
#include <stdexcept>
#include "pair.hpp"
#include "bidirectional_iterator.hpp"
#include "reverse_iterator.hpp"
#include "lexicographical_compare.hpp"
#include "is_same.hpp"
#include "equal.hpp"

namespace ft
{
	template<typename ptr>
		void swap(ptr & lhs, ptr & rhs)
		{
			ptr tmp;
			tmp = rhs;
			rhs = lhs;
			lhs = tmp;
		}

	template <class value_type, class Compare, class Allocator = std::allocator<value_type> >
		class RbTree
		{
			public:
				typedef value_type								key_type;
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
						this->value = this->_alloc.allocate(1);
						this->_alloc.construct(this->value, val);
					}
					~node(void)
					{
						if (this->value)
						{
							this->_alloc.destroy(this->value);
							this->_alloc.deallocate(this->value, 1);
						}
					}
					node &	operator=(const node & src)
					{
						if (this == &src)
							return (*this);
						this->parent = src.parent;
						this->child[LEFT] = src.child[LEFT];
						this->child[RIGHT] = src.child[RIGHT];
						this->color = src.color;
						if (this->value)
						{
							this->_alloc.destroy(this->value);
							this->_alloc.deallocate(this->value);
						}
						if (src.value)
						{
							this->value = this->_alloc.allocate(1);
							this->_alloc.construct(this->value, src.value);
						}
						else
							this->value = NULL;
					}
					node*		parent;
					node*		child[2];
					bool		color;
					pointer		value;
					void swap(node * & other)
					{
						if (this->parent == other->parent)
							ft::swap(this->parent->child[LEFT], other->parent->child[RIGHT]);
						else
						{
							if (this->parent->value && this->parent != other)
							{
								if (this->parent->child[LEFT] == this)
									this->parent->child[LEFT] = other;
								else
									this->parent->child[RIGHT] = other;
							}
							if (other->parent->value && other->parent != this)
							{
								if (other->parent->child[LEFT] == other)
									other->parent->child[LEFT] = this;
								else
									other->parent->child[RIGHT] = this;
							}
						}
						if (this->child[LEFT] && this->child[LEFT] != other)
							this->child[LEFT]->parent = other;
						if (this->child[RIGHT] && this->child[RIGHT] != other)
							this->child[RIGHT]->parent = other;
						if (other->child[LEFT] && other->child[LEFT] != this)
							other->child[LEFT]->parent = this;
						if (other->child[RIGHT] && other->child[RIGHT] != this)
							other->child[RIGHT]->parent = this;
						if (this->parent != other && other->parent != this)
						{
							ft::swap(this->parent, other->parent);
							ft::swap(this->child[LEFT], other->child[LEFT]);
							ft::swap(this->child[RIGHT], other->child[RIGHT]);
						}
						else if (this->parent == other)
						{
							this->parent = other->parent;
							other->parent = this;
							if (other->child[LEFT] == this)
							{
								other->child[LEFT] = this->child[LEFT];
								this->child[LEFT] = other;
								ft::swap(other->child[RIGHT], this->child[RIGHT]);
							}
							else
							{
								other->child[RIGHT] = this->child[RIGHT];
								this->child[RIGHT] = other;
								ft::swap(other->child[LEFT], this->child[LEFT]);
							}
						}
						else if (other->parent == this)
						{
							other->parent = this->parent;
							this->parent = other;
							if (this->child[LEFT] == other) 
							{
								this->child[LEFT] = other->child[LEFT];
								other->child[LEFT] = this;
								ft::swap(other->child[RIGHT], this->child[RIGHT]);
							}
							else
							{
								this->child[RIGHT] = other->child[RIGHT];
								other->child[RIGHT] = this;
								ft::swap(other->child[LEFT], this->child[LEFT]);
							}
						}
						if (this->color != other->color)
						{
							this->color = !this->color;
							other->color = !other->color;
						}
					}

					private:
					Allocator	_alloc;
				};

				typedef node *							nodePTR;
				typedef ft::bIterator<nodePTR, value_type>			iterator;
				typedef ft::bIterator<nodePTR, const value_type>	const_iterator;
				typedef ft::Reverse_iterator<iterator>				reverse_iterator;
				typedef ft::Reverse_iterator<const_iterator>		const_reverse_iterator;

				explicit RbTree(const Compare & comp, const Allocator & alloc = Allocator()): _comp(comp)
			{
				this->_nodealloc = std::allocator<node>();
				this->_alloc = alloc;
				this->_size = 0;
				node	val(NULL, this->_alloc);
				this->_Nil = this->_nodealloc.allocate(1);
				this->_nodealloc.construct(this->_Nil, val);
				this->_Nil->parent = this->_Nil;
				this->_start = this->_Nil;
			}
				RbTree(const RbTree & copy): _alloc(copy._alloc), _comp(copy._comp), _nodealloc(copy._nodealloc), _size(copy._size)
			{
				this->_Nil = this->_nodealloc.allocate(1);
				this->_nodealloc.construct(this->_Nil, *(copy._Nil));
				this->_start = this->_Nil;
				if (copy.begin() != copy.end())
				{
					this->_start = this->_copy(this->_start, copy._start);
					this->_start->parent = this->_Nil;
					this->_Nil->parent = this->_start;
				}
				else
				{
					this->_start = this->_Nil;
					this->_Nil->parent = this->_Nil;
				}
			}
			private:
				node *	_copy(node * root, node * my_node)
				{
					node * tmp = this->_nodealloc.allocate(1);
					this->_nodealloc.construct(tmp, *(my_node));

					tmp->parent = root;
					if (my_node->child[LEFT])
						tmp->child[LEFT] = this->_copy(tmp, my_node->child[LEFT]);
					if (my_node->child[RIGHT])
						tmp->child[RIGHT] = this->_copy(tmp, my_node->child[RIGHT]);
					return (tmp);
				}
			public:
				RbTree(value_type & value, const Compare & comp = Compare(), const Allocator & alloc = Allocator()): _comp(comp)
			{
				this->_nodealloc = std::allocator<node>();
				this->_alloc = alloc;
				this->_start = this->_nodealloc.allocate(1);
				this->_nodealloc.construct(this->_start, node(value, this->_alloc));
				this->_Nil = this->_nodealloc.allocate(1);
				this->_size = 1;
				node	val(NULL, this->_alloc);
				this->_Nil = this->_nodealloc.allocate(1);
				this->_nodealloc.construct(this->_Nil, val);
				this->_Nil->parent = this->_start;
			}
				template<class InputIt>
					RbTree(InputIt first, InputIt last, const Compare & comp = Compare(), const Allocator & alloc = Allocator()): _comp(comp)
				{
					this->_nodealloc = std::allocator<node>();
					this->_alloc = alloc;
					this->_size = 0;

					node	val(NULL, this->_alloc);
					this->_Nil = this->_nodealloc.allocate(1);
					this->_nodealloc.construct(this->_Nil, val);
					this->_start = this->_Nil;
					this->_Nil->parent = this->_Nil;

					this->insert(first, last);
				}
				~RbTree(void)
				{
					this->clear();
					if (this->_Nil)
					{
						this->_nodealloc.destroy(this->_Nil);
						this->_nodealloc.deallocate(this->_Nil, 1);
					}
				}
				RbTree& operator=(const RbTree & other)
				{
					if (this == &other)
						return (*this);
					if (this->_start)
						this->clear();
					if (other._start != other._Nil)
					{
						this->_start = this->_copy(this->_Nil, other._start);
						this->_Nil->parent = this->_start;
					}
					else
					{
						this->_start = this->_Nil;
						this->_Nil->parent = this->_Nil;
					}
					this->_size = other._size;
					return (*this);
				}
				value_type & at( const key_type& key )
				{
					iterator tmp = this->find(key);

					if (tmp == this->end())
						throw std::out_of_range("Key not exist");
					return (*tmp);
				}
				const value_type & at( const key_type& key ) const
				{
					const_iterator tmp = this->find(key);

					if (tmp == this->end())
						throw std::out_of_range("Key not exist");
					return (*tmp);
				}
				iterator begin(void)
				{
					if (this->_start == this->_Nil)
						return (iterator(this->_Nil));
					node * tmp = this->_start;
					while (tmp && tmp->child[LEFT])
						tmp = tmp->child[LEFT];
					return (iterator(tmp));
				}
				const_iterator begin(void) const
				{
					if (this->_start == this->_Nil)
						return (const_iterator(this->_Nil));
					node * tmp = this->_start;
					while (tmp && tmp->child[LEFT])
						tmp = tmp->child[LEFT];
					return (const_iterator(tmp));
				}
				const_iterator constbegin(void) const
				{
					if (this->_start == this->_Nil)
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
				const_iterator constend(void) const
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
				const_reverse_iterator rconstbegin(void) const
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
				const_reverse_iterator rconstend(void) const
				{
					return (const_reverse_iterator(this->begin()));
				}
				bool empty(void) const
				{
					return (this->_start == this->_Nil);
				}
				size_type size(void)
				{
					return (this->_size);
				}
				size_type max_size(void) const
				{
					return (this->_nodealloc.max_size());
				}
				void clear(void)
				{
					node*	tmp = this->_start;
					node*	to_del;

					while (tmp && tmp->value)
					{
						if (tmp->child[LEFT])
							tmp = tmp->child[LEFT];
						else if (tmp->child[RIGHT])
							tmp = tmp->child[RIGHT];
						else
						{
							if (tmp != this->_start)
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
								tmp = this->_Nil;
								this->_nodealloc.destroy(to_del);
								this->_nodealloc.deallocate(to_del, 1);
							}
						}
					}
					this->_size = 0;
					this->_start = this->_Nil;
					this->_Nil->parent = this->_Nil;
				}
				ft::pair<iterator, bool>	insert(const value_type & value)
				{
					node* tmp = this->_start;
					node* tmpp = this->_Nil;
					if (this->find(value) != this->end())
						return (ft::make_pair(iterator(tmp), false));

					if (!tmp || !tmp->value)
					{
						this->_start = this->_nodealloc.allocate(1);
						this->_nodealloc.construct(this->_start, node(value, this->_alloc));
						this->_start->color = BLACK;
						this->_start->parent = this->_Nil;
						this->_Nil->parent = this->_start;
						this->_size++;
						return (ft::make_pair(iterator(tmp), true));
					}
					while (tmp && tmp->value)
					{
						tmpp = tmp;
						if (!this->_comp(value, *(tmp->value)))
							tmp = tmp->child[RIGHT];
						else if (this->_comp(value, *(tmp->value)))
							tmp = tmp->child[LEFT];
						else
							return (ft::make_pair(iterator(tmp), false));
					}
					tmp = this->_nodealloc.allocate(1);
					this->_nodealloc.construct(tmp, node(value, this->_alloc));
					tmp->parent = tmpp;
					if (tmpp != this->_Nil)
					{
						if (!this->_comp(value, *(tmpp->value)))
							tmp->parent->child[RIGHT] = tmp;
						else if (this->_comp(value, *(tmpp->value)))
							tmp->parent->child[LEFT] = tmp;
						else
						{
							this->_nodealloc.destroy(tmp);
							this->_nodealloc.deallocate(tmp, 1);
							return (ft::make_pair(iterator(tmp), false));
						}
					}
					this->_balance(tmp, tmp->parent);
					this->_size++;
					return (ft::make_pair(iterator(tmp), true));
				}
				iterator insert( iterator pos, const value_type& value )
				{
					(void)pos;
					return (this->insert(value).first);
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
					node * C = S->child[dir];

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
						if (gparent == NULL)
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
					node * to_del = pos.base();
					if (to_del->child[LEFT] && to_del->child[RIGHT])
					{
						node * tmp = to_del->child[RIGHT];
						while (tmp->child[LEFT])
							tmp = tmp->child[LEFT];
						if (to_del == this->_start)
						{
							this->_start = tmp;
							to_del->swap(tmp);
							this->_Nil->parent = this->_start;
							this->_start->parent = this->_Nil;
						}
						else
							to_del->swap(tmp);
					}
					if (to_del->child[LEFT] || to_del->child[RIGHT])
					{
						if (to_del->child[RIGHT])
						{
							if (to_del->parent->value)
							{
								if (to_del == to_del->parent->child[LEFT])
									to_del->parent->child[LEFT] = to_del->child[RIGHT];
								else
									to_del->parent->child[RIGHT] = to_del->child[RIGHT];
							}
							to_del->child[RIGHT]->parent = to_del->parent;
							if (to_del == this->_start)
							{
								this->_start = to_del->child[RIGHT];
								this->_Nil->parent = this->_start;
								this->_start->parent = this->_Nil;
							}
							to_del->child[RIGHT]->color = BLACK;
							this->_nodealloc.destroy(to_del);
							this->_nodealloc.deallocate(to_del, 1);
							this->_size--;
						}
						else
						{
							if (to_del->parent->value)
							{
								if (to_del == to_del->parent->child[LEFT])
									to_del->parent->child[LEFT] = to_del->child[LEFT];
								else
									to_del->parent->child[RIGHT] = to_del->child[LEFT];
							}
							to_del->child[LEFT]->parent = to_del->parent;
							if (to_del == this->_start)
							{
								this->_start = to_del->child[LEFT];
								this->_Nil->parent = this->_start;
								this->_start->parent = this->_Nil;
							}
							to_del->child[LEFT]->color = BLACK;
							this->_nodealloc.destroy(to_del);
							this->_nodealloc.deallocate(to_del, 1);
							this->_size--;
						}
					}
					else if (to_del->parent->value)
					{
						if (to_del->color == BLACK)
						{
							int	dir = to_del->parent->child[RIGHT] == to_del ? RIGHT : LEFT;
							node * parent = to_del->parent;
							node * sib;
							node * D;
							node * C;
							parent->child[dir] = NULL;
							this->_nodealloc.destroy(to_del);
							this->_nodealloc.deallocate(to_del, 1);
							this->_size--;
							to_del = NULL;
							do
							{
								if (to_del)
									dir = to_del->parent->child[RIGHT] == to_del ? RIGHT : LEFT;
								sib = parent->child[1-dir];
								D = sib->child[1-dir];
								C = sib->child[dir];
								if (sib->color == RED)
								{
									this->_case_3(parent, sib, D, C, dir);
									return ;
								}
								if (D && D->color == RED)
								{
									this->_case_6(parent, sib, D, dir);
									return ;
								}
								if (C && C->color == RED)
								{
									this->_case_5(parent, sib, D, C, dir);
									return ;
								}
								if (parent->color == RED)
								{
									sib->color = RED;
									parent->color = BLACK;
									return ;
								}
								sib->color = RED;
								to_del = parent;
								parent = to_del->parent;
							}
							while (parent->value);
							if (parent->value)
								parent->child[RIGHT] == to_del ? parent->child[RIGHT] : parent->child[LEFT] = NULL;
						}
						else
						{
							if (to_del->parent->child[LEFT] == to_del)
								to_del->parent->child[LEFT] = NULL;
							else
								to_del->parent->child[RIGHT] = NULL;
							this->_nodealloc.destroy(to_del);
							this->_nodealloc.deallocate(to_del, 1);
							this->_size--;
						}
					}
					else
					{
						this->_nodealloc.destroy(to_del);
						this->_nodealloc.deallocate(to_del, 1);
						this->_Nil->parent = this->_Nil;
						this->_start = this->_Nil;
						this->_size--;
					}
				}
				void erase(iterator first, iterator last)
				{
					iterator	it;
					while (first != last)
					{
						it = first;
						first++;
						this->erase(it);
					}
				}
				size_type erase(const key_type & key)
				{
					const_iterator	it = find(key);
					if (it != this->end())
					{
						erase(this->find(key));
						return (1);
					}
					return (0);
				}
				iterator find( const key_type& key )
				{
					node *	tmp = this->_start;

					while (tmp && tmp->value)
					{
						if (this->_comp(*(tmp->value), key) == 0 && this->_comp(key, *(tmp->value)) == 0)
							return (iterator(tmp));
						if (this->_comp(*(tmp->value), key))
							tmp = tmp->child[RIGHT];
						else
							tmp = tmp->child[LEFT];
					}
					return (this->end());
				}
				const_iterator find( const key_type& key ) const
				{
					node *	tmp = this->_start;

					while (tmp && tmp->value)
					{
						if (this->_comp(*(tmp->value), key) == 0 && this->_comp(key, *(tmp->value)) == 0)
							return (const_iterator(tmp));
						if (this->_comp(*(tmp->value), key))
							tmp = tmp->child[RIGHT];
						else
							tmp = tmp->child[LEFT];
					}
					return (this->end());
				}
				const_iterator constfind( const key_type& key ) const
				{
					node *	tmp = this->_start;

					while (tmp && tmp->value)
					{
						if (this->_comp(*(tmp->value), key) == 0 && this->_comp(key, *(tmp->value)) == 0)
							return (const_iterator(tmp));
						if (this->_comp(*(tmp->value), key))
							tmp = tmp->child[RIGHT];
						else
							tmp = tmp->child[LEFT];
					}
					return (this->end());
				}
				iterator lower_bound( const key_type& key )
				{
					node * tmp = this->_start;
					node * ret = NULL;
					while (tmp && tmp->value)
					{
						if (this->_comp(*(tmp->value), key) == 0 && this->_comp(key, *(tmp->value)) == 0)
							return (iterator(tmp));
						if (!this->_comp(*(tmp->value), key))
							ret = tmp;
						if (this->_comp(*(tmp->value), key))
							tmp = tmp->child[RIGHT];
						else
							tmp = tmp->child[LEFT];
					}
					if (ret)
						return (iterator(ret));
					return (this->end());
				}
				const_iterator lower_bound( const key_type& key ) const
				{
					node * tmp = this->_start;
					node * ret = NULL;
					while (tmp && tmp->value)
					{
						if (this->_comp(*(tmp->value), key) == 0 && this->_comp(key, *(tmp->value)) == 0)
							return (const_iterator(tmp));
						if (!this->_comp(*(tmp->value), key))
							ret = tmp;
						if (this->_comp(*(tmp->value), key))
							tmp = tmp->child[RIGHT];
						else
							tmp = tmp->child[LEFT];
					}
					if (ret)
						return (const_iterator(ret));
					return (this->end());
				}

				iterator upper_bound( const key_type& key )
				{
					node * tmp = this->_start;
					node * ret = this->_Nil;

					while (tmp->value) {
						if (this->_comp(key, *tmp->value)) {
							ret = tmp;
							if (tmp->child[LEFT])
								tmp = tmp->child[LEFT];
							else
								return (iterator(tmp));
						} else if (this->_comp(*(tmp->value), key)) {
							if (tmp->child[RIGHT])
								tmp = tmp->child[RIGHT];
							else
								return (iterator(ret));
						} else {
							iterator it(tmp);
							it++;
							return (it);
						}
					}
					return (iterator(this->_Nil));
				}
				const_iterator upper_bound( const key_type& key ) const
				{
					node * tmp = this->_start;
					node * ret = this->_Nil;

					while (tmp->value) {
						if (this->_comp(key, *tmp->value)) {
							ret = tmp;
							if (tmp->child[LEFT])
								tmp = tmp->child[LEFT];
							else
								return (iterator(tmp));
						} else if (this->_comp(*tmp->value, key)) {
							if (tmp->child[RIGHT])
								tmp = tmp->child[RIGHT];
							else
								return (iterator(ret));
						} else {
							iterator it(tmp);
							it++;
							return (it);
						}
					}
					return (iterator(this->_Nil));
				}

			private:
				void	_case_3(node * parent, node * sib, node * D, node * C, int dir)
				{
					this->_rotateDirRoot(parent, dir);
					parent->color = RED;
					sib->color = BLACK;
					sib = C;
					D = sib->child[1 - dir];
					if (D != NULL && D->color == RED)
					{
						this->_case_6(parent, sib, D, dir);
						return ;
					}
					C = sib->child[dir];
					if (C != NULL && C->color == RED)
					{
						this->_case_5(parent, sib, D, C, dir);
						return ;
					}
					sib->color = RED;
					parent->color = BLACK;
				}
				void	_case_5(node * parent, node * sib, node * D, node * C, int dir)
				{
					this->_rotateDirRoot(sib, 1 - dir);
					sib->color = RED;
					C->color = BLACK;
					D = sib;
					sib = C;
					this->_case_6(parent, sib, D, dir);
				}
				void	_case_6(node * parent, node * sib, node * D, int dir)
				{
					this->_rotateDirRoot(parent, dir);
					sib->color = parent->color;
					parent->color = BLACK;
					D->color = BLACK;
				}
			public:
				node*					_start;
			private:
				Allocator				_alloc;
				Compare					_comp;
				std::allocator<node>	_nodealloc;
				size_type				_size;
				node *					_Nil;

		};
	template< class T, class Compare, class Alloc >
		bool operator==( const RbTree<T,Compare,Alloc>& lhs, const RbTree<T,Compare,Alloc>& rhs )
		{
			return ((lhs.size() == rhs.size()) && ft::equal(lhs.begin, lhs.end(), rhs.begin()));
		}
	template< class T, class Compare, class Alloc >
		bool operator!=( const RbTree<T,Compare,Alloc>& lhs, const RbTree<T,Compare,Alloc>& rhs )
		{
			return (!(lhs == rhs));
		}
	template< class T, class Compare, class Alloc >
		bool operator<( const RbTree<T,Compare,Alloc>& lhs, const RbTree<T,Compare,Alloc>& rhs )
		{
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		}
	template< class T, class Compare, class Alloc >
		bool operator<=( const RbTree<T,Compare,Alloc>& lhs, const RbTree<T,Compare,Alloc>& rhs )
		{
			return (!(lhs > rhs));
		}
	template< class T, class Compare, class Alloc >
		bool operator>( const RbTree<T,Compare,Alloc>& lhs, const RbTree<T,Compare,Alloc>& rhs )
		{
			return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
		}
	template< class T, class Compare, class Alloc >
		bool operator>=( const RbTree<T,Compare,Alloc>& lhs, const RbTree<T,Compare,Alloc>& rhs )
		{
			return (!(lhs < rhs));
		}

	template< class T, class Compare, class Alloc >
		void swap( RbTree<T,Compare,Alloc>& lhs, RbTree<T,Compare,Alloc>& rhs )
		{
			lhs.swap(rhs);
		}
}

#endif
