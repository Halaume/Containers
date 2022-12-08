/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectional_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 14:59:51 by ghanquer          #+#    #+#             */
/*   Updated: 2022/12/08 12:40:38 by ghanquer         ###   ########.fr       */
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
	template<typename T>
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
					this->_value();
					this->_tree();
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

				operator bIterator<const T>()
				{
					return (bIterator<const T>(this->_value));
				}

				bIterator &	operator=(const bIterator & src)
				{
					if (this == &src)
						return (*this);
					this->_value = src._value;
					return (*this);
				}
				operator	bIterator<iterator_category>(void) const
				{
					return (bIterator<iterator_category>(this->_value));
				}
				bIterator & operator++(void)
				{
					if (this->_value->value == NULL)
					{
						this->_value = this->_value->parent;
						return (*this);
					}
					T	tmp(this->_value);
					if (tmp->child[RIGHT])
					{
						tmp = tmp->child[RIGHT];
						while (tmp->child[LEFT])
							tmp = tmp->child[LEFT];
					}
					else
					{
						while (tmp->parent && tmp->parent->child[RIGHT] != tmp)
						{
							tmp = tmp->parent;
						}
						tmp = tmp->parent;
					}
					this->_value = tmp;
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
					T	tmp(this->_value);
					if (tmp->child[LEFT])
					{
						tmp = tmp->child[LEFT];
						while (tmp->child[RIGHT])
							tmp = tmp->child[RIGHT];
					}
					else
					{
						while (tmp->parent && tmp->parent->child[LEFT] != tmp)
						{
							tmp = tmp->parent;
						}
						tmp = tmp->parent;
					}
					this->_value = tmp;
					return (*this);

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
		};
}

#endif
