/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:01:38 by ghanquer          #+#    #+#             */
/*   Updated: 2022/10/12 15:00:25 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"
#include <vector>
namespace ft
{
	template<class T, class Container = ft::vector<T> >
		class stack
		{
			public:
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
			protected:
				Container	c;
		};
}
#endif
