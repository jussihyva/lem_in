/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   breadth_first_search.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 14:45:49 by ubuntu            #+#    #+#             */
/*   Updated: 2020/05/06 13:27:58 by ubuntu           ###   ########.fr       */
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
									size_t level, size_t branch_id)
{
	t_room			*adj_room;
	t_list			*adj_elem;

	adj_elem = room->connection_lst;
	while (adj_elem)
	{
		adj_room = *(t_room **)adj_elem->content;
		if (adj_room == output->end_room_ptr)
			save_path(output, room, branch_id);
		else if (adj_room->num_of_conn_to_start == -1)
		{
			adj_room->num_of_conn_to_start = level;
			adj_room->parent_room = room;
			ft_lstadd(new_room_elem_lst, ft_lstnew(&adj_room,
															sizeof(adj_room)));
		}
		adj_elem = adj_elem->next;
	}
	return ;
}

static void					bfs(t_output *output, t_list **room_elem_lst,
																size_t level, size_t branch_id)
{
	t_list			*elem;
	t_room			*room;
	t_list			*new_room_elem_lst;

	new_room_elem_lst = NULL;
	elem = *room_elem_lst;
	while (elem)
	{
		room = *(t_room **)elem->content;
		collect_adj_rooms(output, &new_room_elem_lst, room, level, branch_id);
		elem = elem->next;
	}
	if (new_room_elem_lst)
	{
		ft_lstdel(room_elem_lst, del_path);
		*room_elem_lst = new_room_elem_lst;
		bfs(output, room_elem_lst, level + 1, branch_id);
	}
	return ;
}

void						breadth_first_search(t_output *output)
{
	t_list			**room_elem_lst;
	t_list			*elem;
	t_room			*room;
	size_t			level;
	size_t			branch_id;

	reset_level_counter(output);
	room_elem_lst = (t_list **)ft_memalloc(sizeof(*room_elem_lst));
	room = output->start_room_ptr;
	branch_id = 0;
	elem = room->connection_lst;
	while (elem)
	{
		room = *(t_room **)elem->content;
		*room_elem_lst = ft_lstnew(&room, sizeof(room));
		level = 1;
		room->num_of_conn_to_start = level;
		room->parent_room = output->start_room_ptr;
		bfs(output, room_elem_lst, level + 1, branch_id++);
		ft_lstdel(room_elem_lst, del_path);
		reset_level_counter(output);
		elem = elem->next;
	}
	free(room_elem_lst);
	return ;
}
