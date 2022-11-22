/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:45:44 by ghanquer          #+#    #+#             */
/*   Updated: 2022/11/22 13:45:00 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

#include <iterator>
#include <cstddef>

namespace ft
{

	template <class Iterator> 
		struct iterator_traits
		{
			typedef typename Iterator::difference_type difference_type;
			typedef typename Iterator::value_type value_type;
			typedef typename Iterator::pointer pointer;
			typedef typename Iterator::reference reference;
			typedef typename Iterator::iterator_category iterator_category;
		};

	template <class T> 
		struct iterator_traits<T*>
		{
			typedef ptrdiff_t difference_type;
			typedef T value_type;
			typedef T * pointer;
			typedef T & reference;
			typedef std::random_access_iterator_tag iterator_category;
		};

	template <class T> 
		struct iterator_traits<const T*>
		{
			typedef ptrdiff_t difference_type;
			typedef T value_type;
			typedef T * pointer;
			typedef T & reference;
			typedef std::random_access_iterator_tag iterator_category;
		};
}

#endif
