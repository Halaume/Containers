/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:08:10 by ghanquer          #+#    #+#             */
/*   Updated: 2022/10/26 16:55:11 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <stdexcept>
#include <cstddef>
#include <iterator>
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
				typedef Iterator<std::random_access_iterator_tag, const T> const_iterator;
				typedef Reverse_iterator< Iterator<std::random_access_iterator_tag, T> > reverse_iterator;
				typedef Reverse_iterator< Iterator<std::random_access_iterator_tag, const T> > const_reverse_iterator;

				vector(void) {}

				explicit vector(const Allocator & alloc)
				{
					this->_alloc = alloc;
					this->_tab = this->_alloc.allocate(0);
					this->_size = 0;
					this->_capacity = 0;
				}

				explicit vector(std::size_t count, const T & value = T(), const Allocator & alloc = Allocator())
				{
					size_type	i = 0;
					this->_alloc = alloc;
					this->_size = count;
					this->_tab = this->_alloc.allocate(this->_size);
					this->_capacity = this->_size;
					while (i < this->_size)
					{
						this->_alloc.construct(this->_tab[i], value);
						i++;
					}
				}

				template<class InputIt>
				vector(InputIt first, InputIt last, const Allocator & alloc = Allocator())
				{
					this->_alloc = alloc;
					//this->_size = my_dist(first, last);
					this->_tab = this->_alloc.allocate(last - first);
					this->_capacity = last - first;
				}

				vector(const vector & copy): _alloc(copy._alloc), _tab(copy._tab), _size(copy._size), _capacity(copy._capacity)
				{
				}

				~vector(void) 
				{
					this->clear();
					if (this->_capacity)
						this->_alloc.deallocate(this->_tab, this->_capacity);
				}

				vector &	operator=(const vector & src)
				{
					if (this == &src)
						return (*this);
					if (this->tab)
					{
						this->clear();
						if (this->_capacity)
							this->_alloc.deallocate(this->_tab, this->_capacity);
					}
					this->_alloc = src._alloc;
					this->_tab = this->_alloc.allocate(src._size);
					this->_size = src._size;
					this->_end = src.end;
					this->_capacity = src.capacity;
					iterator it = src.begin();
					iterator it2 = src.end();
					while (it != it2)
					{
						this->_tab + it = src.tab + it;
						it++;
					}
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
				iterator	begin(void) { iterator temp = this->_tab; return (temp); }


				iterator	end(void) { iterator tmp = this->_tab[this->_size]; return (tmp); }

				const_iterator	end(void) const { const_iterator tmp = this->_tab[this->_size]; return (tmp); }

				reverse_iterator	rbegin(void) { reverse_iterator tmp = this->end(); return (tmp); }

				const_reverse_iterator	rbegin(void) const { const_reverse_iterator tmp = this->end(); return (tmp); }

				reverse_iterator	rend(void) { reverse_iterator tmp = this->begin(); return (tmp); }

				const_reverse_iterator	rend(void) const { const_reverse_iterator tmp = this->begin(); return (tmp); }

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

				size_type	capacity() const
				{
					return (this->_capacity);
				}

				void	clear(void)
				{
					size_type	i = 0;
					if (!this->_size)
						return ;
					while (i < this->_size)
					{
						this->_alloc.destroy(this->_tab + i);
						i++;
					}
					this->_size = 0;
				}

				iterator	insert(const_iterator pos, const T & value);
				iterator	insert(const_iterator pos, size_type count, const T & value);
				template<class InputIt>
				iterator	insert(const_iterator pos, InputIt first, InputIt last);
				iterator	erase(iterator pos);
				/*{
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
				}*/

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
				size_type	_capacity;
				T*			_tab;
				Allocator	_alloc;
				size_type	_size;
		};
}

#endif
