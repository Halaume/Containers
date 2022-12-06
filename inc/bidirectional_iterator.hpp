/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectional_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 14:59:51 by ghanquer          #+#    #+#             */
/*   Updated: 2022/12/06 16:07:21 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIDIRECTIONNAL_ITERATOR_HPP
#define BIDIRECTIONNAL_ITERATOR_HPP

#include <cstddef>
#include <iterator>
#include "Iterator_traits.hpp"
#include "enable_if.hpp"
#include "is_same.hpp"

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
			private:
				pointer _value;
		};
}

#endif
