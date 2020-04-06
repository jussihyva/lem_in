/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 14:49:03 by ubuntu            #+#    #+#             */
/*   Updated: 2020/04/06 14:59:34 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		ft_lstadd_sort(t_list **alst, t_list *new, void (*cmp)(void *, void *))
{
	t_list		*elem;

	if (*alst)
	{
		elem = *alst;
		while (elem->next)
		{
			elem = elem->next;
		}
		elem->
	}
	else
		*alst = new;
	return ;
}
