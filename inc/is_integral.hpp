/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:12:55 by ghanquer          #+#    #+#             */
/*   Updated: 2022/11/24 11:02:32 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_INTEGRAL_HPP
#define IS_INTEGRAL_HPP

#include "integral_constant.hpp"
#include "remove_cv.hpp"

namespace ft
{

	template<typename>
		struct is_integral_base: ft::false_type {};

	template<>
		struct is_integral_base<bool>: ft::true_type {};
	template<>
		struct is_integral_base<char>: ft::true_type {};
//	template<>
//		struct is_integral_base<char16_t>: ft::true_type {};
//	template<>
//		struct is_integral_base<char32_t>: ft::true_type {};
	template<>
		struct is_integral_base<wchar_t>: ft::true_type {};
	template<>
		struct is_integral_base<unsigned char>: ft::true_type {};
	template<>
		struct is_integral_base<signed char>: ft::true_type {};
	template<>
		struct is_integral_base<short>: ft::true_type {};
	template<>
		struct is_integral_base<int>: ft::true_type {};
	template<>
		struct is_integral_base<long>: ft::true_type {};
	template<>
		struct is_integral_base<unsigned short>: ft::true_type {};
	template<>
		struct is_integral_base<unsigned int>: ft::true_type {};
	template<>
		struct is_integral_base<unsigned long>: ft::true_type {};

	template<class T>
		struct	is_integral : is_integral_base<typename remove_cv<T>::type > {};
}

#endif
