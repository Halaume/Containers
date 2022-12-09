/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:08:10 by ghanquer          #+#    #+#             */
/*   Updated: 2022/12/09 17:30:44 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <stdexcept>
#include <cstddef>
#include <iterator>
#include "iterator.hpp"
#include "reverse_iterator.hpp"
#include <iostream>
#include "lexicographical_compare.hpp"
#include "enable_if.hpp"
#include "is_integral.hpp"
#include "is_same.hpp"

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
				typedef typename Allocator::const_pointer		const_pointer;
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
					if (count > this->max_size())
						throw (std::length_error("ft::vector"));
					this->_size = count;
					this->_capacity = this->size();
					if (count == 0)
						this->_tab = NULL;
					else
						this->_tab = this->_alloc.allocate(this->capacity());
					while (i < this->_size)
					{
						this->_alloc.construct(this->_tab + i, value);
						i++;
					}
				}
				template<class InputIt>
					vector(InputIt first, InputIt last, const Allocator & alloc = Allocator(), typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL)
					{
						this->_alloc = alloc;
						difference_type	dist = this->_distit(first, last);
						if (dist != - 1)
						{
							if (static_cast<size_type>(this->_distit(first,last)) > this->max_size())
								throw (std::length_error("ft::vector"));
							this->_size = static_cast<size_type>(dist);
							this->_tab = this->_alloc.allocate(this->size());
							this->_capacity = this->size();
							for (size_type i = 0; i < this->size(); i++, first++)
								this->_alloc.construct(this->_tab + i, *first);
						}
						else
						{
							this->_size = 0;
							this->_capacity = 0;
							for (;first != last; first++)
								this->push_back(*first);
						}
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
						if (this->capacity() != 0)
							this->_alloc.deallocate(this->_tab, this->capacity());
					}
					this->_alloc = src._alloc;
					if (src.capacity() == 0)
						this->_tab = NULL;
					else
						this->_tab = this->_alloc.allocate(src.capacity());
					this->_size = src._size;
					this->_capacity = src._capacity;
					for (size_type	i = 0; i < this->size(); i++)
						this->_alloc.construct(this->_tab + i, *(src._tab + i));
					return (*this);
				}

				void	assign(size_type count, const T & value)
				{
					if (count > this->max_size())
						throw (std::length_error("ft::vector"));
					if (count <= this->capacity())
					{
						this->clear();
						for (size_type	i = 0; i < count; i++)
							this->push_back(value);
					}
					else
					{
						pointer	tab;
						if (count == 0)
							tab = NULL;
						else
							tab = this->_alloc.allocate(count);
						for (size_type	i = 0; i < count; i++)
							this->_alloc.construct(tab + i, value);
						this->clear();
						if (this->capacity() != 0)
							this->_alloc.deallocate(this->_tab, this->capacity());
						this->_tab = tab;
						this->_size = count;
						this->_capacity = count;
					}
				}

				template<class InputIt>
					void	assign(InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL)
					{
						difference_type dist = this->_distit(first, last);
						if (dist != -1 && static_cast<size_type>(this->_distit(first, last)) <= this->capacity())
						{
							if (static_cast<size_type>(dist) > this->max_size())
								throw (std::length_error("ft::vector"));
							this->clear();
							for (size_type i = 0; first != last; i++, first++)
								this->push_back(*first);
						}
						else if (dist != -1)
						{
							if (static_cast<size_type>(dist) > this->max_size())
								throw (std::length_error("ft::vector"));
							pointer	tab;
							if (dist == 0)
								tab = NULL;
							else
								tab = this->_alloc.allocate(dist);
							for (difference_type	i = 0; i < dist; i++, first++)
								this->_alloc.construct(tab + i, *first);
							this->clear();
							if (this->capacity() != 0)
								this->_alloc.deallocate(this->_tab, this->capacity());
							this->_tab = tab;
							this->_size = dist;
							this->_capacity = dist;
						}
						else
						{
							this->clear();
							while (first != last)
							{
								this->push_back(*first);
								first++;
							}
						}
					}

				allocator_type	get_allocator() const
				{
					return  (this->_alloc);
				}

				reference at(std::size_t pos)
				{
					if (pos < 0 || pos >= this->_size)
						throw std::out_of_range("ft::vector");
					return (this->_tab[pos]);
				}

				const_reference at(std::size_t pos) const
				{
					if (pos < 0 || pos >= this->_size)
						throw std::out_of_range("ft::vector");
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
					if (new_cap > this->max_size())
						throw (std::length_error("ft::vector"));
					if (new_cap <= this->capacity())
						return ;
					pointer newvec = this->_alloc.allocate(new_cap);
					for (size_type i = 0; i < new_cap && i < this->size(); i++)
						this->_alloc.construct(newvec + i, this->_tab[i]);
					size_type tmp = this->size();
					this->clear();
					if (this->capacity() != 0)
						this->_alloc.deallocate(this->_tab, this->_capacity);
					this->_size = tmp;
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
					if (!this->size())
						return ;
					while (i < this->size())
					{
						this->_alloc.destroy(this->_tab + i);
						i++;
					}
					this->_size = 0;
				}

				iterator	insert(const_iterator pos, const T & value)
				{
					iterator it;
					if (this->size() + 1 > this->max_size())
						throw (std::length_error("ft::vector"));
					if (!this->capacity())
					{
						this->push_back(value);
						return (this->begin());
					}
					if (this->size() + 1 > this->capacity())
					{
						it = this->begin();
						pointer	tab;
						tab = this->_alloc.allocate(this->capacity() * 2);
						size_type i;
						for (i = 0;it != pos; it++, i++)
							this->_alloc.construct(tab + i, *(it));
						this->_alloc.construct(tab + i, value);
						iterator	ret = iterator(tab + i);
						for (i = i + 1;it != this->end(); it++, i++)
							this->_alloc.construct(tab + i, *(it));
						size_type tmp = this->size();
						this->clear();
						this->_alloc.deallocate(this->_tab, this->capacity());
						this->_capacity *= 2;
						this->_size = tmp + 1;
						this->_tab = tab;
						return (ret);
					}
					else
					{
						it = this->end();
						if (it != pos)
						{
							this->_alloc.construct(&(*it), *(it - 1));
							it--;
						}
						for (;it != pos; it--)
						{
							this->_alloc.destroy(&(*it));
							this->_alloc.construct(&(*it), *(it - 1));
						}
						if (it != this->end())
							this->_alloc.destroy(&(*it));
						this->_alloc.construct(&(*it), value);
					}
					this->_size++;
					return (it);
				}
				iterator	insert(iterator pos, size_type count, const T & value)
				{
					if (count == 0)
						return (pos);
					if (this->size() + count > this->max_size())
						throw (std::length_error("ft::vector"));
					if (!this->size())
					{
						assign(count, value);
						return (this->begin());
					}
					difference_type	start = this->_distit(this->begin(), pos);
					if (start != -1 && this->size() + count > this->capacity())
					{
						size_type capacity = this->capacity() * 2 >= this->size() + count ? this->capacity() * 2 : this->size() + count;
						if (capacity > this->max_size())
							throw (std::length_error("ft::vector"));
						pointer tab;
						tab = this->_alloc.allocate(capacity);
						difference_type j = 0;
						while (j < start)
						{
							this->_alloc.construct(tab + j, *(this->begin() + j));
							j++;
						}
						for (size_type i = 0; i < count; i++)
							this->_alloc.construct(tab + start + i, value);
						iterator it = pos;
						j = start + count;
						size_type i = 0;
						while (it != this->end())
						{
							this->_alloc.construct(tab + j, this->_tab[start + i]);
							it++;
							i++;
							j++;
						}
						size_type tmp = this->size();
						this->clear();
						this->_alloc.deallocate(this->_tab, this->capacity());
						this->_size = tmp + count;
						this->_capacity = capacity;
						this->_tab = tab;
					}
					else
					{
						while (count != 0)
						{
							this->insert(pos, value);
							count--;
						}
					}
					return (pos + 1);
				}
				template<class InputIt>
					iterator	insert(iterator pos, InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL)
					{
						if (first == last)
							return (pos);
						iterator it = this->begin();
						difference_type size = this->_distit(first, last);
						difference_type dist_pos = this->_distit(this->begin(), pos);
						if (size != -1 && this->size() + size > this->max_size())
							throw (std::length_error("ft::vector"));
						if (!this->capacity())
						{
							assign(first, last);
							return (this->begin());
						}
						if (size != -1 && dist_pos != -1 && this->size() + size > this->capacity())
						{
							size_type capacity = this->capacity() * 2 >= this->size() + size ? this->capacity() * 2 : this->size() + size;
							if (capacity > this->max_size())
								throw (std::length_error("ft::vector"));
							pointer tab;
							tab = this->_alloc.allocate(capacity);
							difference_type j = 0;
							while (j < dist_pos)
							{
								this->_alloc.construct(tab + j, *(this->begin() + j));
								j++;
							}
							for (size_type i = 0; first != last; first++, i++)
								this->_alloc.construct(tab + dist_pos + i, *first);
							it = pos;
							j = dist_pos + size;
							size_type i = 0;
							while (it != this->end())
							{
								this->_alloc.construct(tab + j, this->_tab[dist_pos + i]);
								it++;
								i++;
								j++;
							}
							size_type	tmp = this->size();
							this->clear();
							this->_alloc.deallocate(this->_tab, this->capacity());
							this->_size = tmp + size;
							this->_capacity = capacity;
							this->_tab = tab;
						}
						else
						{
							pointer	tab;
							size_type	istart = 0;
							it = this->begin();
							while (it != pos)
							{
								it++;
								istart++;
							}
							tab = this->_alloc.allocate(this->size() - istart);
							size_type	i = 0;
							while (it != this->end())
							{
								this->_alloc.construct(tab + i, *(this->_tab + istart));
								i++;
								istart++;
								it++;
							}
							if (pos != this->end())
							{
								while (pos + 1 != this->end())
								{
									this->pop_back();
								}
							}
							while (first != last)
							{
								this->push_back(*first);
								first++;
							}
							size_type	j = 0;
							while (j != i)
							{
								this->push_back(tab[j]);
								this->_alloc.destroy(tab + j);
								j++;
							}
							this->_alloc.deallocate(tab, i);
						}
						return (pos + 1);
					}
				iterator	erase(iterator pos)
				{
					this->_alloc.destroy(&(*pos));
					for (iterator start = pos; (start + 1) != this->end(); start++)
					{
						this->_alloc.construct(&(*start), *(start + 1));
						this->_alloc.destroy(&(*(start + 1)));
					}

					this->_size--;
					return (pos);
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
				}
				void	push_back(const T & value)
				{
					if (this->size() + 1 > this->max_size())
						throw (std::length_error("ft::vector"));
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
						if (this->capacity() != 0)
							this->_alloc.deallocate(this->_tab, this->capacity());
						this->_capacity *= 2;
						this->_tab = tab;
					}
					this->_alloc.construct(this->_tab + this->size(), value);
					this->_size++;
				}

				void	pop_back(void)
				{
					if (this->size())
					{
						this->_alloc.destroy(&this->_tab[this->size()] - 1);
						this->_size--;
					}
				}

				void	resize(size_type count, T value = T())
				{
					if (this->_size > count)
					{
						while (this->size() != count)
							this->pop_back();
					}
					else
					{
						if (count > this->max_size())
							throw (std::length_error("ft::vector"));
						while (this->_size != count)
							this->push_back(value);
					}
				}
				void	swap(vector & other)
				{
					Allocator	alloc = this->_alloc;
					pointer		tab = this->_tab;
					size_type	size = this->_size;
					size_type	capacity = this->_capacity;

					this->_alloc = other._alloc;
					this->_tab = other._tab;
					this->_size = other._size;
					this->_capacity = other._capacity;
					other._alloc = alloc;
					other._tab = tab;
					other._size = size;
					other._capacity = capacity;
				}
			private:
				Allocator	_alloc;
				pointer		_tab;
				size_type	_size;
				size_type	_capacity;
			/*	template<class InputIt>
					difference_type	_distit(InputIt first, InputIt last)
					{
						if (ft::is_same<typename iterator_traits<InputIt>::iterator_category, std::input_iterator_tag>::value)
							return (-1);
						difference_type	i = 0;
						for (InputIt	tmp = first; tmp != last; tmp++, i++);
						return (i);
					}*/
				template<class It>
					difference_type	_distit(It  first, It  last, typename ft::enable_if<ft::is_same<typename iterator_traits<It>::iterator_category, std::input_iterator_tag>::value, It>::type* = NULL)
					{
						(void)first;
						(void)last;
						return (-1);
					}

				template<class It>
					difference_type	_distit(It  first, It  last, typename ft::enable_if<ft::is_same<typename iterator_traits<It>::iterator_category, std::output_iterator_tag>::value, It>::type* = NULL)
					{
						(void)first;
						(void)last;
						return (-1);
					}

				template<class It>
					difference_type	_distit(It  first, It  last, typename ft::enable_if<ft::is_same<typename iterator_traits<It>::iterator_category, std::forward_iterator_tag>::value, It>::type* = NULL)
					{
						difference_type	i = 0;
						for (It	tmp = first; tmp != last; tmp++, i++);
						return (i);
					}

				template<class It>
					difference_type	_distit(It  first, It  last, typename ft::enable_if<ft::is_same<typename iterator_traits<It>::iterator_category, std::bidirectional_iterator_tag>::value, It>::type* = NULL)
					{
						difference_type	i = 0;
						for (It	tmp = first; tmp != last; tmp++, i++);
						return (i);
					}

				template<class It>
					difference_type	_distit(It  first, It  last, typename ft::enable_if<ft::is_same<typename iterator_traits<It>::iterator_category, std::random_access_iterator_tag>::value, It>::type* = NULL)
					{
						return (last - first);
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
				return (true);
			}
			return (false);
		}

	template<class T, class Alloc>
		void	swap(ft::vector<T, Alloc>&lhs, ft::vector<T, Alloc>& rhs)
		{
			lhs.swap(rhs);
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
