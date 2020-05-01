/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_ford_fulkerson4.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 16:03:12 by ubuntu            #+#    #+#             */
/*   Updated: 2020/05/01 19:08:31 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		re_trace_path(t_room *current_room, t_room *start_room,
															t_room *end_room)
{
	t_list		*elem;
	int			return_code;
	t_room		*adj_room;
	t_room		*next_room;

	return_code = 0;
	if (current_room->re_routing)
		return (return_code);
	current_room->re_routing = 1;
	elem = current_room->connection_lst;
	while (elem && !return_code)
	{
		adj_room = *(t_room **)elem->content;
		if (adj_room->is_visited && adj_room->prev_room &&
					adj_room->prev_room != current_room &&
					adj_room->prev_room != start_room)
		{
			next_room = adj_room->prev_room;
			while (!return_code && next_room != start_room &&
														!next_room->re_routing)
			{
				ft_printf("%s: %10s(%s)\n", current_room->name, adj_room->name,
															next_room->name);
				return_code = trace_path(next_room, start_room, end_room);
				next_room = next_room->prev_room;
			}
		}
		elem = elem->next;
	}
	if (return_code)
	{
		ft_printf("RE-ROUTED PATH: %s\n", current_room->name);
		current_room->next_room = adj_room;
		adj_room->prev_room = current_room;
	}
	current_room->re_routing = 0;
	return (return_code);
}

int				trace_path(t_room *current_room, t_room *start_room,
															t_room *end_room)
{
	t_list		*elem;
	int			return_code;
	int			is_connection_to_valid_path;
	t_room		*adj_room;

	return_code = 0;
	is_connection_to_valid_path = 0;
	current_room->is_visited = 1;
	elem = current_room->connection_lst;
	while (elem && !return_code)
	{
		adj_room = *(t_room **)elem->content;
		if (adj_room == end_room)
			return_code = 1;
		else if (adj_room->is_visited && adj_room->prev_room &&
										adj_room->next_room != current_room &&
											adj_room->prev_room != current_room)
			is_connection_to_valid_path = 1;
		else if (!adj_room->is_visited && !is_connection_to_valid_path)
			return_code = trace_path(adj_room, start_room, end_room);
		elem = elem->next;
	}
	if (return_code)
	{
		current_room->next_room = adj_room;
		adj_room->prev_room = current_room;
	}
	else if (!current_room->next_room)
	{
		if (is_connection_to_valid_path)
			return_code = re_trace_path(current_room, start_room, end_room);
		if (!return_code)
			current_room->is_visited = 0;
	}
	return (return_code);
}

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
		return_code = trace_path(adj_room, output->start_room_ptr,
														output->end_room_ptr);
		ft_printf("\n");
		if (return_code)
			adj_room->prev_room = current_room;
		track_path(adj_room);
		ft_printf("\n");
		elem = elem->next;
	}
	ft_printf("\nSummary:\n");
	elem = current_room->connection_lst;
	while (elem)
	{
		adj_room = *(t_room **)elem->content;
		ft_printf("\n");
		track_path(adj_room);
		ft_printf("\n");
		elem = elem->next;
	}
	return_code = 0;
	return (return_code);
}
