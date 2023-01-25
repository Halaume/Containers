/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:59:23 by ghanquer          #+#    #+#             */
/*   Updated: 2023/01/25 16:01:45 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <cstddef>
#include <functional>
#include <memory>
#include "pair.hpp"
#include "reverse_iterator.hpp"
#include "bidirectional_iterator.hpp"
#include "rbTree.hpp"
#include "lexicographical_compare.hpp"
#include "enable_if.hpp"
#include "is_integral.hpp"
#include "is_same.hpp"

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

				class value_compare : public std::binary_function<key_type, value_type, key_compare>
			{
				friend class map;

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

			private:
				typedef typename ft::RbTree<value_type, value_compare, Allocator>	Tree;
			public:
				typedef typename ft::RbTree<value_type, value_compare, Allocator>::iterator						iterator;
				typedef typename ft::RbTree<value_type, value_compare, Allocator>::const_iterator						const_iterator;
				typedef ft::Reverse_iterator<iterator>			reverse_iterator;
				typedef ft::Reverse_iterator<const_iterator>	const_reverse_iterator;

				map(void): _comp(Compare())
				{
					std::allocator<Tree> rballoc;
					this->_alloc = Allocator();
					this->_tree = rballoc.allocate(1);
					Tree val(this->_comp, this->_alloc);
					rballoc.construct(this->_tree, val);
				}

				explicit map(const Compare & comp, const Allocator & alloc = Allocator()): _alloc(alloc), _comp(comp)
			{
				std::allocator<Tree> rballoc;
				this->_tree = rballoc.allocate(1);
				Tree val = Tree(this->_comp, this->_alloc);
				rballoc.construct(this->_tree, val);
			}

				template<class InputIt>
					map(InputIt first, InputIt last, const Compare & comp = Compare(), const Allocator & alloc = Allocator()): _alloc(alloc), _comp(comp)
				{
					std::allocator<Tree> rballoc;
					this->_tree = rballoc.allocate(1);
					Tree val = Tree(first, last, this->_comp, this->_alloc);
					rballoc.construct(this->_tree, val);
				}

				map(const map & copy): _alloc(copy._alloc), _comp(copy._comp.comp)
			{
				std::allocator<Tree> rballoc;
				this->_tree = rballoc.allocate(1);
				rballoc.construct(this->_tree, *(copy._tree));
			}

				~map(void)
				{
					std::allocator<Tree> rballoc;
					rballoc.destroy(this->_tree);
					rballoc.deallocate(this->_tree, 1);
				}

				map& operator=( const map& other )
				{
					if (this == &other)
						return (*this);
					std::allocator<Tree> rballoc;
					if (other._tree == NULL)
					{
						if (this->_tree)
						{
							rballoc.destroy(this->_tree);
							rballoc.deallocate(this->_tree, 1);
						}
						this->_tree = NULL;
					}
					else if (this->_tree)
						*(this->_tree) = *(other._tree);
					else
					{
						this->_tree = rballoc.allocate(1);
						rballoc.construct(this->_tree, *(other._tree));
					}
					return (*this);
				}

				allocator_type get_allocator() const
				{
					return (this->_alloc);
				}

				T& at( const Key& key )
				{
					return (this->_tree->at(ft::make_pair(key, T())).second);
				}

				const T& at(const Key& key) const
				{
					return (this->_tree->at(ft::make_pair(key, T())).second);
				}

				T& operator[]( const Key& key )
				{
					iterator tmp = this->find(key);
					if (tmp != this->end())
						return ((*tmp).second);
					this->_tree->insert(ft::make_pair(key, T()));
					return ((*(this->find(key))).second);
				}

				iterator begin()
				{
					return (this->_tree->begin());
				}

				const_iterator begin() const
				{
					return (this->_tree->constbegin());
				}

				iterator end()
				{
					return (this->_tree->end());
				}

				const_iterator end() const
				{
					return (this->_tree->constend());
				}

				reverse_iterator rbegin()
				{
					return (this->_tree->rbegin());
				}

				const_reverse_iterator rbegin() const
				{
					return (this->_tree->rconstbegin());
				}

				reverse_iterator rend()
				{
					return (this->_tree->rend());
				}

				const_reverse_iterator rend() const
				{
					return (this->_tree->rconstend());
				}

				bool empty() const
				{
					return (this->_tree->empty());
				}

				size_type size() const
				{
					return (this->_tree->size());
				}

				size_type max_size() const
				{
					return (this->_tree->max_size());
				}

				void clear()
				{
					this->_tree->clear();
				}

				ft::pair<iterator, bool>	insert(const value_type & value)
				{
					return (this->_tree->insert(value));
				}

				iterator	insert(iterator pos, const value_type & value)
				{
					return (this->_tree->insert(pos, value));
				}

				template<class InputIt>
					void insert(InputIt first, InputIt last)
					{
						this->_tree->insert(first, last);
					}

				void erase( iterator pos )
				{
					this->_tree->erase(pos);
				}

				void erase( iterator first, iterator last )
				{
					this->_tree->erase(first, last);
				}

				size_type erase( const Key& key )
				{
					return (this->_tree->erase(ft::make_pair(key, T())));
				}

				void swap( map& other )
				{
					ft::swap(this->_tree, other._tree);
				}

				size_type count( const Key& key ) const
				{
					if (this->find(key) == this->end())
						return (0);
					return (1);
				}
				iterator find( const Key& key )
				{
					return (this->_tree->find(ft::make_pair(key, T())));
				}

				const_iterator find( const Key& key ) const
				{
					return (this->_tree->constfind(ft::make_pair(key, T())));
				}

				ft::pair<iterator,iterator> equal_range( const Key& key )
				{
					return (ft::make_pair(this->lower_bound(key), this->upper_bound(key)));
				}

				ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const
				{
					return (ft::make_pair(this->lower_bound(key), this->upper_bound(key)));
				}
				iterator lower_bound( const Key& key )
				{
					return (this->_tree->lower_bound(ft::make_pair(key, T())));
				}

				const_iterator lower_bound( const Key& key ) const
				{
					return (this->_tree->lower_bound(ft::make_pair(key, T())));
				}

				iterator upper_bound( const Key& key )
				{
					return (this->_tree->upper_bound(ft::make_pair(key, T())));
				}

				const_iterator upper_bound( const Key& key ) const
				{
					return (this->_tree->upper_bound(ft::make_pair(key, T())));
				}

				key_compare key_comp(void) const
				{
					return (Compare());
				}
				value_compare value_comp(void) const
				{
					return (value_compare(Compare()));
				}



			private:
				Tree *			_tree;
				Allocator		_alloc;
				value_compare	_comp;
		};

	template< class Key, class T, class Compare, class Alloc >
		bool operator==( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
		{
			return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
		}
	template< class Key, class T, class Compare, class Alloc >
		bool operator!=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
		{
			return (!(lhs == rhs));
		}
	template< class Key, class T, class Compare, class Alloc >
		bool operator<( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
		{
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		}
	template< class Key, class T, class Compare, class Alloc >
		bool operator<=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
		{
			return (!(lhs > rhs));
		}
	template< class Key, class T, class Compare, class Alloc >
		bool operator>( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
		{
			return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
		}
	template< class Key, class T, class Compare, class Alloc >
		bool operator>=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
		{
			return (!(lhs < rhs));
		}

	template< class Key, class T, class Compare, class Alloc >
		void swap( map<Key,T,Compare,Alloc>& lhs, map<Key,T,Compare,Alloc>& rhs )
		{
			lhs.swap(rhs);
		}
}


#endif
