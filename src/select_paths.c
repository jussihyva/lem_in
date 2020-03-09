/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 10:16:44 by jkauppi           #+#    #+#             */
/*   Updated: 2020/03/09 19:56:31 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_room			*get_next_best_room(t_list *adj_room_elem)
{
	t_room		*best_room;
	t_room		*next_room;

	best_room = NULL;
	while (adj_room_elem)
	{
		next_room = *(t_room **)adj_room_elem->content;
		if (best_room)
		{
			if (next_room->num_of_conn_to_end <
											best_room->num_of_conn_to_end)
				best_room = next_room;
		}
		else
			best_room = next_room;
		adj_room_elem = adj_room_elem->next;
	}
	return (best_room);
}

static t_valid_path		*find_shortest_path(t_input *input, t_list **path)
{
	t_list			*adj_room_elem;
	int				end_room_reached;
	t_room			*best_room;
	t_valid_path	*valid_path;

	ft_lstadd_e(path, ft_lstnew(input->start_room_ptr,
											sizeof(*input->start_room_ptr)));
	adj_room_elem = (*input->start_room_ptr)->connection_lst;
	end_room_reached = 0;
	while (!end_room_reached)
	{
		best_room = get_next_best_room(adj_room_elem);
		ft_lstadd_e(path, ft_lstnew(&best_room, sizeof(best_room)));
		if (best_room == *input->end_room_ptr)
			end_room_reached = 1;
		else
			adj_room_elem = best_room->connection_lst;
	}
	valid_path = (t_valid_path *)ft_memalloc(sizeof(*valid_path));
	valid_path->path = path;
	valid_path->num_of_conn_to_end =
								(*input->start_room_ptr)->num_of_conn_to_end;
	return (valid_path);
}

void					select_paths(t_input *input, t_report *report)
{
	t_valid_path	*valid_path;
	t_list			**path;
	size_t			c;
	char			*ant_id;

	path = (t_list **)ft_memalloc(sizeof(*path));
	valid_path = find_shortest_path(input, path);
	ft_lstadd(report->lst_of_valid_paths, ft_lstnew(&valid_path,
														sizeof(valid_path)));
	report->number_of_paths = 1;
	c = -1;
	while (++c < report->number_of_ants)
	{
		ant_id = ft_itoa(c + 1);
		report->ant_array[c].name = ft_strjoin("L", ant_id);
		ft_strdel(&ant_id);
		report->ant_array[c].path = valid_path->path;
	}
	return ;
}
