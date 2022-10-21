/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:12:09 by ghanquer          #+#    #+#             */
/*   Updated: 2022/10/21 15:32:07 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>

/*template <class Category, class T, class Distance = ptrdiff_t,
  class Pointer = T*, class Reference = T&>
  struct iterator {
  typedef T         value_type;
  typedef Distance  difference_type;
  typedef Pointer   pointer;
  typedef Reference reference;
  typedef Category  iterator_category;
  };*/

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
		//		typedef random_access_iterator_tag iterator_category;
};

template <class T> 
class iterator_traits<const T*>
{
	public:
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T * pointer;
		typedef T & reference;
		//		typedef random_access_iterator_tag iterator_category;
};

template <class T>
class Iterator
{
	public:
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T * pointer;
		typedef T & reference;
		Iterator(void) {}
		Iterator(const Iterator & copy)
		{
			*this = copy;
		}
		Iterator(pointer value) { this->_value = value; }
		~Iterator(void) {}
		Iterator &	operator=(const Iterator & src)
		{
			if (this == &src)
				return (*this);
			this->_value = src._value;
			return (*this);
		}
		bool		operator>(Iterator other) const { return (this->_value > other._value); }
		bool		operator<(Iterator other) const { return (this->_value < other._value); }
		bool		operator>=(Iterator other) const { return (this->_value >= other._value); }
		bool		operator<=(Iterator other) const { return (this->_value <= other._value); }
		bool		operator==(Iterator other) const { return (this->_value == other._value); }
		bool		operator!=(Iterator other) const { return (this->_value != other._value); }

		Iterator &	operator+=(difference_type other) const 
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
		Iterator	operator+(difference_type nb) const { Iterator temp = this->value; return (temp += nb); }
		Iterator &	operator-=(difference_type nb) const { return (*this += -nb); }
		Iterator	operator-(Iterator other) const { return ((this->_value - other._value)); }
//		Iterator	operator-(difference_type nb) const { Iterator temp = this->value; return (temp -= nb); }
// A comprendre
		Iterator	operator++(void) { return (this->_value++); }
		Iterator	operator++(int)
		{
			Iterator tmp = *this;
			++*this;
			return (tmp);
		}
		Iterator	operator--(void) { return (this->_value--); }
		Iterator	operator--(int)
		{
			Iterator tmp = *this;
			--*this;
			return (tmp);
		}
		reference	operator[](int i)
		{
			return (*(this->_value + i));
		}

	private:
		pointer	_value;
};

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
		Reverse_iterator(void) { current = Iter(); }
		explicit Reverse_iterator(iterator_type x)
		{
			current = x;
		}
		Reverse_iterator(const Reverse_iterator<Iter> & other)
		{
			current = Iter(other);
		}
		Reverse_iterator &	operator=(const Reverse_iterator & src)
		{
			if (this == &src)
				return (*this);
			this->_value = src._value;
			return (*this);
		}
		bool				operator>(Reverse_iterator other) const { return (this->_value > other._value); }
		bool				operator<(Reverse_iterator other) const { return (this->_value < other._value); }
		bool				operator>=(Reverse_iterator other) const { return (this->_value >= other._value); }
		bool				operator<=(Reverse_iterator other) const { return (this->_value <= other._value); }
		bool				operator==(Reverse_iterator other) const { return (this->_value == other._value); }
		bool				operator!=(Reverse_iterator other) const { return (this->_value != other._value); }
		Reverse_iterator	operator+(Reverse_iterator other) const { return (this->_value + other._value); }
		Reverse_iterator	operator-(Reverse_iterator other) const { return (this->_value - other._value); }

		Reverse_iterator	operator++(void) { --current; return (*this); }
		Reverse_iterator	operator++(int)
		{
			Reverse_iterator tmp = *this;
			++*this;
			return (tmp);
		}
		Reverse_iterator	operator--(void) { ++current; return (*this); }
		Reverse_iterator	operator--(int)
		{
			Reverse_iterator tmp = *this;
			--*this;
			return (tmp);
		}

	private:
		Iter	current;
};

#endif
