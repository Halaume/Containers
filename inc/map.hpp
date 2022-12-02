/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:59:23 by ghanquer          #+#    #+#             */
/*   Updated: 2022/12/02 18:34:49 by ghanquer         ###   ########.fr       */
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
								*/
				map(const map & copy)
				{
					this->_tree = copy._tree;
				}
				~map(void)
				{
				}
				map& operator=( const map& other );
				allocator_type get_allocator() const
				{
					return (this->_alloc);
				}
				T& at( const Key& key );
				T& operator[]( const Key& key );
				iterator begin();
				const_iterator begin() const;
				iterator end();
				const_iterator end() const;
				reverse_iterator rbegin();
				const_reverse_iterator rbegin() const;
				reverse_iterator rend();
				const_reverse_iterator rend() const;
				bool empty() const
				{
					return (this->_tree.empty());
				}
				size_type size() const
				{
					return (this->_size());
				}
				size_type max_size() const
				{
					return (this->_alloc.max_size());
				}
				void clear()
				{
					this->_tree.clear();
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
				iterator erase( iterator pos );
				iterator erase( iterator first, iterator last );
				size_type erase( const Key& key );
				void swap( map& other );
				size_type count( const Key& key ) const;
				iterator find( const Key& key );
				const_iterator find( const Key& key ) const;
				ft::pair<iterator,iterator> equal_range( const Key& key );
				ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const;
				iterator lower_bound( const Key& key );
				const_iterator lower_bound( const Key& key ) const;
				iterator upper_bound( const Key& key );
				const_iterator upper_bound( const Key& key ) const;
				key_compare key_comp() const;
				value_compare value_comp() const;



			private:
				RbTree<Key, T>	_tree;
				Allocator		_alloc;
				size_type		_size;
		};

	template< class Key, class T, class Compare, class Alloc >
		bool operator==( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs );
	template< class Key, class T, class Compare, class Alloc >
		bool operator!=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
		{
			return (!(lhs == rhs));
		}
	template< class Key, class T, class Compare, class Alloc >
		bool operator<( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
		{
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) && lhs != rhs);
		}
	template< class Key, class T, class Compare, class Alloc >
		bool operator<=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
		{
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) || lhs == rhs);
		}
	template< class Key, class T, class Compare, class Alloc >
		bool operator>( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
		{
			return (!(ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())) && lhs != rhs);
		}
	template< class Key, class T, class Compare, class Alloc >
		bool operator>=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
		{
			return (!(ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())) || lhs == rhs);
		}

	template< class Key, class T, class Compare, class Alloc >
		void swap( map<Key,T,Compare,Alloc>& lhs, map<Key,T,Compare,Alloc>& rhs )
		{
			lhs.swap(rhs);
		}
}


#endif
