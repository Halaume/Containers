/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <ghanquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:23:53 by ghanquer          #+#    #+#             */
/*   Updated: 2022/11/20 10:56:28 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/stack.hpp"
#include "../inc/vector.hpp"

#include <vector>
#include <iostream>
#include <stack>

#ifndef NAMESPACE
#define NAMESPACE ft
#endif

void	do_stack(void);
void	do_vector(void);

int main(void)
{
	do_stack();
	do_vector();

	return (0);
}
