/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_ford_fulkerson5.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 18:21:34 by ubuntu            #+#    #+#             */
/*   Updated: 2020/04/14 10:25:55 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_list			**track_path(t_list **path, t_room *current_room,
														t_room *end_room_ptr)
{
	ft_printf("%7s(%d)", current_room->name, current_room->num_of_conn_to_end);
	if (current_room->next_room)
	{
		if (current_room->next_room != end_room_ptr)
			track_path(path, current_room->next_room, end_room_ptr);
		ft_lstadd(path, ft_lstnew(&current_room->next_room,
											sizeof(current_room->next_room)));
	}
	return (path);
}

static int				trace_path_1(t_room *current_roon, t_room *start_room_ptr,
														t_room *end_room_ptr, size_t c)
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
																end_room_ptr, c + 1);
			else if (adj_room->next_room)
				ft_printf("Colission: %s (%d)\n", adj_room->name, c);
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

int						algorithm_ford_fulkerson5(t_output *output)
{
	t_room				*current_roon;
	t_room				*adj_room;
	t_list				*elem;
	int					trace_result;
	t_valid_path		*valid_path;
	t_list				**path;

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
														output->end_room_ptr, 1);
		if (trace_result)
		{
			ft_printf("\n");
			path = (t_list **)ft_memalloc(sizeof(*path));
			track_path(path, adj_room, output->end_room_ptr);
			if (*path)
			{
				ft_lstadd(path, ft_lstnew(&adj_room,
											sizeof(adj_room)));
				ft_lstadd(path, ft_lstnew(&current_roon,
											sizeof(current_roon)));
				output->number_of_paths++;
				valid_path = create_valid_path(path, valid);
				ft_lstadd(output->lst_of_selectd_paths, ft_lstnew(&valid_path,
														sizeof(valid_path)));
			}
			ft_printf("\n");
		}
		elem = elem->next;
	}
	trace_result = put_ants_to_paths(output);
	return (1);
}
