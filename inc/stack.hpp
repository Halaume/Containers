/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:01:38 by ghanquer          #+#    #+#             */
/*   Updated: 2022/10/12 10:10:43 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

template<class T, class Container = Vector<T>>
class Stack
{
	public:
//		Stack(void);
		explicit Stack(const Container & cont = Container());
		Stack(const Stack & copy) 
		{
			*this = copy;
		}
		~Stack(void)
		{
			~this->_cont();
		}
		Stack &	operator=(const Stack & src)
		{
			if (this = *src)
				return (*this);
			if (this->_cont)
				delete this->_cont;
			Container tmp = new Container(src.cont);
			this->_cont = tmp;
			return (*this);

		}
		T &			top(void)
		{
			return (this->_cont.end());
		}
		const T &	top(void) const
		{
			return (this->_cont.end());
		}
		bool		empty(void) const
		{
			return (this->_cont.empty());
		}
		size_t		size(void) const
		{
			return (this->_cont.size());
		}
		void		push(const T &);
		void		pop(void);
	private:
		Container	_cont;
};

#endif
