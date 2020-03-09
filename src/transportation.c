/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transportation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 10:25:46 by jkauppi           #+#    #+#             */
/*   Updated: 2020/03/09 10:37:23 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				transportation(t_report *report)
{
	t_list		*elem;
	t_room		*room;

	elem = *(t_list **)report->lst_of_valid_paths;
	while (elem)
	{
		room = (t_room *)elem->content;
		elem = elem->next;
	}
	return ;
}
