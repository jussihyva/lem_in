/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 15:02:30 by ubuntu            #+#    #+#             */
/*   Updated: 2020/04/06 15:05:00 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		ft_lstsort(t_list **list, int cmp(t_list *elem1, t_list *elem2))
{
	t_list		*elem;
	int			is_sorted;

	is_sorted = 0;
	while (!is_sorted)
	{
		elem = *list;
		is_sorted = 1;
		while (elem)
		{
			if (elem->next && !cmp(elem, elem->next))
			{
				if (*list == elem)
					*list = elem->next;
				ft_lstswap(elem, elem->next);
				is_sorted = 0;
			}
			else
				elem = elem->next;
		}
	}
	return ;
}
