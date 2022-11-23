/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:08:10 by ghanquer          #+#    #+#             */
/*   Updated: 2022/11/23 15:34:24 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <stdexcept>
#include <cstddef>
#include <iterator>
#include "iterator.hpp"
#include <iostream>
#include "lexicographical_compare.hpp"
#include "enable_if.hpp"
#include "is_integral.hpp"

namespace ft
{
	template<class T, class Allocator = std::allocator<T> >
		class vector
		{
			public:
				typedef T										value_type;
				typedef Allocator								allocator_type;
				typedef std::size_t								size_type;
				typedef std::ptrdiff_t							difference_type;
				typedef typename Allocator::reference			reference;
				typedef typename Allocator::const_reference		const_reference;
				typedef typename Allocator::pointer				pointer;
				typedef const typename Allocator::pointer		const_pointer;
				typedef ft::Iterator<T>							iterator;
				typedef ft::Iterator<const T>					const_iterator;
				typedef ft::Reverse_iterator<iterator>			reverse_iterator;
				typedef ft::Reverse_iterator<const_iterator>	const_reverse_iterator;

				vector(void)
				{
					this->_alloc = Allocator();
					this->_capacity = 0;
					this->_tab = NULL;
					this->_size = 0;
				}

				explicit vector(const Allocator & alloc)
				{
					this->_alloc = alloc;
					this->_tab = NULL;
					this->_size = 0;
					this->_capacity = 0;
				}

				explicit vector(std::size_t count, const T & value = T(), const Allocator & alloc = Allocator())
				{
					size_type	i = 0;
					this->_alloc = alloc;
					this->_size = count;
					this->_capacity = this->_size;
					this->_tab = this->_alloc.allocate(this->capacity());
					while (i < this->_size)
					{
						this->_alloc.construct(this->_tab + i, value);
						i++;
					}
				}
				template<class InputIt>
					//TODO Fix this operator
					vector(InputIt first, InputIt last, const Allocator & alloc = Allocator(), typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL)
					{
						std::cout << "AAAAH " << ft::is_integral<InputIt>::value << std::endl;
						this->_alloc = alloc;
						this->_size = this->_distit(first, last);	//C'est de la merde a changer
						this->_tab = this->_alloc.allocate(this->size());
						this->_capacity = this->size();
						for (size_type i = 0; i < this->size(); i++, first++)
							this->_alloc.construct(this->_tab + i, *first);
					}

				vector(const vector & copy): _alloc(copy._alloc), _size(copy._size), _capacity(copy._capacity)
				{
					if (copy.capacity() == 0)
						this->_tab = NULL;
					else
					{
						this->_tab = this->_alloc.allocate(this->capacity());
						for (size_type i = 0; i < copy.size(); i++)
							this->_alloc.construct(this->_tab + i, copy._tab[i]);
					}
				}

				~vector(void) 
				{
					this->clear();
					if (this->_capacity)
					{
						this->_alloc.deallocate(this->_tab, this->capacity());
					}
				}
				vector &	operator=(const vector & src)
				{
					if (this == &src)
						return (*this);
					if (this->_tab)
					{
						this->clear();
						if (this->_capacity)
							this->_alloc.deallocate(this->_tab, this->capacity());
					}
					this->_alloc = src._alloc;
					this->_tab = this->_alloc.allocate(src.capacity());
					this->_size = src._size;
					this->_capacity = src._capacity;
					for (size_type	i = 0; i < this->size(); i++)
						this->_tab[i] = src._tab[i];
					return (*this);
				}

				void	assign(std::size_t count, const T & value)
				{
					if (count <= this->_size)
					{
						for (size_type	i = 0; i < this->_size; i++)
						{
							this->_alloc.destroy(this->_tab + i);
							this->_alloc.construct(&this->_tab[i], value);
						}
					}
					else
					{
						vector<T> vec(this->_alloc);

						vec._capacity = count;
						vec._size = count;
						vec._tab = vec._alloc.allocate(vec.capacity());
						for (size_type	i = 0; i < vec.capacity(); i++)
						{
							if (i < this->_size)
							{
								vec._alloc.construct(&vec._tab[i], this->_tab[i]);
								this->_alloc.destroy(this->_tab + i);
							}
							else
								vec._alloc.construct(&vec._tab[i], value);
						}
						this->_alloc.deallocate(this->_tab, this->capacity());
						*this = vec;
					}
				}

				template<class InputIt>
					void	assign(InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL)
					{
						if (this->_distit(first, last) <= this->capacity())
						{
							for (size_type i = 0; first != last; i++, first++)
								this->_tab[i] = *first;
						}
						else
						{
							this->clear();
							this->_alloc.deallocate(this->_tab, this->size());
							this->_capacity = this->_distit(first, last);
							this->_size = this->capacity();
							this->_tab = this->_alloc.allocate(this->capacity());
							for (size_type	i = 0; first != last; first++, i++)
								this->_tab[i] = *first;
						}
					}

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
					if (this->size() > 0)
						return (*(this->end() - 1));
					return (*(this->_tab));
				}

				const_reference	back(void) const
				{
					if (this->size() > 0)
						return (*(this->end() - 1));
					return (*(this->_tab));
				}

				T*	data(void)
				{
					return (this->_tab);
				}

				const T*	data(void) const
				{
					return (this->_tab);
				}

				iterator	begin(void)
				{
					return (iterator(this->_tab));
				}

				const_iterator begin() const
				{
					return (const_iterator(this->_tab));
				}

				iterator	end(void)
				{
					return (iterator(this->_tab + this->size()));
				}

				const_iterator	end(void) const
				{
					return (const_iterator(this->_tab + this->size()));
				}

				reverse_iterator	rbegin(void)
				{
					return (reverse_iterator(this->end()));
				}

				const_reverse_iterator	rbegin(void) const
				{
					return (const_reverse_iterator(this->end()));
				}

				reverse_iterator	rend(void)
				{
					return (reverse_iterator(this->begin()));
				}

				const_reverse_iterator	rend(void) const
				{
					return (const_reverse_iterator(this->begin()));
				}

				bool	empty(void) const
				{
					if (this->size() == 0)
						return (true);
					return (false);
				}

				size_type	size(void) const
				{
					return (this->_size);
				}

				size_type	max_size(void) const
				{
					return (this->_alloc.max_size());
				}

				void	reserve(size_type new_cap)
				{
					if (new_cap <= this->capacity())
						return ;
					pointer newvec = this->_alloc.allocate(new_cap);
					for (size_type i = 0; i < new_cap && i < this->size(); i++)
						newvec[i] = this->_tab[i];
					this->_alloc.deallocate(this->_tab, this->_capacity);
					this->_tab = newvec;
					this->_capacity = new_cap;
				}

				size_type	capacity(void) const
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

				iterator	insert(const_iterator pos, const T & value)
				{
					iterator it = this->end();
					if (this->size() + 1 > this->capacity())
					{
						pointer	tab;
						this->_alloc.allocate(tab, this->capacity() * 2);
						this->_capacity *= 2;
						for (;it != pos; it--)
						{
							if (it != this->end())
								this->_alloc.destroy(*it);
							this->_alloc.construct(*it, *it - 1);
						}
						this->_alloc.destroy(*it);
						this->_alloc.construct(*it, value);
						this->_alloc.deallocate(this->_tab, this->size());
						this->_size++;
						this->_tab = tab;
					}
					else
					{
						for (;it != pos; it--)
						{
							this->_alloc.destroy(*it);
							this->_alloc.construct(*it, *it - 1);
						}
						this->_alloc.destroy(*it);
						this->_alloc.construct(*it, value);

					/*	pointer	tab;
						size_type size_tab = this->_distit(pos, this->end());
						tab = this->_alloc.allocate(size_tab);
						size_type i = 0;
						for (iterator it = pos; it != this->end(); it++, i++)
							tab[i] = *it;
						*pos = value;
						i = this->_distit(this->begin(), pos);
						for (size_type it = 0; it != size_tab; it++, i++)
							this->_tab[i] = tab[it];
						this->_alloc.deallocate(tab, size_tab);*/
					}
				}
				//TODO Here
				iterator	insert(const_iterator pos, size_type count, const T & value);
				template<class InputIt>
					iterator	insert(const_iterator pos, InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL);
				iterator	erase(iterator pos)
				{
					iterator	ret;
					pointer	tab;
					size_type j = 0;

					tab = this->_alloc.allocate(this->size());
					for (size_type i = 0; i < this->size(); i++)
						tab[i] = this->_tab[i];
					iterator it = this->begin();
					while (it != pos)
					{
						j++;
						it++;
					}
					this->_alloc.destroy(this->_tab + j);
					for (size_type i = j + 1; i != this->size(); i++)
						this->_tab[i - 1] = tab[i];
					this->_alloc.deallocate(tab, this->_size);

					this->_size--;
					return (ret);
				}
				iterator	erase(iterator first, iterator last)
				{
					if (first == last)
						return (last);

					size_type i = 0;

					for (;this->_tab + i != &(*first);i++);
					for (;last != this->end(); i++, last++)
					{
						this->_alloc.destroy(this->_tab + i);
						this->_alloc.construct(this->_tab + i, *last);
					}
					size_type newsize = i;
					for (;i < this->size(); i++)
						this->_alloc.destroy(this->_tab + i);
					this->_size = newsize;
					return (first);
					/*
					if (first == last)
						return (last);
					size_type j = 0;
					iterator it = this->begin();
					while (it != first)
					{
						j++;
						it++;
					}
					if (last == this->end())
					{
						for (iterator tmp = first; tmp != last; tmp++)
						{
							this->_alloc.destroy(this->_tab + j);
							this->_size--;
						}
						return (this->end());
					}
					else
					{
						size_type i = j;
						for (; first != last; first++, j++)
						{
							this->_alloc.destroy(this->_tab + j);
							this->_size--;
						}
						while (i != j)
						{
							this->_tab[i] = this->_tab[j];
							i++;
						}
						return (first);
					}*/
				}
				void	push_back(const T & value)
				{
					if (this->size() + 1 > this->max_size())
						throw (std::length_error("Max size exceeded"));
					if (this->capacity() == 0)
					{
						this->_capacity = 1;
						this->_tab = this->_alloc.allocate(this->capacity());
					}
					else if (this->size() == this->capacity())
					{
						pointer tab;
						tab = this->_alloc.allocate(this->capacity() * 2);
						for (size_type i = 0; i < this->size(); i++)
						{
							this->_alloc.construct(tab + i, this->_tab[i]);
							this->_alloc.destroy(this->_tab + i);
						}
						this->_alloc.deallocate(this->_tab, this->capacity());
						this->_capacity *= 2;
						this->_tab = tab;
					}
					this->_alloc.construct(&this->_tab[this->size()], value);
					this->_size++;
				}

				void	pop_back(void)
				{
					if (this->size())
					{
						this->_alloc.destroy(&this->_tab[this->size()]);
						this->_size--;
					}
				}

				void	resize(size_type count, T value = T())
				{
					if (this->_size > count)
					{
						while (this->_size != count)
							this->pop_back();
					}
					else
					{
						while (this->_size != count)
							this->push_back(value);
					}
				}
				void	swap(vector & other)
				{
					vector<T> tmp;

					tmp = other;
					other = *this;
					*this = tmp;
				}
			private:
				Allocator	_alloc;
				T*			_tab;
				size_type	_size;
				size_type	_capacity;
				//TODO spec for any iterator type, impossible with inputit
				template<class InputIt>
					size_type	_distit(InputIt first, InputIt last)
					{
						size_type	i = 0;
						for (InputIt	tmp = first; tmp != last; tmp++, i++);
						return (i);
					}
		};

	template< class T, class Alloc >
		bool operator==( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
		{
			if (lhs.size() == rhs.size())
			{
				typename vector<T, Alloc>::const_iterator it1;
				it1 = lhs.begin();
				typename vector<T, Alloc>::const_iterator it2;
				it2 = rhs.begin();

				for (;it1 != lhs.end() && it2 != lhs.end(); it1++, it2++)
				{
					if (*it1 != *it2)
						return (false);
				}
				
			}
			return (true);
		}

	template< class T, class Alloc >
		bool operator!=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs ) { return (!(lhs == rhs)); }

	template< class T, class Alloc >
		bool operator<( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
		{
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) && lhs != rhs);
		}

	template< class T, class Alloc >
		bool operator<=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
		{
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) || lhs == rhs);
		}

	template< class T, class Alloc >
		bool operator>( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
		{
			return (!(ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())) && lhs != rhs);
		}

	template< class T, class Alloc >
		bool operator>=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
		{
			return (!(ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())) || lhs == rhs);
		}
}

#endif
