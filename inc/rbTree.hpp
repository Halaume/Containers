/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:41:09 by ghanquer          #+#    #+#             */
/*   Updated: 2022/12/12 17:37:22 by ghanquer         ###   ########.fr       */
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
				typedef ft::bIterator<const nodePTR, value_type>	const_iterator;
				typedef ft::Reverse_iterator<iterator>				reverse_iterator;
				typedef ft::Reverse_iterator<const_iterator>		const_reverse_iterator;

				explicit RbTree(const Compare & comp, const Allocator & alloc = Allocator())
				{
					this->_nodealloc = std::allocator<node>();
					this->_start = NULL;
					this->_alloc = alloc;
					this->_comp = comp;
					this->_size = 0;
					value_type	val = value_type();
					this->_nodealloc.construct(this->_Nil, val);
					this->_alloc.destroy(this->_Nil->value);
					this->_alloc.deallocate(this->_Nil->value, 1);
					this->_Nil->value = NULL;
					this->_Nil->parent = this->_Nil;
				}
				RbTree(const RbTree & copy): _start(copy._start), _alloc(copy._alloc), _comp(copy._comp), _nodealloc(copy._nodealloc), _size(copy._size), _Nil(copy._Nil)
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
					value_type	val = value_type();
					this->_nodealloc.construct(this->_Nil, val);
					this->_alloc.destroy(this->_Nil->value);
					this->_alloc.deallocate(this->_Nil->value, 1);
					this->_Nil->value = NULL;
					this->_Nil = this->_start;
					this->_Nil->parent = this->_Nil;
				}
				template<class InputIt>
					RbTree(InputIt first, InputIt last, const Compare & comp = Compare(), const Allocator & alloc = Allocator())
					{
						this->_nodealloc = std::allocator<node>();
						this->_start = NULL;
						this->_alloc = alloc;
						this->_comp = comp;
						this->_size = 0;
						value_type	val = value_type();
						this->_nodealloc.construct(this->_Nil, val);
						this->_alloc.destroy(this->_Nil->value);
						this->_alloc.deallocate(this->_Nil->value, 1);
						this->_Nil->value = NULL;
						this->_Nil->parent = this->_Nil;
						while (first != last)
						{
							this->insert(first);
							first++;
						}
					}
				~RbTree(void)
				{
					this->clear();
					node * to_del;
					to_del = this->_Nil;
					this->_Nil = NULL;
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
				value_type & at( const Key& key )
				{
					iterator tmp = this->find(key);

					if (tmp == this->end())
						throw std::out_of_range("Key not exist");
					return (*tmp);
				}
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
				size_type size(void)
				{
					return (this->_size);
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
						this->_Nil->parent = this->_start;
						this->_size++;
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
					std::cout << "ERASE : " << pos->first << std::endl;
					node * to_del = pos.base();
					if (to_del == this->_start && !this->_start->child[RIGHT] && !this->_start->child[LEFT])
					{
						this->_Nil->parent = this->_Nil;
						this->_delnode(this->_start, false);
						this->_start = this->_Nil;
						return ;
					}
					else if (to_del->child[LEFT] && to_del->child[RIGHT])
					{
						node * tmp = to_del->child[RIGHT];
						while (tmp->child[LEFT])
							tmp = tmp->child[LEFT];
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
								this->_start = to_del->child[RIGHT];
							to_del->child[RIGHT]->color = BLACK;
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
								this->_start = to_del->child[LEFT];
							to_del->child[LEFT]->color = BLACK;
						}
						this->_delnode(to_del, false);
					}
					else if (to_del->color == BLACK)
					{
						int	dir = to_del->parent->child[RIGHT] == to_del ? RIGHT : LEFT;
						node * parent = to_del->parent;
						node * sib;
						node * D;
						node * C;
						parent->child[dir] = NULL;
						this->_delnode(to_del, true);
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
						return ;
					}
					else
						this->_delnode(to_del, true);
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
				iterator find( const Key& key )
				{
					node *	tmp = this->_start;

					while (tmp && tmp->value)
					{
						if (this->_comp(tmp->value, key) == 0 && this->_comp(key, tmp->value) == 0)
							return (iterator(tmp));
						if (this->_comp(tmp->value, key))
							tmp = tmp->child[RIGHT];
						else
							tmp = tmp->child[LEFT];
					}
					return (this->end());
				}
				const_iterator find( const Key& key ) const
				{
					node *	tmp = this->_start;

					while (tmp && tmp->value)
					{
						if (this->_comp(tmp->value, key) == 0 && this->_comp(key, tmp->value) == 0)
							return (const_iterator(tmp));
						if (this->_comp(tmp->value, key))
							tmp = tmp->child[RIGHT];
						else
							tmp = tmp->child[LEFT];
					}
					return (this->end());
				}
				iterator lower_bound( const Key& key )
				{
					node * tmp = this->_start;
					node * ret = NULL;
					while (tmp && tmp->value)
					{
						if (this->_comp(tmp->value, key) == 0 && this->_comp(key, tmp->value) == 0)
							return (iterator(tmp));
						if (!this->_comp(tmp->value, key))
							ret = tmp;
						if (this->_comp(tmp->value, key))
							tmp = tmp->child[RIGHT];
						else
							tmp = tmp->child[LEFT];
					}
					if (ret)
						return (iterator(ret));
					return (this->end());
				}
				const_iterator lower_bound( const Key& key ) const
				{
					node * tmp = this->_start;
					node * ret = NULL;
					while (tmp && tmp->value)
					{
						if (this->_comp(tmp->value, key) == 0 && this->_comp(key, tmp->value) == 0)
							return (const_iterator(tmp));
						if (!this->_comp(tmp->value, key))
							ret = tmp;
						if (this->_comp(tmp->value, key))
							tmp = tmp->child[RIGHT];
						else
							tmp = tmp->child[LEFT];
					}
					if (ret)
						return (const_iterator(ret));
					return (this->end());
				}

				iterator upper_bound( const Key& key )
				{
					node * tmp = this->_start;
					node * ret = NULL;
					while (tmp && tmp->value)
					{
						if (this->_comp(tmp->value, key) == 0 && this->_comp(key, tmp->value) == 0)
							return (iterator(tmp));
						if (this->_comp(tmp->value, key))
							ret = tmp;
						if (this->_comp(tmp->value, key))
							tmp = tmp->child[RIGHT];
						else
							tmp = tmp->child[LEFT];
					}
					if (ret)
						return (iterator(ret));
					return (this->end());
				}
				const_iterator upper_bound( const Key& key ) const
				{
					node * tmp = this->_start;
					node * ret = NULL;
					while (tmp && tmp->value)
					{
						if (this->_comp(tmp->value, key) == 0 && this->_comp(key, tmp->value) == 0)
							return (const_iterator(tmp));
						if (this->_comp(tmp->value, key))
							ret = tmp;
						if (this->_comp(tmp->value, key))
							tmp = tmp->child[RIGHT];
						else
							tmp = tmp->child[LEFT];
					}
					if (ret)
						return (const_iterator(ret));
					return (this->end());
				}

			private:
				void	_delnode(node * my_node, bool is_here)
				{
					node * to_del = my_node;

					if (is_here && my_node->parent->value)
						(my_node->parent->child[RIGHT] == my_node ? my_node->parent->child[RIGHT] : my_node->parent->child[LEFT]) = NULL;
					this->_nodealloc.destroy(to_del);
					this->_nodealloc.deallocate(to_del, 1);
					this->_size--;
				}
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
