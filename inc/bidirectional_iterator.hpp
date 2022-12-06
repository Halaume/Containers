/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectional_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 14:59:51 by ghanquer          #+#    #+#             */
/*   Updated: 2022/12/06 18:57:37 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIDIRECTIONNAL_ITERATOR_HPP
#define BIDIRECTIONNAL_ITERATOR_HPP

#include <cstddef>
#include <iterator>
#include "Iterator_traits.hpp"
#include "enable_if.hpp"
#include "is_same.hpp"

#define LEFT 0
#define RIGHT 1

namespace ft
{
	template<typename T, typename RbTree>
		class bIterator
		{
		public:
				typedef std::ptrdiff_t difference_type;
				typedef T value_type;
				typedef T * pointer;
				typedef T & reference;
				typedef std::bidirectional_iterator_tag iterator_category;

				bIterator(void)
				{
				}

				bIterator(const bIterator & copy): _value(copy._value)
				{
				}

				bIterator(pointer value): _value(value)
				{
				}

				~bIterator(void) 
				{
				}

				operator bIterator<const T, RbTree>()
				{
					return (bIterator<const T, RbTree>(this->_value));
				}

				bIterator &	operator=(const bIterator & src)
				{
					if (this == &src)
						return (*this);
					this->_value = src._value;
					return (*this);
				}
				operator	bIterator<iterator_category, RbTree>(void) const
				{
					return (bIterator<iterator_category, RbTree>(this->_value));
				}
				bIterator & operator++(void)
				{
					if (!this->_value->child[RIGHT] && this->_value->parent->value > this->_value->value)
					{
						this->_value = this->_value->parent;
						return (*this);
					}
					else if (!this->_value->child[RIGHT] && this->_value->parent->value < this->_value->value && this->_value->parent->parent && this->_value->parent->parent->value > )
					{
					}
					while (this->_value->child[RIGHT])
						this->_value = this->_value->parent;
					return (*this);
				}
				bIterator operator++(int)
				{
					bIterator tmp = *this;
					++*this;
					return (tmp);
				}
				bIterator & operator--(void)
				{
				}
				bIterator operator--(int)
				{
					bIterator tmp = *this;
					--*this;
					return (tmp);
				}
				reference	operator*(void) const { return (*(this->_value->value)); }
			private:
				T		_value;
				RbTree	_tree;
		};
}

#endif
