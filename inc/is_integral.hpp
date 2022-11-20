/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:12:55 by ghanquer          #+#    #+#             */
/*   Updated: 2022/11/20 14:06:19 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "integral_constant.hpp"

namespace ft
{

	template<typename> struct is_integral_base: ft::integral_constant<typename>::false_type {};

	template <class T>
		struct remove_cv{ typedef T type; };
	template <class T>
		struct remove_cv<T const>{ typedef T type;  };
	template <class T>
		struct remove_cv<T volatile>{ typedef T type; };
	template <class T>
		struct remove_cv<T const volatile>{ typedef T type; };

	template<>
		struct is_integral_base<bool>: integral_constant<bool, true>::true_type {};
	template<>
		struct is_integral_base<int>: integral_constant::true_type {};
	template<>
		struct is_integral_base<short>: integral_constant::true_type {};
	template<>
		struct is_integral_base<long>: integral_constant::true_type {};
	template<>
		struct is_integral_base<unsigned int>: integral_constant::true_type {};
	template<>
		struct is_integral_base<unsigned short>: integral_constant::true_type {};
	template<>
		struct is_integral_base<unsigned long>: integral_constant::true_type {};
	template<>
		struct is_integral_base<char>: integral_constant::true_type {};
	template<>
		struct is_integral_base<unsigned char>: integral_constant<true>::true_type {};

	template<class T>
		struct	is_integral : is_integral_base<remove_cv<T> > {};
}
