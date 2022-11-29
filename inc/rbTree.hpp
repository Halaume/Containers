/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:41:09 by ghanquer          #+#    #+#             */
/*   Updated: 2022/11/29 16:22:58 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
#define RBTREE_HPP

#define RED true
#define BLACK false

#include <cstddef>

namespace ft
{

	template <class T>
		class RbTree
		{
			public:
				struct node
				{
					node(void): color(BLACK), value()
					{
						parent = NULL;
						lchild = NULL;
						rchild = NULL;
					}
					node(const node & copy): parent(copy.parent), lchild(copy.lchild), rchild(copy.rchild), color(copy.color), value(copy.value)
					{
					}
					node(T value, node parent, bool get_color = BLACK)
					{
						lchild = NULL;
						rchild = NULL;
						color = get_color;
					}
					~node(void)
					{
					}
					node &	operator=(const node & src);
					node*	parent;
					node*	lchild;
					node*	rchild;
					bool	color;
					T		value;
				};
				node	start;
		};
}

#endif
