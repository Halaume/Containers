/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:49:07 by ghanquer          #+#    #+#             */
/*   Updated: 2022/11/15 11:40:59 by ghanquer         ###   ########.fr       */
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
			pair(void): first(first_type()), second(second_type())
			{
			}
			pair(const T1 & x, const T2 & y): first(first_type(x)), second(second_type(y))
			{
			}
			template<class U1, class U2>
				pair(const pair<U1, U2> & p): first(p.first), second(p.second)
				{
				}
			pair(const pair & p) = default;
			pair &	operator=(const pair & other);
			bool operator==(const pair<T1,T2>& other );
			bool operator!=( const pair<T1,T2>& other );
			bool operator<( const pair<T1,T2>& other );
			bool operator<=( const pair<T1,T2>& other );
			bool operator>( const pair<T1,T2>& other );
			bool operator>=( const pair<T1,T2>& other );
			first_type	first;
			second_type	second;
		};

	template<class T1, class T2>
		pair<T1, T2> make_pair(T1 t, T2 u)
		{
			pair<T1, T2>	ret(t, u);
			return (ret);
		}
}

#endif
