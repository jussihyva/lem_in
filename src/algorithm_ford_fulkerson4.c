/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_ford_fulkerson4.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 16:03:12 by ubuntu            #+#    #+#             */
/*   Updated: 2020/04/09 13:41:02 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		trace_path(t_room *current_room, t_room *end_room)
{
	t_list		*elem;
	int			return_code;
	t_room		*adj_room;

	return_code = 0;
	current_room->is_visited = 1;
	elem = current_room->connection_lst;
	while (elem && !return_code)
	{
		adj_room = *(t_room **)elem->content;
		if (adj_room == end_room)
			return_code = 1;
		else if (!adj_room->is_visited)
			return_code = trace_path(adj_room, end_room);
		elem = elem->next;
	}
	if (return_code)
		current_room->next_room = adj_room;
	// else
	// 	ft_printf("No path: %10s\n", current_room->name);
	return (return_code);
}

static void		track_path(t_room *current_room)
{
	ft_printf("%5s", current_room->name);
	if (current_room->next_room)
		track_path(current_room->next_room);
	return ;
}

int				algorithm_ford_fulkerson4(t_output *output)
{
	t_list		*elem;
	int			return_code;
	t_room		*current_room;
	t_room		*adj_room;

	return_code = 1;
	output->lst_of_selectd_paths =
				(t_list **)ft_memalloc(sizeof(*output->lst_of_selectd_paths));
	current_room = output->start_room_ptr;
	current_room->is_visited = 1;
	elem = current_room->connection_lst;
	while (elem)
	{
		adj_room = *(t_room **)elem->content;
		return_code = trace_path(adj_room, output->end_room_ptr);
		if (return_code)
		{
			ft_printf("\n");
			track_path(adj_room);
			ft_printf("\n");
		}
		elem = elem->next;
	}
	return_code = 0;
	return (return_code);
}
