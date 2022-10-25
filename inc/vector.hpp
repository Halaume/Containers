/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:08:10 by ghanquer          #+#    #+#             */
/*   Updated: 2022/10/25 12:03:45 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <stdexcept>
#include <cstddef>
#include "vector.hpp"
#include "iterator.hpp"

namespace ft
{
	template<class T, class Allocator = std::allocator<T> >
		class vector
		{
			public:
				typedef T value_type;
				typedef Allocator allocator_type;
				typedef std::size_t size_type;
				typedef std::ptrdiff_t difference_type;
				typedef T & reference;
				typedef const T & const_reference;
				typedef typename Allocator::pointer pointer;
				typedef const typename Allocator::pointer const_pointer;
				typedef Iterator<std::random_access_iterator_tag, T> iterator;
				typedef Iterator<std::random_access_iterator_tag, T> const_iterator;
				typedef Reverse_iterator< Iterator<std::random_access_iterator_tag, T> > reverse_iterator;
				typedef Reverse_iterator< Iterator<std::random_access_iterator_tag, T> > const_reverse_iterator;
				vector(void) {}
				explicit vector(const Allocator & alloc)
				{
					this->Allocator = alloc;
					this->_tab = new T;
					this->_size = 0;
				}
				explicit vector(std::size_t count, const T & value = T(), const Allocator & alloc = Allocator())
				{
					(void)value;
					(void)alloc;
					this->_size = count;
					this->_tab = new T;
				}
				template<class InputIt>
				vector(InputIt first, InputIt last, const Allocator & alloc = Allocator())
				{
					(void)first;
					(void)last;
					(void)alloc;
					//this->_size = my_dist(first, last);
					this->_tab = new T;
				}
				vector(const vector & copy)
				{
					*this = copy;
				}
				~vector(void) {}
				vector &	operator=(const vector & src)
				{
					if (this == &src)
						return (*this);
					if (this->tab)
						delete [] this->tab;
					T* tmp = new T;
					//tmp = src._tab; //C'est de la bite en bois
					this->_tab = tmp;
					this->_size = src.size;
				}
				void	assign(std::size_t count, const T & value);
				template<class InputIt>
				void	assign(InputIt first, InputIt last);
				allocator_type	get_allocator() const
				{
					return  (this->Allocator);
				}
				reference at(std::size_t pos)
				{
					if (pos < 0 || pos > this->_size)
						throw std::out_of_range("Invalid size");
					return (this->_tab[pos]);
				}
				const_reference at(std::size_t pos) const
				{
					if (pos < 0 || pos > this->_size)
						throw std::out_of_range("Invalid size");
					return (this->_tab[pos]);
				}
				reference operator[](size_type pos)
				{
					return (this->_tab[pos]);
				}
				const_reference operator[](size_type pos) const
				{
					return (this->_tab[pos]);
				}
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
					return (*this->end() - 1);
				}
				T*	data(void)
				{
					return (this->_tab);
				}
				const T*	data(void) const;
				iterator	begin(void) { return (this->_tab); }
				const_iterator	begin(void) const { iterator tmp = this->_tab; return (tmp); }
				iterator	end(void) { iterator tmp = this->_tab; tmp += this->_size; return (tmp); }
				const_iterator	end(void) const { iterator tmp = this->_tab; tmp += this->_size; return (tmp); }
				reverse_iterator	rbegin(void) { reverse_iterator tmp = this->end(); return (tmp); }
				const_reverse_iterator	rbegin(void) const { reverse_iterator tmp = this->end(); return (tmp); }
				reverse_iterator	rend(void) { reverse_iterator tmp = this->begin(); return (tmp); }
				const_reverse_iterator	rend(void) const { reverse_iterator tmp = this->begin(); return (tmp); }
				bool	empty(void) const
				{
					if (this->_size == 0)
						return (true);
					return (false);
				}
				size_type	size(void) const
				{
					return (this->_size);
				}
				size_type	max_size(void) const
				{
					return (Allocator::max_size());
				}
				void	reserve(size_type new_cap);
				size_type	capacity() const;
				void	clear(void)
				{
				//	iterator
				}
				iterator	insert(const_iterator pos, const T & value);
				iterator	insert(const_iterator pos, size_type count, const T & value);
				template<class InputIt>
				iterator	insert(const_iterator pos, InputIt first, InputIt last);
				iterator	erase(iterator pos)
				{
					T*	tmp = new T;
					size_type	i = 0;
					size_type	j = 0;
					delete this->_tab[pos];
					this->_tab[pos] = NULL;
					while (i < this->_size)
					{
						if (this->_tab[i] != NULL)
						{
							tmp[j] = this->_tab[i];
							j++;
						}
						i++;
					}
					this->_size--;
					delete this->_tab;
					this->_tab = tmp;
					return (this->tab[pos]);
				}
				iterator	erase(iterator first, iterator last);
				void	push_back(const T & value)
				{
					this->_tab[this->_size] = value;
					this->_size++;
				}
				void	pop_back(void)
				{
					this->_size--;
					delete this->_tab[this->_size];
				}
				void	resize(size_type count, T value = T());
				void	swap(vector & other);
			private:
				T*			_tab;
				size_type	_size;
		};
}

#endif
