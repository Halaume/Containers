/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 10:57:10 by ghanquer          #+#    #+#             */
/*   Updated: 2023/01/21 17:10:04 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include <cstddef>
#include <iterator>
#include "iterator.hpp"
#include <iostream>

namespace ft
{
	template <class Iter>
		class Reverse_iterator: public std::iterator<typename ft::iterator_traits<Iter>::iterator_category, typename ft::iterator_traits<Iter>::value_type, typename ft::iterator_traits<Iter>::difference_type, typename ft::iterator_traits<Iter>::pointer, typename ft::iterator_traits<Iter>::reference>
		{
			public:
				typedef Iter iterator_type;
				typedef typename Iter::iterator_category iterator_category;
				typedef typename Iter::value_type value_type;
				typedef typename Iter::difference_type difference_type;
				typedef typename Iter::pointer pointer;
				typedef typename Iter::reference reference;
				Reverse_iterator(void) { _current = Iter(); }
				explicit Reverse_iterator(iterator_type x)
				{
					this->_current = x;
				}
				template< class U >
					Reverse_iterator(const Reverse_iterator<U> & other)
					{
						_current = other.base();
					}
				Reverse_iterator &	operator=(const Reverse_iterator & src)
				{
					if (this == &src)
						return (*this);
					this->_current = src.base();
					return (*this);
				}

				operator Reverse_iterator<const Iter>()
				{
					return (Reverse_iterator<const Iter>(this->_current));
				}

				iterator_type base() const { return (this->_current); }

				Reverse_iterator &	operator+=(difference_type other) 
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
				Reverse_iterator		operator+(difference_type nb) { return (Reverse_iterator(this->_current - nb)); }
				Reverse_iterator &		operator-=(difference_type nb) { this->_current += nb; return (*this); }
				Reverse_iterator		operator-(difference_type nb) const { return (Reverse_iterator(this->_current + nb)); }
				Reverse_iterator &		operator++(void) { --_current; return (*this); }
				Reverse_iterator		operator++(int)
				{
					Reverse_iterator tmp = *this;
					++*this;
					return (tmp);
				}
				Reverse_iterator &	operator--(void) { ++_current; return (*this); }
				Reverse_iterator	operator--(int)
				{
					Reverse_iterator tmp = *this;
					--*this;
					return (tmp);
				}
				reference	operator*(void) { Iter tmp = this->_current; return (*(--tmp)); }
				pointer		operator->(void) { Iter tmp = this->_current; return (&(*(--tmp))); }
				pointer		operator->(void) const { Iter tmp = this->_current; return (&(*(--tmp))); }
				reference	operator[](int i)
				{
					return (*(*this + i));
				}

			private:
				Iter	_current;
		};
	template <class T, class U>
		bool		operator>(const Reverse_iterator<T>& lhs, const Reverse_iterator<U>& rhs)
		{
			return (lhs.base() < rhs.base());
		}

	template <class T, class U>
		bool		operator<(const Reverse_iterator<T>& lhs, const Reverse_iterator<U>& rhs)
		{
			return (lhs.base() > rhs.base());
		}

	template <class T, class U>
		bool		operator>=(const Reverse_iterator<T>& lhs, const Reverse_iterator<U>& rhs)
		{
			return (lhs.base() <= rhs.base());
		}

	template <class T, class U>
		bool		operator<=(const Reverse_iterator<T>& lhs, const Reverse_iterator<U>& rhs)
		{
			return (lhs.base() >= rhs.base());
		}

	template <class T, class U>
		bool		operator==(const Reverse_iterator<T>& lhs, const Reverse_iterator<U>& rhs)
		{
			return (lhs.base() == rhs.base());
		}

	template <class T, class U>
		bool		operator!=(const Reverse_iterator<T>& lhs, const Reverse_iterator<U>& rhs)
		{
			return (lhs.base() != rhs.base());
		}
		template <class T>
		ft::Reverse_iterator<T>	operator+(typename ft::Reverse_iterator<T>::difference_type nb, Reverse_iterator<T> const & it) { return (Reverse_iterator<T>(it.base() - nb)); }

	template <class T, class U>
		typename Reverse_iterator<T>::difference_type	operator-(const Reverse_iterator<T>& lhs, const Reverse_iterator<U>& rhs){ return (rhs.base() - lhs.base()); }

}

#endif
