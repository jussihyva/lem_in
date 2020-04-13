/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_ford_fulkerson5.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 18:21:34 by ubuntu            #+#    #+#             */
/*   Updated: 2020/04/13 23:43:29 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		track_path(t_room *current_room)
{
	ft_printf("%7s(%d)", current_room->name, current_room->num_of_conn_to_end);
	if (current_room->next_room)
	{
		if (current_room != ((t_room *)current_room->next_room)->next_room)
			track_path(current_room->next_room);
	}
	return ;
}

static int		trace_path_1(t_room *current_roon, t_room *start_room_ptr,
														t_room *end_room_ptr)
{
	int			trace_result;
	t_room		*adj_room;
	t_list		*elem;

	adj_room = end_room_ptr;
	if (current_roon == end_room_ptr)
		trace_result = 1;
	else if (current_roon == start_room_ptr)
		trace_result = 0;
	else
	{
		current_roon->is_visited = 1;
		trace_result = 0;
		elem = current_roon->connection_lst;
		while (elem && !trace_result)
		{
			adj_room = *(t_room **)elem->content;
			if (!adj_room->is_visited && !current_roon->is_blocked)
				trace_result = trace_path_1(adj_room, start_room_ptr,
																end_room_ptr);
			else if (adj_room->next_room)
				ft_printf("Colission: %s\n", adj_room->name);
			elem = elem->next;
		}
		if (!trace_result)
			current_roon->is_visited = 0;
		else
			current_roon->is_visited = 1;
	}
	if (trace_result)
		current_roon->next_room = adj_room;
		// ft_printf("Room: %s (%d)\n", current_roon->name,
		// 									current_roon->num_of_conn_to_end);
	else
		current_roon->is_blocked = 1;
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
	current_roon->is_visited = 1;
	trace_result = 0;
	elem = current_roon->connection_lst;
	while (elem)
	{
		adj_room = *(t_room **)elem->content;
		trace_result = trace_path_1(adj_room, output->start_room_ptr,
														output->end_room_ptr);
		if (trace_result)
		{
			ft_printf("\n");
			track_path(adj_room);
			ft_printf("\n");
		}
		elem = elem->next;
	}
	return (0);
}
