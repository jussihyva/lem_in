/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_ford_fulkerson5.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/12 18:21:34 by ubuntu            #+#    #+#             */
/*   Updated: 2020/05/04 09:40:03 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void				print_valid_paths(t_output *output)
{
	t_valid_path	*path;
	t_list			*room_elem;
	size_t			c;
	size_t			i;
	t_room			*room;

	c = 0;
	ft_printf("\n");
	while (c < output->number_of_paths)
	{
		path = (t_valid_path *)output->valid_paths[c];
		ft_printf("%3d %3d", c, path->num_of_conn_to_end);
		room_elem = *path->room_lst;
		i = 25;
		while (room_elem && i--)
		{
			room = *(t_room **)room_elem->content;
			ft_printf(" %s", room->name);
			room_elem = room_elem->next;
		}
		ft_printf("\n");
		c++;
	}
	return ;
}

static int				create_path(t_output *output, t_list **room_lst,
										t_validity validity, t_room *start_room)
{
	t_valid_path	*path;
	t_list			*room_elem;
	t_room			*room;

	path = initialize_path(output, validity);
	path->num_of_conn_to_end = -1;
	room_elem = *room_lst;
	while (room_elem)
	{
		room = *(t_room **)room_elem->content;
		if (room != start_room && room != output->end_room_ptr)
			path->room_vector[room->id / 32] |= 1 << (room->id % 32);
		ft_lstadd(path->room_lst, ft_lstnew(room_elem->content,
													room_elem->content_size));
		path->num_of_conn_to_end++;
		room_elem = room_elem->next;
	}
	ft_lstadd_e(output->lst_of_valid_paths, ft_lstnew(&path, sizeof(path)));
	output->number_of_paths++;
	return (1);
}

static int				validate_adj_room(t_output *output, t_room *prev_room,
										t_room *current_room, t_list **path_lst)
{
	int				trace_result;
	t_list			*elem;
	t_room			*adj_room;
	size_t			c;

	trace_result = 0;
	elem = current_room->connection_lst;
	while (elem)
	{
		adj_room = *(t_room **)elem->content;
		if (adj_room == output->start_room_ptr)
			trace_result |= 1;
		else if (!adj_room->is_blocked && !adj_room->is_visited &&
														adj_room != prev_room)
			trace_result |= trace_path_1(output, path_lst, adj_room,
															current_room);
		if (!prev_room)
		{
			c = -1;
			while (++c < output->num_of_rooms)
				output->room_array[c]->is_blocked = 0;
		}
		elem = elem->next;
	}
	return (trace_result);
}

int						trace_path_1(t_output *output, t_list **path_lst,
										t_room *current_room, t_room *prev_room)
{
	int				trace_result;
	t_list			*current_elem;

	current_room->is_visited = 1;
	current_elem = ft_lstnew(&current_room, sizeof(current_room));
	ft_lstadd(path_lst, current_elem);
	if (current_room == output->end_room_ptr)
		trace_result = create_path(output, path_lst, valid_room,
														output->start_room_ptr);
	else
		trace_result = validate_adj_room(output, prev_room, current_room,
																	path_lst);
	if (trace_result == 0)
		current_room->is_blocked = 1;
	ft_lstrem(path_lst, current_elem);
	current_room->is_visited = 0;
	return (trace_result);
}

int						algorithm_ford_fulkerson5(t_output *output)
{
	t_list				**path;
	t_list				*new_path_lst;
	size_t				*merged_room_vector;

	merged_room_vector = (size_t *)ft_memalloc(sizeof(*merged_room_vector) *
											((output->num_of_rooms / 32) + 1));
	output->lst_of_selectd_paths =
				(t_list **)ft_memalloc(sizeof(*output->lst_of_selectd_paths));
	path = (t_list **)ft_memalloc(sizeof(*path));
	trace_path_1(output, path, output->start_room_ptr, NULL);
	ft_lstdel(path, del_path);
	free(path);
	output->number_of_paths = ft_lstlen(output->lst_of_valid_paths);
	output->valid_paths =
					(t_valid_path **)ft_memalloc(sizeof(*output->valid_paths) *
													output->number_of_paths);
	sort_valid_paths(output->lst_of_valid_paths, output->valid_paths);
	if (output->opt && output->opt & verbose1)
		print_valid_paths(output);
	new_path_lst = NULL;
	select_best_group(&new_path_lst, merged_room_vector, output, 0);
	ft_lstdel(&new_path_lst, del_path);
	output->number_of_paths = ft_lstlen(output->lst_of_selectd_paths);
	put_ants_to_paths(output);
	return (1);
}
