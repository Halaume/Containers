/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConstClass.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdetune <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 20:17:43 by bdetune           #+#    #+#             */
/*   Updated: 2022/12/07 15:45:08 by bdetune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTCLASS_HPP
# define CONSTCLASS_HPP
# include <iostream>

class ConstClass
{
	public:
		ConstClass(int nb): _val(nb) {}
		ConstClass(void): _val() {}
		ConstClass(ConstClass const & src): _val(src._val){}
		~ConstClass(void){}

		ConstClass & operator=(ConstClass const & rhs){(void)rhs;return(*this);}
		bool operator==(ConstClass const & rhs) const {return (this->_val == rhs._val);}

		int	getValue(void) const {return (_val);}
	
	private:
		const int	_val;
};


bool operator==(ConstClass const & lhs, ConstClass const & rhs)
{
	return (lhs.getValue() == rhs.getValue());
}

std::ostream &	operator<<(std::ostream & stream, ConstClass const & toprint)
{
	stream << toprint.getValue();
	return (stream);
}

#endif
