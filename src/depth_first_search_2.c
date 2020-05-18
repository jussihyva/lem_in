/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   depth_first_search_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 06:48:18 by ubuntu            #+#    #+#             */
/*   Updated: 2020/05/18 07:21:07 by ubuntu           ###   ########.fr       */
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
	ft_lstadd_e(output->lst_of_valid_paths, ft_lstnew(&path, sizeof(path)));
	return ;
}

static void		dfs_2(t_room *current_room, t_room *start_room)
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
			dfs_2(adj_room, start_room);
		}
		elem = elem->next;
	}
	return ;
}

void			depth_first_search_2(t_output *output)
{
	t_room		*current_room;
	size_t		i;

	current_room = output->start_room_ptr;
	dfs_2(current_room, output->start_room_ptr);
	i = -1;
	while (++i < output->num_of_rooms)
	{
		current_room = output->room_array[i];
		if (current_room != output->start_room_ptr && !current_room->parent_room)
			dfs_2(current_room, output->start_room_ptr);
	}
	save_path_2(output, output->end_room_ptr);
	return ;
}
