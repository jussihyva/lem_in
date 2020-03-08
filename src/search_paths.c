/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 10:46:53 by jkauppi           #+#    #+#             */
/*   Updated: 2020/03/08 11:43:06 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			navigate_shortest_path(t_input *input, t_report *report)
{
	t_room		*start_room;
	t_room		*next_room;
	t_room		*best_room;
	t_list		*adj_room_elem;
	int			end_room_reached;

	start_room = *input->start_room_ptr;
	ft_lstadd(report->path, ft_lstnew(&start_room, sizeof(start_room)));
	ft_printf("%10s", start_room->name);
	adj_room_elem = start_room->connection_lst;
	end_room_reached = 0;
	while (!end_room_reached)
	{
		best_room = NULL;
		while (adj_room_elem)
		{
			next_room = *(t_room **)adj_room_elem->content;
			if (best_room)
			{
				if (next_room->num_of_conn_to_end <
												best_room->num_of_conn_to_end)
					best_room = next_room;
			}
			else
				best_room = next_room;
			adj_room_elem = adj_room_elem->next;
		}
		ft_lstadd(report->path, ft_lstnew(&best_room, sizeof(best_room)));
		ft_printf(" %10s", best_room->name);
		if (best_room == *input->end_room_ptr)
			end_room_reached = 1;
		else
			adj_room_elem = best_room->connection_lst;
	}
	ft_printf("\n");
	return ;
}