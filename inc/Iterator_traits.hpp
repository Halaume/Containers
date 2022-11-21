/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:45:44 by ghanquer          #+#    #+#             */
/*   Updated: 2022/11/21 15:47:48 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

#include <iterator>
#include <cstddef>

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
}

#endif
