/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transportation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 10:25:46 by jkauppi           #+#    #+#             */
/*   Updated: 2020/03/09 12:31:21 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				transportation(t_report *report)
{
	t_list		**elem;
	t_list		*path;
	t_room		*room;

	path = *(t_list **)report->lst_of_valid_paths;
	while (path)
	{
		elem  = path->content;
		ft_printf("Path : ");
		while (*elem)
		{
			room = *(t_room **)(*elem)->content;
			ft_printf("%10s", room->name);
			elem = &(*elem)->next;
		}
		ft_printf("\n");
		path  = path->next;
	}
	return ;
}
