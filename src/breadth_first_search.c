/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   breadth_first_search.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 14:45:49 by ubuntu            #+#    #+#             */
/*   Updated: 2020/06/25 01:19:31 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void					reset_level_counter(t_output *output)
{
	t_room		*room;
	size_t		i;
	size_t		level;

	i = -1;
	while (++i < output->num_of_rooms)
	{
		room = output->room_array[i];
		room->num_of_conn_to_start = -1;
	}
	room = output->start_room_ptr;
	level = 0;
	room->num_of_conn_to_start = level;
	return ;
}

static void					collect_adj_rooms(t_output *output,
									t_list **new_room_elem_lst, t_room *room,
														t_bfs_data *bfs_data)
{
	t_room			*adj_room;
	t_list			*adj_elem;

	adj_elem = room->connection_lst;
	while (adj_elem)
	{
		adj_room = *(t_room **)adj_elem->content;
		if (adj_room == output->end_room_ptr)
		{
			adj_room->parent_room = room;
			save_path(output, bfs_data->branch_id);
		}
		else if (adj_room->num_of_conn_to_start == -1)
		{
			adj_room->num_of_conn_to_start = bfs_data->level;
			adj_room->parent_room = room;
			ft_lstadd(new_room_elem_lst, ft_lstnew(&adj_room,
															sizeof(adj_room)));
		}
		adj_elem = adj_elem->next;
	}
	return ;
}

static void					bfs(t_output *output, t_list **room_elem_lst,
														t_bfs_data *bfs_data)
{
	t_list			*elem;
	t_room			*room;
	t_list			*new_room_elem_lst;

	new_room_elem_lst = NULL;
	elem = *room_elem_lst;
	while (elem)
	{
		room = *(t_room **)elem->content;
		collect_adj_rooms(output, &new_room_elem_lst, room, bfs_data);
		elem = elem->next;
	}
	if (new_room_elem_lst)
	{
		ft_lstdel(room_elem_lst, del_path);
		*room_elem_lst = new_room_elem_lst;
		bfs_data->level++;
		bfs(output, room_elem_lst, bfs_data);
	}
	return ;
}

static void					start_bfs(t_output *output, t_room *room,
														t_bfs_data *bfs_data)
{
	t_list			*room_elem_lst;

	room_elem_lst = ft_lstnew(&room, sizeof(room));
	bfs(output, &room_elem_lst, bfs_data);
	ft_lstdel(&room_elem_lst, del_path);
	return ;
}

void						breadth_first_search(t_output *output)
{
	t_list			*elem;
	t_room			*room;
	t_bfs_data		bfs_data;

	reset_level_counter(output);
	bfs_data.branch_id = -1;
	elem = output->start_room_ptr->connection_lst;
	while (elem)
	{
		room = *(t_room **)elem->content;
		bfs_data.level = 1;
		bfs_data.branch_id++;
		room->num_of_conn_to_start = bfs_data.level;
		room->parent_room = output->start_room_ptr;
		if (room == output->end_room_ptr)
		{
			save_path(output, bfs_data.branch_id);
			break ;
		}
		start_bfs(output, room, &bfs_data);
		reset_level_counter(output);
		elem = elem->next;
	}
}
