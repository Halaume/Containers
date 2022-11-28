/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:41:09 by ghanquer          #+#    #+#             */
/*   Updated: 2022/11/28 15:00:09 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
#define RBTREE_HPP

#define RED true
#define BLACK false

namespace ft
{

	template <class T>
		class RbTree
		{
			public:
				struct node
				{
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
