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
				vector(void) {}
				explicit vector(const Allocator & alloc);
				explicit vector(std::size_t count, const T & value = T(), const Allocator & alloc = Allocator());
				template<class InputIt>
				vector(InputIt first, InputIt last, const Allocator & alloc = Allocator());
				vector(const vector & other);
				~vector(void) {}
				vector &	operator=(const vector & src);
				void	assign(std::size_t count, const T & value);
				template<class InputIt>
				void	assign(InputIt first, InputIt last);
				allocator_type	get_allocator() const
				{
					return  (this->Allocator);
				}
				reference at(std::size_t pos);
				const_reference at(std::size_t pos) const;
				reference operator[](size_type pos);
				const_reference operator[](size_type pos) const;
				reference	front(void)
				{
					return (*this->begin());
				}
				const_reference	front(void) const
				{
					return (*this->begin());
				}
				reference	back(void)
				{
					return (*this->end() - 1);
				}
				const_reference	back(void) const
				{
					return (*this->end - 1);
				}
				T*	data(void);
				const T*	data(void) const;
//				iterator	begin(void);
//				const_iterator	begin(void) const;
//				iterator	end(void);
//				const_iterator	end(void) const;
//				reverse_iterator	rbegin(void);
//				const_reverse_iterator	rbegin(void) const;
//				reverse_iterator	rend(void);
//				const_reverse_iterator	rend(void) const;
				bool	empty(void) const;
				size_type	size(void) const;
				size_type	max_size(void) const;
				void	reserve(size_type new_cap);
				size_type	capacity() const;
				void	clear(void);
//				iterator	insert(const_iterator pos, const T & value);
//				iterator	insert(const_iterator pos, size_type count, const T & value);
//				iterator	insert(const_iterator pos, size_type count, const T & value);
//				template<class InputIt>
//				iterator	insert(const_iterator pos, InputIt first, InputIt last);
//				iterator	erase(iterator pos);
//				iterator	erase(iterator first, iterator last);
				void	push_back(const T & value);
				void	pop_back(void);
				void	resize(size_type count, T value = T());
				void	swap(vector & other);

		};
}

#endif
