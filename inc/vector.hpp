/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:08:10 by ghanquer          #+#    #+#             */
/*   Updated: 2022/11/16 16:11:28 by ghanquer         ###   ########.fr       */
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
				typedef ft::Iterator<std::random_access_iterator_tag, T> iterator;
				typedef ft::Iterator<std::random_access_iterator_tag, const T> const_iterator;
				typedef ft::Reverse_iterator<iterator> reverse_iterator;
				typedef ft::Reverse_iterator<const_iterator> const_reverse_iterator;

				vector(void)
				{
					this->_alloc = Allocator();
					this->_capacity = 0;
					this->_tab = this->_alloc.allocate(0);
					this->_size = 0;
				}

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
					this->_capacity = this->_size * 2;
					this->_tab = this->_alloc.allocate(this->capacity());
					while (i < this->_size)
					{
						this->_alloc.construct(&this->_tab[i], value);
						i++;
					}
				}
				// TODO This constructor
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
							this->_alloc.destruct(this->_tab[i]);
							this->_alloc.construct(&this->_tab[i], value);
						}
					}
					else
					{
						vector<T> vec(this->_alloc);

						vec._capacity = count;
						vec._size = count;
						vec._tab = vec._alloc.allocate(vec.capacity());
						for (size_type	i = 0; i < vec._capacity; i++)
						{
							if (i < this->_size)
							{
								vec._alloc.construct(&vec._tab[i], this->_tab[i]);
								this->_alloc.destruct(this->_tab[i]);
							}
							else
								vec._alloc.construct(&vec._tab[i], value);
						}
						this->_alloc.deallocate(this->_tab, this->capacity());
						*this = vec;
					}
				}

				template<class InputIt>
					void	assign(InputIt first, InputIt last)
					{
						if (this->_distit(first, last) <= this->capacity())
						{
							for (size_type i = 0; first != last; i++, first++)
							{
								this->_tab[i] = *first;
							}
						}
						else
						{
							this->clear();
							this->deallocate(this->begin(), this->end());
							this->_capacity = this->_distit(first, last);
							this->_size = this->capacity();
							this->_tab = this->allocate(this->capacity());
							for (size_type	i = 0; first != last; first++, i++)
								this._tab[i] = first;
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

				const T*	data(void) const
				{
					return (this->_tab);
				}

				iterator	begin(void) { iterator temp = this->_tab; return (temp); }

				const_iterator begin() const { const_iterator temp = this->_tab; return (temp); }

				iterator	end(void) { iterator tmp = this->_tab + this->size(); return (tmp); }

				const_iterator	end(void) const { const_iterator tmp = this->_tab + this->size(); return (tmp); }

				reverse_iterator	rbegin(void) { reverse_iterator tmp = this->end(); return (tmp); }

				const_reverse_iterator	rbegin(void) const { const_reverse_iterator tmp = this->end(); return (tmp); }

				reverse_iterator	rend(void) { reverse_iterator tmp = this->begin(); return (tmp); }

				const_reverse_iterator	rend(void) const { const_reverse_iterator tmp = this->begin(); return (tmp); }

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
					vector<T> vec(this->_alloc);

					vec._size = this->size();
					vec._capacity = new_cap;
					vec._tab = vec.alloc.allocate(vec.capacity());

					size_type i = 0;

					for (iterator it = this->begin(); it != this->end(); it++, i++)
					{
						vec[i] = *it;
						this->_alloc.destroy(it);
					}
					this->_alloc.deallocate(this->_tab, this->capacity());
					*this = vec;
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

				iterator	insert(const_iterator pos, const T & value);
				iterator	insert(const_iterator pos, size_type count, const T & value);
				template<class InputIt>
					iterator	insert(const_iterator pos, InputIt first, InputIt last);
				iterator	erase(iterator pos)
				{
					if (pos == this->end())
						return (this->end());
					iterator	ret;
					for (iterator pos2 = pos; pos2 != this->end() - 1 ; pos2++)
					{
						std::cout << *pos2 << std::endl;
						pos2 = pos2 + 1;
					}
					this->_alloc.destroy(this->_tab + this->size());
					this->_size--;
					return (ret);
				}

				iterator	erase(iterator first, iterator last)
				{
					if (!first || first == last)
						return (last);
					if (last == this->end())
					{
						for (iterator tmp = first; tmp != last; tmp++)
						{
							destroy(tmp);
							this->_size--;
						}
						return (this->_end());
					}
					else
					{
						for (iterator tmp = first; tmp != last; tmp++)
						{
							destroy(tmp);
							this->_size--;
						}
						size_type i = 0;
						for (iterator tmp = last; tmp != this->end(); tmp++, i++)
						{
							first + i = tmp;
						}
						return (first);
					}
				}
				void	push_back(const T & value)
				{
					if (this->size() == this->capacity())
					{
						size_type	i = 0;
						if (!this->_tab)
						{
							this->_capacity++;
							this->_tab = this->_alloc.allocate(this->capacity());
						}
						else
						{
							vector<T> newvec(this->size());
							while (i < this->size())
							{
								newvec._alloc.construct(&newvec._tab[i], this->_tab[i]);
								i++;
							}
							*this = newvec;
						}
					}
					this->_alloc.construct(&this->_tab[this->size()], value);
					this->_size++;
				}

				void	pop_back(void)
				{
					this->_alloc.destroy(this->_tab + this->size());
					this->_size--;
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
				typename vector<T, Alloc>::iterator it1 = lhs.begin();
				typename vector<T, Alloc>::iterator it2 = rhs.begin();

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
			return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) && lhs != rhs);
		}

	template< class T, class Alloc >
		bool operator<=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
		{
			return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) || lhs == rhs);
		}

	template< class T, class Alloc >
		bool operator>( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
		{
			return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) && lhs != rhs);
		}

	template< class T, class Alloc >
		bool operator>=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
		{
			return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) || lhs == rhs);
		}
}

#endif
