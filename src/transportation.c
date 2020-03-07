/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transportation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 09:45:38 by jkauppi           #+#    #+#             */
/*   Updated: 2020/03/06 16:17:34 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void					add_path_to_valid_lst(t_report *report,
															t_room **valid_path)
{
	size_t			size_of_valid_path;

	size_of_valid_path = sizeof(valid_path);
	if (*report->lst_of_valid_paths)
		ft_lstadd(report->lst_of_valid_paths, ft_lstnew(&valid_path,
														size_of_valid_path));
	else
		*report->lst_of_valid_paths = ft_lstnew(&valid_path, size_of_valid_path);
	return ;
}

static t_room				**save_path(t_report *report, t_list *path)
{
	t_list			*elem;
	size_t			c;
	t_valid_path		*valid_path;
	size_t			size_of_path;

	size_of_path = sizeof(*valid_path) * (report->connection_counter + 2);
	valid_path->path = (t_room **)ft_memalloc(size_of_valid_path);
	elem = path;
	c = 0;
	while (elem)
	{
		valid_path[c] = *((t_room **)elem->content);
		c++;
		elem = elem->next;
	}
	valid_path[c] = 0;
	valid_path->num_of_rooms = c;
	valid_path->visited_rooms = .....;
	if (report->opt & verbose)
		print_path(valid_path);
	return (valid_path);
}

static void					validate_adj_rooms(t_report *report,
										t_input *input, t_room *current_room)
{
	t_list			*new_room_elem;
	t_room			*next_room;
	t_list			*adj_room_elem;

	current_room->num_of_connections_to_end = report->step_counter;
	adj_room_elem = current_room->connection_lst;
	while (adj_room_elem)
	{
		next_room = (t_room *)adj_room_elem->content;
		if ((next_room->id == (*input->start_room_ptr)->id) || (!next_room->num_of_connections_to_end ||
					next_room->num_of_connections_to_end > report->step_counter))
		{
			report->number_of_rooms++;
			report->step_counter++;
			new_room_elem = ft_lstnew(&next_room, sizeof(next_room));
			ft_lstadd(report->path, new_room_elem);
			if (next_room->id == (*input->start_room_ptr)->id)
				add_path_to_valid_lst(report, save_path(report, *report->path));
			else
				add_room_to_path(report, input, next_room);
			*report->path = (*report->path)->next;
			ft_lstdelone(&new_room_elem, del_path_2);
			report->number_of_rooms--;
			report->step_counter--;
		}
		adj_room_elem = adj_room_elem->next;
	}
	return ;
}

t_report					*ants_transportation(t_input *input)
{
	t_report		*report;
	t_room			*room;

	report = (t_report *)ft_memalloc(sizeof(*report));
	report->error = 0;
	report->opt = input->opt;
	report->path = (t_list **)ft_memalloc(sizeof(*(report->path)));
	report->lst_of_valid_paths =
				(t_list **)ft_memalloc(sizeof(*(report->lst_of_valid_paths)));
	room = *input->end_room_ptr;
	*(report->path) = ft_lstnew(&room, sizeof(room));
	report->visited_room = (size_t *)ft_memalloc(sizeof(*report->visited_room) *
										((input->num_of_rooms - 1) / 32 + 1));
	report->visited_room[room->id / 32] |= 1 << (room->id % 32);
	report->number_of_rooms = 1;
	report->connection_counter = 0;
	add_room_to_path(report, input, room);
	ft_lstdel(report->path, del_path_2);
	free(report->path);
	report->path = NULL;
	free(report->visited_room);
	report->visited_room = NULL;
	return (report);
}
