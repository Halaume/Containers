/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integral_constant.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:13:07 by ghanquer          #+#    #+#             */
/*   Updated: 2022/11/22 17:18:44 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace ft
{
	template <class T, T val>
		struct integral_constant
		{
			typedef T value_type;
			typedef integral_constant<T, val> type;
			static const T value = val;
			operator	T() const { return (value); }
		};

	template <bool val>
		struct integral_constant<bool, val>
		{
			typedef bool value_type;
			typedef integral_constant<bool, val> type;
			static const bool value = val;
			operator	bool() const { return (value); }
		};

	template <bool val>
		bool const integral_constant<bool, val>::value;
	template <class T, T val>
		T const integral_constant<T, val>::value;

	typedef integral_constant<bool, true> true_type;
	typedef integral_constant<bool, false> false_type;
}
