/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:12:55 by ghanquer          #+#    #+#             */
/*   Updated: 2022/11/12 14:32:10 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "integral_constant.hpp"

namespace ft
{

	template<typename> struct is_integral_base: ft::integral_constant<typename>::false_type {};

	template<>
		struct is_integral_base<bool> integral_constant::true_type {};
	template<>
		struct is_integral_base<int> integral_constant::true_type {};
	template<>
		struct is_integral_base<short> integral_constant::true_type {};
	template<>
		struct is_integral_base<long> integral_constant::true_type {};
	template<>
		struct is_integral_base<unsigned int> integral_constant::true_type {};
	template<>
		struct is_integral_base<unsigned short> integral_constant::true_type {};
	template<>
		struct is_integral_base<unsigned long> integral_constant::true_type {};
	template<>
		struct is_integral_base<char> integral_constant::true_type {};
	template<>
		struct is_integral_base<unsigned char> integral_constant<>::true_type {};

	template<class T>
		struct	is_integral : integral_constant<bool, is_integral(T)>{};
}
