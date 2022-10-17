/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:01:38 by ghanquer          #+#    #+#             */
/*   Updated: 2022/10/17 14:17:20 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"
#include <vector>
namespace ft
{
	template<class T, class Container = std::vector<T> >
		class stack
		{
			public:
				typedef Container container_type;
				typedef typename Container::value_type value_type;
				typedef typename Container::size_type size_type;
				typedef typename Container::reference reference;
				typedef typename Container::const_reference const_reference;
				explicit stack(const Container & cont = Container()): c(cont)
				{
				}
				stack(const stack & copy) 
				{
					*this = copy;
				}
				~stack(void)
				{
				}
				stack &	operator=(const stack & src)
				{
					if (this == &src)
						return (*this);
					Container tmp = Container(src.c);
					this->c = tmp;
					return (*this);
				}
				T &			top(void)
				{
					return (*(this->c.end() - 1));
				}
				const T &	top(void) const
				{
					return (*(this->c.end() - 1));
				}
				bool		empty(void) const
				{
					return (this->c.empty());
				}
				std::size_t		size(void) const
				{
					return (this->c.size());
				}
				void		push(const T & elem)
				{
					this->c.insert(this->c.begin(), elem);
				}
				void		pop(void)
				{
					this->c.erase(this->c.end() - 1);
				}
				bool friend operator==(const stack & lhs, const stack & rhs)
				{
					return (lhs.c == rhs.c);
				}
				bool friend operator!=(const stack & lhs, const stack & rhs)
				{
					return (lhs.c != rhs.c);
				}
				bool friend operator<(const stack & lhs, const stack & rhs)
				{
					return (lhs.c < rhs.c);
				}
				bool friend operator<=(const stack & lhs, const stack & rhs)
				{
					return (lhs.c <= rhs.c);
				}
				bool friend operator>(const stack & lhs, const stack & rhs)
				{
					return (lhs.c > rhs.c);
				}
				bool friend operator>=(const stack & lhs, const stack & rhs)
				{
					return (lhs.c >= rhs.c);
				}
			protected:
				Container	c;
		};
}

#endif
