/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   depth_first_search_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 06:48:18 by ubuntu            #+#    #+#             */
/*   Updated: 2020/05/29 14:48:43 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		save_path_2(t_output *output, t_room *room)
{
	t_room			*parent_room;
	t_valid_path	*path;
	size_t			branch_id;

	branch_id = 0;
	path = initialize_path(output, valid_room, branch_id);
	ft_lstadd(path->room_lst, ft_lstnew(&room, sizeof(room)));
	room->num_of_conn_to_end = path->num_of_conn_to_end;
	parent_room = room->parent_room;
	while (parent_room->parent_room)
	{
		path->room_vector[parent_room->id / VECTOR_BITS] |= 1 <<
												(parent_room->id % VECTOR_BITS);
		ft_lstadd(path->room_lst, ft_lstnew(&parent_room, sizeof(parent_room)));
		path->num_of_conn_to_end++;
		parent_room->num_of_conn_to_end = path->num_of_conn_to_end;
		parent_room = parent_room->parent_room;
	}
	ft_lstadd(path->room_lst, ft_lstnew(&output->start_room_ptr,
											sizeof(output->start_room_ptr)));
	path->num_of_conn_to_end++;
	ft_printf("connections: %d\n", path->num_of_conn_to_end);
	ft_lstadd_e(output->lst_of_valid_paths, ft_lstnew(&path, sizeof(path)));
	return ;
}

static void		dfs_2(t_output *output, t_room *current_room,
										t_room *start_room, t_room *end_room)
{
	t_room		*adj_room;
	t_list		*elem;

	elem = current_room->connection_lst;
	while (elem)
	{
		adj_room = *(t_room **)elem->content;
		if (adj_room != start_room && !adj_room->parent_room)
		{
			adj_room->parent_room = current_room;
			if (adj_room == end_room)
				save_path_2(output, end_room);
			else
				dfs_2(output, adj_room, start_room, end_room);
			adj_room->parent_room = NULL;
		}
		elem = elem->next;
	}
	return ;
}

void			depth_first_search_2(t_output *output)
{
	t_room		*current_room;

	current_room = output->start_room_ptr;
	dfs_2(output, current_room, output->start_room_ptr, output->end_room_ptr);
	return ;
}
