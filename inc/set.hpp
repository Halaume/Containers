/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:59:23 by ghanquer          #+#    #+#             */
/*   Updated: 2023/01/23 17:10:21 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
#define SET_HPP

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
	template<class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> >
		class set
		{
			public:
				typedef Key										key_type;
				typedef Key										value_type;
				typedef Allocator								allocator_type;
				typedef std::size_t								size_type;
				typedef Compare									key_compare;
				typedef std::ptrdiff_t							difference_type;
				typedef value_type &							reference;
				typedef Compare									value_compare;
				typedef const value_type &						const_reference;
				typedef typename Allocator::pointer				pointer;
				typedef typename Allocator::const_pointer		const_pointer;

				typedef typename ft::RbTree<value_type, value_compare, Allocator>					Tree;
				typedef typename ft::RbTree<value_type, value_compare, Allocator>::const_iterator	const_iterator;
				typedef const_iterator							iterator;
				typedef ft::Reverse_iterator<iterator>			reverse_iterator;
				typedef ft::Reverse_iterator<const_iterator>	const_reverse_iterator;

				//TODO DEL THIS BEFORE END!
				Tree & base(void)
				{
					return (*(this->_tree));
				}

				set(void): _comp(Compare())
				{
					std::allocator<Tree> rballoc;
					this->_alloc = Allocator();
					this->_tree = rballoc.allocate(1);
					Tree val(this->_comp, this->_alloc);
					rballoc.construct(this->_tree, val);
				}

				explicit set(const Compare & comp, const Allocator & alloc = Allocator()): _alloc(alloc), _comp(comp)
			{
				std::allocator<Tree> rballoc;
				this->_tree = rballoc.allocate(1);
				Tree val = Tree(this->_comp, this->_alloc);
				rballoc.construct(this->_tree, val);
			}

				template<class InputIt>
					set(InputIt first, InputIt last, const Compare & comp = Compare(), const Allocator & alloc = Allocator()): _alloc(alloc), _comp(comp)
				{
					std::allocator<Tree> rballoc;
					this->_tree = rballoc.allocate(1);
					Tree val = Tree(first, last, this->_comp, this->_alloc);
					rballoc.construct(this->_tree, val);
				}

				set(const set & copy): _alloc(copy._alloc), _comp(copy._comp)
			{
				std::allocator<Tree> rballoc;
				this->_tree = rballoc.allocate(1);
				rballoc.construct(this->_tree, *(copy._tree));
			}

				~set(void)
				{
					std::allocator<Tree> rballoc;
					rballoc.destroy(this->_tree);
					rballoc.deallocate(this->_tree, 1);
				}

				set& operator=( const set& other )
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

				const_iterator begin() const
				{
					return (this->_tree->constbegin());
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
					ft::pair<typename Tree::iterator, bool>	test(this->_tree->insert(value));
					iterator test2(test.first);
					return (ft::make_pair(test2, test.second));
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
					return (this->_tree->erase(key));
				}

				void swap( set& other )
				{
					ft::swap(this->_tree, other._tree);
				}

				size_type count( const Key& key ) const
				{
					if (this->find(key) == this->end())
						return (0);
					return (1);
				}

				const_iterator find( const Key& key ) const
				{
					return (this->_tree->constfind(key));
				}

				ft::pair<iterator,iterator> equal_range( const Key& key )
				{
					return (ft::make_pair(this->lower_bound(key), this->upper_bound(key)));
				}

				ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const
				{
					return (ft::make_pair(this->lower_bound(key), this->upper_bound(key)));
				}

				const_iterator lower_bound( const Key& key ) const
				{
					return (this->_tree->lower_bound(key));
				}

				const_iterator upper_bound( const Key& key ) const
				{
					return (this->_tree->upper_bound(key));
				}

				key_compare key_comp(void) const
				{
					return (Compare());
				}
				value_compare value_comp(void) const
				{
					return (Compare());
				}

			private:
				Tree *			_tree;
				Allocator		_alloc;
				value_compare	_comp;
		};

	template< class Key, class Compare, class Alloc >
		bool operator==( const set<Key,Compare,Alloc>& lhs, const set<Key,Compare,Alloc>& rhs )
		{
			return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
		}
	template< class Key, class Compare, class Alloc >
		bool operator!=( const set<Key,Compare,Alloc>& lhs, const set<Key,Compare,Alloc>& rhs )
		{
			return (!(lhs == rhs));
		}
	template< class Key, class Compare, class Alloc >
		bool operator<( const set<Key,Compare,Alloc>& lhs, const set<Key,Compare,Alloc>& rhs )
		{
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		}
	template< class Key, class Compare, class Alloc >
		bool operator<=( const set<Key,Compare,Alloc>& lhs, const set<Key,Compare,Alloc>& rhs )
		{
			return (!(lhs > rhs));
		}
	template< class Key, class Compare, class Alloc >
		bool operator>( const set<Key,Compare,Alloc>& lhs, const set<Key,Compare,Alloc>& rhs )
		{
			return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
		}
	template< class Key, class Compare, class Alloc >
		bool operator>=( const set<Key,Compare,Alloc>& lhs, const set<Key,Compare,Alloc>& rhs )
		{
			return (!(lhs < rhs));
		}

	template< class Key, class Compare, class Alloc >
		void swap( set<Key,Compare,Alloc>& lhs, set<Key,Compare,Alloc>& rhs )
		{
			lhs.swap(rhs);
		}
}


#endif
