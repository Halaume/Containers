/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectional_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 14:59:51 by ghanquer          #+#    #+#             */
/*   Updated: 2023/01/20 16:35:55 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIDIRECTIONNAL_ITERATOR_HPP
#define BIDIRECTIONNAL_ITERATOR_HPP

#include <cstddef>
#include <iterator>
#include "Iterator_traits.hpp"
#include "enable_if.hpp"
#include "is_same.hpp"
#include "pair.hpp"
#include <iostream>

#define LEFT 0
#define RIGHT 1

namespace ft
{
	template<typename T, class value_typee>
		class bIterator
		{
			public:
				typedef value_typee						value_type;
				typedef std::ptrdiff_t					difference_type;
				typedef value_type *					pointer;
				typedef value_type &					reference;
				typedef std::bidirectional_iterator_tag	iterator_category;

				bIterator(void): _value()
				{
				}

				bIterator(const bIterator & copy): _value(copy._value)
			{
			}

				bIterator(T value): _value(value)
			{
			}

				~bIterator(void) 
				{
				}

				operator bIterator<T, const value_type>()
				{
					return (bIterator<T, const value_type>(this->_value));
				}
				operator	bIterator<iterator_category, value_type>(void) const
				{
					return (bIterator<iterator_category, value_type>(this->_value));
				}
				bIterator &	operator=(const bIterator & src)
				{
					if (this == &src)
						return (*this);
					this->_value = src._value;
					return (*this);
				}
				T base() const { return (this->_value); }
				bIterator & operator++(void)
				{
					if (this->_value->value == NULL)
					{
						this->_value = this->_value->parent;
						while (this->_value->child[LEFT])
							this->_value = this->_value->child[LEFT];
						return (*this);
					}
					if (this->_value->child[RIGHT])
					{
						this->_value = this->_value->child[RIGHT];
						while (this->_value->child[LEFT])
							this->_value = this->_value->child[LEFT];
					}
					else
					{
						while (this->_value->parent->value && this->_value->parent->child[RIGHT] == this->_value)
							this->_value = this->_value->parent;
						this->_value = this->_value->parent;
					}
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
					if (this->_value->value == NULL)
					{
						this->_value = this->_value->parent;
						while (this->_value->child[RIGHT])
							this->_value = this->_value->child[RIGHT];
						return (*this);
					}
					if (this->_value->child[LEFT])
					{
						this->_value = this->_value->child[LEFT];
						while (this->_value->child[RIGHT])
							this->_value = this->_value->child[RIGHT];
					}
					else
					{
						while (this->_value->parent->value && this->_value->parent->child[LEFT] == this->_value)
							this->_value = this->_value->parent;
						this->_value = this->_value->parent;
					}
					return (*this);
				}
				bIterator operator--(int)
				{
					bIterator tmp = *this;
					--*this;
					return (tmp);
				}
				reference	operator*(void) const { return (*(this->_value->value)); ;}
				pointer		operator->(void) const { return (&(*(this->_value->value))); }
				pointer		operator->(void) { return (&(*(this->_value->value))); }
			private:
				T		_value;
		};
	template <class T, class value_type>
		bool		operator==(bIterator<T, value_type> lhs, bIterator<T, value_type> rhs)
		{
			return (&(*lhs) == &(*rhs));
		}

	template <class T, class value_type>
		bool		operator!=(bIterator<T, value_type> lhs, bIterator<T, value_type> rhs)
		{
			return (!(lhs == rhs));
		}
}

#endif
