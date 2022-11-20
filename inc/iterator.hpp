/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:12:09 by ghanquer          #+#    #+#             */
/*   Updated: 2022/11/20 15:06:58 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>
#include <iterator>

/*template <class Category, class T, class Distance = ptrdiff_t,
  class Pointer = T*, class Reference = T&>
  struct iterator {
  typedef T         value_type;
  typedef Distance  difference_type;
  typedef Pointer   pointer;
  typedef Reference reference;
  typedef Category  iterator_category;
  };*/

namespace ft
{
	template <class Iterator> 
		class iterator_traits
		{
			public:
				typedef typename Iterator::difference_type difference_type;
				typedef typename Iterator::value_type value_type;
				typedef typename Iterator::pointer pointer;
				typedef typename Iterator::reference reference;
				typedef typename Iterator::iterator_category iterator_category;
		};

	template <class T> 
		class iterator_traits<T*>
		{
			public:
				typedef ptrdiff_t difference_type;
				typedef T value_type;
				typedef T * pointer;
				typedef T & reference;
				typedef std::random_access_iterator_tag iterator_category;
		};

	template <class T> 
		class iterator_traits<const T*>
		{
			public:
				typedef ptrdiff_t difference_type;
				typedef T value_type;
				typedef T * pointer;
				typedef T & reference;
				typedef std::random_access_iterator_tag iterator_category;
		};

	template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
		class Iterator
		{
			public:
				typedef typename iterator_traits<Pointer>::difference_type difference_type;
				typedef typename iterator_traits<Pointer>::iterator_category iterator_category;
				typedef typename iterator_traits<Pointer>::value_type value_type;
				typedef typename iterator_traits<Pointer>::pointer pointer;
				typedef typename iterator_traits<Pointer>::reference reference;

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

				Iterator &	operator=(const Iterator & src)
				{
					if (this == &src)
						return (*this);
					this->_value = src._value;
					return (*this);
				}
				operator	Iterator<Category, const T>(void) const
				{
					return (Iterator<Category, const T>(this->_value));
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
				Iterator		operator+(difference_type nb) const { Iterator temp = *this; return (temp += nb); }
				friend Iterator	operator+(int nb, Iterator const & it) { Iterator temp(it); return (temp += nb); }
				Iterator &		operator-=(difference_type nb) { return (*this += -nb); }
				Iterator		operator-(difference_type nb) const { Iterator temp = *this; return (temp -= nb); }
				difference_type	operator-(Iterator other) const { return ((this->_value - other._value)); }
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
				reference	operator[](int i)
				{
					return (*(*this + i));
				}
				reference	operator*(void) { return (*(this->_value)); }
				pointer		operator->(void) { return (this->_value); }

			private:
				pointer	_value;
		};

	template <class Category, class T>
		bool		operator>(Iterator<Category, T> lhs, Iterator<Category, T> rhs)
		{
			return (!(rhs < lhs) && rhs != lhs);
		}

	template <class Category, class T>
		bool		operator<(Iterator<Category, T> lhs, Iterator<Category, T> rhs)
		{
			return ((rhs - lhs) < 0);
		}

	template <class Category, class T>
		bool		operator>=(Iterator<Category, T> lhs, Iterator<Category, T> rhs)
		{
			return (!(lhs < rhs));
		}

	template <class Category, class T>
		bool		operator<=(Iterator<Category, T> lhs, Iterator<Category, T> rhs)
		{
			return (!(lhs > rhs));
		}

	template <class Category, class T>
		bool		operator==(Iterator<Category, T> lhs, Iterator<Category, T> rhs)
		{
			return (lhs->_value == rhs._value);
		}

	template <class Category, class T>
		bool		operator!=(Iterator<Category, T> lhs, Iterator<Category, T> rhs)
		{
			return (lhs->_value != rhs._value);
		}

	template <class Iter>
		class Reverse_iterator
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
				Reverse_iterator(const Reverse_iterator<Iter> & other)
				{
					_current = Iter(other);
				}
				Reverse_iterator &	operator=(const Reverse_iterator & src)
				{
					if (this == &src)
						return (*this);
					this->_current = src._current;
					return (*this);
				}
				bool		operator>(Reverse_iterator other) const { return (other._current > this->_current); }
				bool		operator<(Reverse_iterator other) const { return (other._current < this->_current); }
				bool		operator>=(Reverse_iterator other) const { return (this->_current >= other._current); }
				bool		operator<=(Reverse_iterator other) const { return (this->_current <= other._current); }
				bool		operator==(Reverse_iterator other) const { return (this->_current == other._current); }
				bool		operator!=(Reverse_iterator other) const { return (this->_current != other._current); }

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
				Reverse_iterator		operator+(difference_type nb) { Reverse_iterator temp = *this; return (temp += nb); }
				Reverse_iterator &		operator-=(difference_type nb) { return (*this += -nb); }
				Reverse_iterator		operator-(difference_type nb) const { Reverse_iterator temp = *this; return (temp -= nb); }
				difference_type	operator-(Reverse_iterator other) const { return ((this->_current - other._current)); }
				Reverse_iterator &	operator++(void) { --_current; return (*this); }
				Reverse_iterator	operator++(int)
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
				reference	operator*(void) { return (*(this->_current)); }
				pointer		operator->(void) { return (this->_current); }

			private:
				Iter	_current;
		};
}

#endif
