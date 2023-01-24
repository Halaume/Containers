/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:12:09 by ghanquer          #+#    #+#             */
/*   Updated: 2023/01/24 16:24:05 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>
#include <iterator>
#include "Iterator_traits.hpp"
#include "enable_if.hpp"
#include "is_same.hpp"

namespace ft
{
	template <typename T>
		class Iterator
		{
			public:
				typedef std::ptrdiff_t difference_type;
				typedef T value_type;
				typedef T * pointer;
				typedef T & reference;
				typedef std::random_access_iterator_tag iterator_category;

				Iterator(void)
				{
				}

				Iterator(const Iterator & copy): _value(copy._value)
				{
				}

				Iterator(pointer value): _value(value)
				{
				}

				~Iterator(void) 
				{
				}

				const pointer & base(void) const
				{
					return (_value);
				}
				operator Iterator<const T>()
				{
					return (Iterator<const T>(this->_value));
				}

				Iterator &	operator=(const Iterator & src)
				{
					if (this == &src)
						return (*this);
					this->_value = src._value;
					return (*this);
				}
				operator	Iterator<iterator_category>(void) const
				{
					return (Iterator<iterator_category>(this->_value));
				}
				Iterator &	operator+=(difference_type other)
				{
					difference_type m = other;
					if (m >= 0)
					{
						while (m--)
							++*this;
					}
					else
					{
						while (m++)
							--*this;
					}
					return (*this);
				}
				Iterator		operator+(difference_type nb) const { return (Iterator(this->_value + nb)); }
				Iterator &		operator-=(difference_type nb) { return (*this += -nb); }
				Iterator		operator-(difference_type nb) const { return (Iterator(this->_value - nb)); }
				difference_type	operator-( const Iterator it) const { return (this->_value - &(*it)); }
				template <class U>
				difference_type	operator-(const Iterator<U> it) const { return (this->_value - &(*it)); }
				Iterator &		operator++(void) { this->_value++; return (*this); }
				Iterator		operator++(int)
				{
					Iterator tmp = *this;
					++*this;
					return (tmp);
				}
				Iterator &	operator--(void) { this->_value--; return (*this); }
				Iterator	operator--(int)
				{
					Iterator tmp = *this;
					--*this;
					return (tmp);
				}
				reference	operator[](int i) const
				{
					return (*(*this + i));
				}
				reference	operator*(void) const { return (*(this->_value)); }
				pointer		operator->(void) const { return (this->_value); }

			private:
				pointer	_value;
		};

	template <class T>
				ft::Iterator<T>	operator+(typename ft::Iterator<T>::difference_type nb, Iterator<T> const & it) { return (it + nb); }

	template <class T>
		bool		operator>(Iterator<T> lhs, Iterator<T> rhs)
		{
			return (&(*lhs) > &(*rhs));
		}

	template <class T>
		bool		operator<(Iterator<T> lhs, Iterator<T> rhs)
		{
			return (&(*lhs) < &(*rhs));
		}

	template <class T>
		bool		operator>=(Iterator<T> lhs, Iterator<T> rhs)
		{
			return (!(lhs < rhs));
		}

	template <class T>
		bool		operator<=(Iterator<T> lhs, Iterator<T> rhs)
		{
			return (!(lhs > rhs));
		}

	template <class T>
		bool		operator==(Iterator<T> lhs, Iterator<T> rhs)
		{
			return (&(*lhs) == &(*rhs));
		}

	template <class T>
		bool		operator!=(Iterator<T> lhs, Iterator<T> rhs)
		{
			return (!(lhs == rhs));
		}

	template <typename it1, typename it2>
		bool		operator>(it1 lhs, it2 rhs)
		{
			return (&(*lhs) > &(*rhs));
		}

	template <typename it1, typename it2>
		bool		operator<(it1 lhs, it2 rhs)
		{
			return (&(*lhs) < &(*rhs));
		}

	template <typename it1, typename it2>
		bool		operator>=(it1 lhs, it2 rhs)
		{
			return (!(lhs < rhs));
		}

	template <typename it1, typename it2>
		bool		operator<=(it1 lhs, it2 rhs)
		{
			return (!(lhs > rhs));
		}

	template <typename it1, typename it2>
		bool		operator==(it1 lhs, it2 rhs)
		{
			return (&(*lhs) == &(*rhs));
		}

	template <typename it1, typename it2>
		bool		operator!=(it1 lhs, it2 rhs)
		{
			return (!(lhs == rhs));
		}
}

#endif
