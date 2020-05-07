/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 10:20:28 by ubuntu            #+#    #+#             */
/*   Updated: 2020/05/07 17:06:27 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			ft_lstrem(t_list **lst, t_list *elem)
{
	t_list			*tmp_elem;

	tmp_elem = elem->next;
	elem->prev ? elem->prev->next = elem->next : 0;
	elem->next ? elem->next->prev = elem->prev : 0;
	if (!elem->prev)
		*lst = tmp_elem;
	free(elem->content);
	free(elem);
	return ;
}
