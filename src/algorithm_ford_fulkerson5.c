/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_ford_fulkerson5.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 18:21:34 by ubuntu            #+#    #+#             */
/*   Updated: 2020/04/13 19:07:27 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		trace_path_1(t_room *current_roon, t_room *start_room_ptr,
														t_room *end_room_ptr)
{
	int		trace_result;

	if (current_roon == end_room_ptr)
		trace_result = 1;
	else if (current_roon == start_room_ptr)
		trace_result = 0;
	else
		trace_result = 0;
	return (trace_result);
}

int				algorithm_ford_fulkerson5(t_output *output)
{
	t_room		*current_roon;
	t_room		*adj_room;
	t_list		*elem;
	int			trace_result;

	output->lst_of_selectd_paths =
				(t_list **)ft_memalloc(sizeof(*output->lst_of_selectd_paths));
	current_roon = output->start_room_ptr;
	trace_result = 0;
	elem = current_roon->connection_lst;
	while (elem && !trace_result)
	{
		adj_room = *(t_room **)elem->content;
		ft_printf("Room: %s (%d)\n", adj_room->name,
												adj_room->num_of_conn_to_end);
		trace_result = trace_path_1(adj_room, output->start_room_ptr,
														output->end_room_ptr);
		elem = elem->next;
	}
	return (0);
}
