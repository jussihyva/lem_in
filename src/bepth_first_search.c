/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bepth_first_search.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 17:16:28 by ubuntu            #+#    #+#             */
/*   Updated: 2020/05/05 23:02:03 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "lem_in.h"

static int		dfs(t_output *output, t_room *current_room, size_t level)
{
	int			return_code;
	t_room		*adj_room;
	t_list		*elem;

//	ft_printf(" %s", current_room->name);
	if (level > 80)
		return (0);
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
//			ft_printf(" %s", adj_room->name);
			save_path(output, current_room);
			return_code = 2;
			current_room->is_visited = 0;
			break ;
		}
		else if (!adj_room->is_visited)
		{
			if (return_code == 2)
				return_code = 0;
			adj_room->parent_room = current_room;
			return_code |= dfs(output, adj_room, level + 1);
		}
		else if (adj_room->is_visited)
			return_code = 0;
		elem = elem->next;
	}
	if (return_code == 2)
	{
//		ft_printf("\n");
		return_code = 0;
	}
	else
		current_room->is_visited = 0;
	return (return_code);
}

void			bepth_first_search(t_output *output)
{
	int			return_code;
	t_room		*start_room;
	t_room		*adj_room;
	t_list		*elem;

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
	while (elem)
	{
		adj_room = *(t_room **)elem->content;
		adj_room->parent_room = start_room;
		return_code = dfs(output, adj_room, 1);
		adj_room->is_visited = 1;
		elem = elem->next;
	}
	return ;
}