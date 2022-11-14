/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integral_constant.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:13:07 by ghanquer          #+#    #+#             */
/*   Updated: 2022/11/12 14:33:42 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace ft
{
	template<class T, T var>
		struct integral_constant
		{
			static const T	value = var;
			typedef T	value_type;
			typedef integral_constant<T, var>	type;
			//	T	operator () { return (var); }
		};

	template<bool, bool var>
		struct integral_constant
		{
			typedef integral_constant<bool, true>	true_type;
			typedef integral_constant<bool, false>	false_type;
			static const bool	value = var;
			//	T	operator () { return (var); }
		};
}
