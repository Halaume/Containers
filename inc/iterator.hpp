/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:12:09 by ghanquer          #+#    #+#             */
/*   Updated: 2022/11/23 18:05:59 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>
#include <iterator>
#include "Iterator_traits.hpp"

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
	template <typename T>
		class Iterator
		{
			public:
				typedef ptrdiff_t difference_type;
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
				difference_type	operator-(Iterator<value_type> it) { return (this->_value - it._value); }
				difference_type	operator-(Iterator<const value_type> it) const { return (this->_value - &(*it)); }
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
				reference	operator*(void) { return (*(this->_current - 1)); }
				pointer		operator->(void) { return (&(*(this->_current - 1))); }
				reference	operator[](int i)
				{
					return (*(*this + i));
				}

			private:
				Iter	_current;
		};
	template <class T>
		bool		operator>(Reverse_iterator<T> lhs, Reverse_iterator<T> rhs)
		{
			return (!(rhs < lhs) && rhs != lhs);
		}

	template <class T>
		bool		operator<(Reverse_iterator<T> lhs, Reverse_iterator<T> rhs)
		{
			return ((rhs - lhs) < 0);
		}

	template <class T>
		bool		operator>=(Reverse_iterator<T> lhs, Reverse_iterator<T> rhs)
		{
			return (!(lhs < rhs));
		}

	template <class T>
		bool		operator<=(Reverse_iterator<T> lhs, Reverse_iterator<T> rhs)
		{
			return (!(lhs > rhs));
		}

	template <class T>
		bool		operator==(Reverse_iterator<T> lhs, Reverse_iterator<T> rhs)
		{
			return (&(*lhs) == &(*rhs));
		}

	template <class T>
		bool		operator!=(Reverse_iterator<T> lhs, Reverse_iterator<T> rhs)
		{
			return (!(lhs == rhs));
		}

	template <class T>
				ft::Reverse_iterator<T>	operator+(typename ft::Reverse_iterator<T>::difference_type nb, Reverse_iterator<T> const & it) { return (Reverse_iterator<T>(it.base() - nb)); }

	template <class T, class U>
				typename Reverse_iterator<T>::difference_type	operator-(const Reverse_iterator<T>& lhs, const Reverse_iterator<U>& rhs){ return (rhs.base() - lhs.base()); }
}

#endif
