/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:08:10 by ghanquer          #+#    #+#             */
/*   Updated: 2022/10/12 15:05:10 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include "vector.hpp"

namespace ft
{
	template<class T, class Allocator = std::allocator<T> >
		class vector
		{
			public:
				typedef T value_type;
				typedef Allocator allocator_type;
				typedef std::size_t size_type;
//				typedef std::ptrdiff_t difference_type;
				typedef T & reference;
				typedef const T & const_reference;
				typedef typename Allocator::pointer pointer;
				typedef const typename Allocator::pointer const_pointer;
//				typedef iterator iterator;
//				typedef const iterator const_iterator;
//				typedef reverse_iterator reverse_iterator;
//				typedef const reverse_iterator const_reverse_iterator;
				vector(void);
				explicit vector(const Allocator & alloc);
				explicit vector(std::size_t count, const T & value = T(), const Allocator & alloc = Allocator());
				template<class InputIt>
				vector(InputIt first, InputIt last, const Allocator & alloc = Allocator());
				vector(const vector & other);
				~vector(void);
				vector &	operator=(const vector & src);
				void	assign(std::size_t count, const T & value);
				template<class InputIt>
				void	assign(InputIt first, InputIt last);



		};
}

#endif
