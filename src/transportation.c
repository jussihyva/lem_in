/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transportation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 09:45:38 by jkauppi           #+#    #+#             */
/*   Updated: 2020/03/08 09:45:56 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void					save_path(t_report *report, t_list *path)
{
	t_list				*elem;
	size_t				c;
	t_valid_path		valid_path;
	size_t				size_of_path;

	size_of_path = sizeof(*valid_path.path) * (report->connection_counter + 2);
	valid_path.path = (t_room **)ft_memalloc(size_of_path);
	elem = path;
	c = 0;
	while (elem)
	{
		valid_path.path[c] = *((t_room **)elem->content);
		c++;
		elem = elem->next;
	}
	valid_path.path[c] = 0;
	valid_path.num_of_rooms = c;
	if (report->opt & verbose)
		print_path(valid_path.path);
	ft_lstadd(report->lst_of_valid_paths, ft_lstnew(&valid_path,
														sizeof(valid_path)));
	return ;
}

static void					is_start_room(t_room *next_room, t_input *input,
															t_report *report)
{
	t_list			*new_room_elem;

	new_room_elem = ft_lstnew(&next_room, sizeof(next_room));
	ft_lstadd(report->path, new_room_elem);
	if (next_room->id == (*input->start_room_ptr)->id)
		save_path(report, *report->path);
	else
		validate_adj_rooms(report, input, next_room);
	*report->path = (*report->path)->next;
	ft_lstdelone(&new_room_elem, del_path_2);
	return ;
}

void						validate_adj_rooms(t_report *report, t_input *input,
																t_room *room)
{
	t_room			*next_room;
	t_list			*adj_room_elem;

	report->connection_counter++;
	room->num_of_conn_to_end = report->connection_counter;
	adj_room_elem = room->connection_lst;
	while (adj_room_elem)
	{
		next_room = *(t_room **)adj_room_elem->content;
		if ((next_room->id == (*input->start_room_ptr)->id) ||
			(!next_room->num_of_conn_to_end ||
			next_room->num_of_conn_to_end > (report->connection_counter + 1)))
			is_start_room(next_room, input, report);
		adj_room_elem = adj_room_elem->next;
	}
	report->connection_counter--;
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
	report->connection_counter = 0;
	room->num_of_conn_to_end = report->connection_counter;
	validate_adj_rooms(report, input, room);
	ft_lstdel(report->path, del_path_2);
	free(report->path);
	report->path = NULL;
	free(report->visited_room);
	report->visited_room = NULL;
	return (report);
}
