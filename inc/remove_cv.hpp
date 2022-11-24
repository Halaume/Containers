/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_cv.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:00:52 by ghanquer          #+#    #+#             */
/*   Updated: 2022/11/24 11:15:23 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REMOVE_CV_HPP
#define REMOVE_CV_HPP

namespace ft
{
	template <class T>
		struct remove_cv{ typedef T type; };
	template <class T>
		struct remove_cv<T const>{ typedef T type;  };
	template <class T>
		struct remove_cv<T volatile>{ typedef T type; };
	template <class T>
		struct remove_cv<T const volatile>{ typedef T type; };
}

#endif
