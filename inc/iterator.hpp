/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:12:09 by ghanquer          #+#    #+#             */
/*   Updated: 2022/10/20 16:37:48 by ghanquer         ###   ########.fr       */
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
		typedef ptrdiff_t difference_value;
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
		Iterator & operator=(const Iterator & src)
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
		Iterator	operator+(Iterator other) const { return (this->_value + other._value); }
		Iterator	operator-(Iterator other) const { return (this->_value - other._value); }
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
		Iterator	operator[](int i)
		{
			return (this->_value[i]);
		}

	private:
		pointer	_value;
};

#endif
