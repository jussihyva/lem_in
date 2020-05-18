/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   depth_first_search_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 17:16:28 by ubuntu            #+#    #+#             */
/*   Updated: 2020/05/18 06:57:08 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		dfs(t_output *output, t_room *current_room, size_t level,
															size_t branch_id)
{
	int			return_code;
	t_room		*adj_room;
	t_list		*elem;

	current_room->is_visited = 1;
	return_code = 2;
	elem = current_room->connection_lst;
	while (elem)
	{
		adj_room = *(t_room **)elem->content;
		if (adj_room == current_room->parent_room)
			;
		else if (adj_room == output->end_room_ptr)
		{
			adj_room->parent_room = current_room;
			save_path(output, current_room, branch_id);
			return_code = 2;
			current_room->is_visited = 0;
			break ;
		}
		else if (!adj_room->is_visited)
		{
			if (return_code == 2)
				return_code = 0;
			adj_room->parent_room = current_room;
			return_code |= dfs(output, adj_room, level + 1, branch_id);
		}
		else if (adj_room->is_visited)
			return_code = 0;
		elem = elem->next;
	}
	if (return_code == 2)
	{
		return_code = 0;
	}
	else
		current_room->is_visited = 0;
	return (return_code);
}

void			depth_first_search(t_output *output)
{
	t_room		*start_room;
	t_room		*adj_room;
	t_list		*elem;
	size_t		branch_id;

	start_room = output->start_room_ptr;
	start_room->is_visited = 1;
	elem = start_room->connection_lst;
	while (elem)
	{
		adj_room = *(t_room **)elem->content;
		adj_room->is_visited = 1;
		elem = elem->next;
	}
	elem = start_room->connection_lst;
	branch_id = 0;
	while (elem)
	{
		adj_room = *(t_room **)elem->content;
		adj_room->parent_room = start_room;
		if (adj_room == output->end_room_ptr)
			save_path(output, start_room, branch_id);
		else
			dfs(output, adj_room, 1, branch_id++);
		adj_room->is_visited = 1;
		elem = elem->next;
	}
	return ;
}
