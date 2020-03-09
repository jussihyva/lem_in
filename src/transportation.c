/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transportation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 10:25:46 by jkauppi           #+#    #+#             */
/*   Updated: 2020/03/09 16:38:33 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				transportation(t_report *report)
{
	t_list			*elem;
	t_list			*valid_path_elem;
	t_valid_path	*valid_path;
	t_room			*room;

	valid_path_elem = *report->lst_of_valid_paths;
	while (valid_path_elem)
	{
		valid_path = *(t_valid_path **)valid_path_elem->content;
		ft_printf("Path : ");
		elem = *valid_path->path;
		while (elem)
		{
			room = *(t_room **)elem->content;
			ft_printf("%10s", room->name);
			elem = elem->next;
		}
		ft_printf("\n");
		valid_path_elem = valid_path_elem->next;
	}
	return ;
}
