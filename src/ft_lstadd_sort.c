/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 14:49:03 by ubuntu            #+#    #+#             */
/*   Updated: 2020/04/09 19:50:00 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		add_elem_into_lst(t_list **alst, t_list *new, t_list *elem)
{
	new->next = elem;
	new->prev = elem->prev;
	if (elem->prev)
		elem->prev->next = new;
	else
		*alst = new;
	elem->prev = new;
	return ;
}

void			ft_lstadd_sort(t_list **alst, t_list *new,
									int (*cmp)(t_list *elem1, t_list *elem2))
{
	t_list	*elem;

	if (*alst)
	{
		elem = *alst;
		while (elem)
		{
			if (cmp(new, elem) < 0)
			{
				add_elem_into_lst(alst, new, elem);
				break ;
			}
			if (!elem->next)
			{
				new->next = elem->next;
				elem->next = new;
				new->prev = elem;
				break ;
			}
			elem = elem->next;
		}
	}
	else
		*alst = new;
	return ;
}
