/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 14:49:03 by ubuntu            #+#    #+#             */
/*   Updated: 2020/04/09 14:06:03 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_lstadd_sort(t_list **alst, t_list *new, int (*cmp)(t_list *elem1,
																t_list *elem2))
{
	t_list	*elem;

	if (*alst)
	{
		elem = *alst;
		while (elem)
		{
			if (cmp(new, elem) < 0)
			{
				ft_lstadd(&elem, new);
				break ;
			}
			if (!elem->next)
			{
				elem->next = new;
				new->prev = elem;
			}
			elem = elem->next;
		}
		elem->next = new;
		new->prev = elem;
	}
	else
		*alst = new;
	return ;
}
