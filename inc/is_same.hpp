/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_same.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 10:59:08 by ghanquer          #+#    #+#             */
/*   Updated: 2022/11/24 11:14:12 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_SAME_HPP
#define IS_SAME_HPP

#include "integral_constant.hpp"

namespace ft
{
	template<class T, class U>
		struct is_same : ft::false_type {};

	template<class T>
		struct is_same<T, T> : ft::true_type {};
}

#endif
