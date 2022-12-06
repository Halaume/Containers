/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_bidirectional_iterator.hpp                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 16:28:31 by ghanquer          #+#    #+#             */
/*   Updated: 2022/12/06 16:30:05 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_BIDIRECTIONNAL_ITERATOR_HPP
#define REVERSE_BIDIRECTIONNAL_ITERATOR_HPP

#include <cstddef>
#include <iterator>
#include "Iterator_traits.hpp"
#include "enable_if.hpp"
#include "is_same.hpp"

namespace ft
{
	template<typename Iter>
		class rbIterator
		{
		public:
				typedef Iter iterator_type;
				typedef typename Iter::iterator_category iterator_category;
				typedef typename Iter::value_type value_type;
				typedef typename Iter::difference_type difference_type;
				typedef typename Iter::pointer pointer;
				typedef typename Iter::reference reference;

		};
}

#endif
