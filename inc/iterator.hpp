/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:12:09 by ghanquer          #+#    #+#             */
/*   Updated: 2022/10/19 14:02:02 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>

template <class Category, class T, class Distance = ptrdiff_t,
		 class Pointer = T*, class Reference = T&>
struct iterator {
	 typedef T         value_type;
	 typedef Distance  difference_type;
	 typedef Pointer   pointer;
	 typedef Reference reference;
	 typedef Category  iterator_category;
};

template <typename T>
class test
{

};

#endif
