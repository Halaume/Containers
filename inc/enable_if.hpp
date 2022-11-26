/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:13:02 by ghanquer          #+#    #+#             */
/*   Updated: 2022/11/26 11:47:08 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef ENABLE_IF_HPP
#define ENABLE_IF_HPP

namespace ft
{
	template<bool type, class T = void>
		struct enable_if
		{
		};
	template <class T>
		struct enable_if<true, T>
		{
			typedef T type;
		};
}

#endif
