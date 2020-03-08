/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_distance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 09:59:20 by jkauppi           #+#    #+#             */
/*   Updated: 2020/03/08 10:22:15 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void						validate_adj_rooms(size_t *connection_counter,
												t_input *input, t_room *room)
{
	t_room			*next_room;
	t_list			*adj_room_elem;

	(*connection_counter)++;
	room->num_of_conn_to_end = *connection_counter;
	adj_room_elem = room->connection_lst;
	while (adj_room_elem)
	{
		next_room = *(t_room **)adj_room_elem->content;
		if (next_room != *input->end_room_ptr)
		{
			if (!next_room->num_of_conn_to_end ||
				next_room->num_of_conn_to_end > (*connection_counter + 1))
				validate_adj_rooms(connection_counter, input, next_room);
		}
		adj_room_elem = adj_room_elem->next;
	}
	(*connection_counter)--;
	return ;
}

t_report					*calc_distance(t_input *input)
{
	t_report		*report;
	t_room			*room;

	report = (t_report *)ft_memalloc(sizeof(*report));
	report->error = 0;
	report->opt = input->opt;
	report->path = (t_list **)ft_memalloc(sizeof(*(report->path)));
	report->lst_of_valid_paths =
				(t_list **)ft_memalloc(sizeof(*(report->lst_of_valid_paths)));
	room = *input->end_room_ptr;
	*(report->path) = ft_lstnew(&room, sizeof(room));
	report->visited_room = (size_t *)ft_memalloc(sizeof(*report->visited_room) *
										((input->num_of_rooms - 1) / 32 + 1));
	report->visited_room[room->id / 32] |= 1 << (room->id % 32);
	report->connection_counter = -1;
	validate_adj_rooms(&report->connection_counter, input, room);
	ft_lstdel(report->path, del_path_2);
	free(report->path);
	report->path = NULL;
	free(report->visited_room);
	report->visited_room = NULL;
	return (report);
}
