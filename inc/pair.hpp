/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:49:07 by ghanquer          #+#    #+#             */
/*   Updated: 2022/11/14 12:57:04 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft
{
	template<class T1, class T2>
		struct pair
		{
			typedef T1 first_type;
			typedef T2 second_type;
			pair(void);
			pair(const T1 & x, const T2 & y);
			template<class U1, class U2>
				pair(const pair<U1, U2> & p);
			pair(const pair & p) = default;
			pair &	operator=(const pair & other);
			private:
				first_type	first;
				second_type	second;
		};
}

#endif
