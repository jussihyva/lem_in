/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_ford_fulkerson5.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 18:21:34 by ubuntu            #+#    #+#             */
/*   Updated: 2020/04/22 14:10:59 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

// static t_list			**track_path(t_list **path, t_room *current_room,
// 														t_room *end_room_ptr)
// {
// 	ft_printf("%7s(%d)", current_room->name, current_room->num_of_conn_to_end);
// 	if (current_room->next_room)
// 	{
// 		if (current_room->next_room != end_room_ptr)
// 			track_path(path, current_room->next_room, end_room_ptr);
// 		ft_lstadd(path, ft_lstnew(&current_room->next_room,
// 											sizeof(current_room->next_room)));
// 	}
// 	return (path);
// }

static t_valid_path		*create_path(t_list **room_lst, t_validity validity)
{
	t_valid_path	*valid_path;
	t_list			*path_elem;
	t_list			*room_elem;

	valid_path = (t_valid_path *)ft_memalloc(sizeof(*valid_path));
	valid_path->room_lst =
						(t_list **)ft_memalloc(sizeof(*valid_path->room_lst));
	room_elem = *room_lst;
	while (room_elem)
	{
		ft_lstadd(valid_path->room_lst, ft_lstnew(room_elem->content,
													room_elem->content_size));
		room_elem = room_elem->next;
	}
//	valid_path->room_lst = room_lst;
	valid_path->validity = validity;
	valid_path->num_of_conn_to_end = -1;
	path_elem = *valid_path->room_lst;
	while (path_elem)
	{
		valid_path->num_of_conn_to_end++;
		path_elem = path_elem->next;
	}
	return (valid_path);
}

static int				trace_path_1(t_output *output, t_list **path_lst,
												t_room *current_roon, size_t c)
{
	int				trace_result;
	t_room			*adj_room;
	t_list			*elem;
	t_list			*current_elem;
	t_valid_path	*path;

	current_elem = ft_lstnew(&current_roon, sizeof(current_roon));
	ft_lstadd(path_lst, current_elem);
	adj_room = output->end_room_ptr;
	if (current_roon == output->end_room_ptr)
	{
		path = create_path(path_lst, valid_room);
		ft_lstadd(output->lst_of_selectd_paths, ft_lstnew(&path,
														sizeof(path)));
		free(path);
		output->number_of_paths++;
		trace_result = 1;
	}
	else if (current_roon == output->start_room_ptr)
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
				trace_result = trace_path_1(output, path_lst, adj_room, c + 1);
			else if (adj_room->next_room)
			{
				if (elem->next)
				{
					adj_room = *(t_room **)elem->content;
//					if (*(t_room **)elem->content)
				}
				else
					ft_printf("Colission: %s (%d)\n", adj_room->name, c);
			}
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
	ft_lstrem(path_lst, current_elem);
	return (trace_result);
}

int						algorithm_ford_fulkerson5(t_output *output)
{
	t_room				*current_roon;
	t_room				*adj_room;
	t_list				*elem;
	int					trace_result;
//	t_valid_path		*valid_path;
	t_list				**path;

	output->lst_of_selectd_paths =
				(t_list **)ft_memalloc(sizeof(*output->lst_of_selectd_paths));
	current_roon = output->start_room_ptr;
	current_roon->is_visited = 1;
	trace_result = 0;
	path = (t_list **)ft_memalloc(sizeof(*path));
	ft_lstadd(path, ft_lstnew(&current_roon, sizeof(current_roon)));
	elem = current_roon->connection_lst;
	while (elem)
	{
		adj_room = *(t_room **)elem->content;
		trace_result = trace_path_1(output, path, adj_room, 1);
		elem = elem->next;
	}
	ft_lstdel(path, del_path);
	free(path);
	// if (trace_result)
	// {
	// 	ft_printf("\n");
	// 	path = (t_list **)ft_memalloc(sizeof(*path));
	// 	track_path(path, adj_room, output->end_room_ptr);
	// 	if (*path)
	// 	{
	// 		output->number_of_paths++;
	// 		valid_path = create_valid_path(path, valid);
	// 		ft_lstadd(output->lst_of_selectd_paths, ft_lstnew(&valid_path,
	// 												sizeof(valid_path)));
	// 	}
	// 	ft_printf("\n");
	// }
	trace_result = put_ants_to_paths(output);
	ft_lstdel(output->lst_of_selectd_paths, del_output);
	return (0);
}
