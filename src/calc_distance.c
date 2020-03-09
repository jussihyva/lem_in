/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_distance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 09:59:20 by jkauppi           #+#    #+#             */
/*   Updated: 2020/03/09 10:29:43 by jkauppi          ###   ########.fr       */
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

void						calc_distance(t_input *input)
{
	t_room		*room;
	size_t		connection_counter;

	room = *input->end_room_ptr;
	connection_counter = -1;
	validate_adj_rooms(&connection_counter, input, room);
	return ;
}
