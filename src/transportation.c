/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transportation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 09:45:38 by jkauppi           #+#    #+#             */
/*   Updated: 2020/03/05 15:11:36 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void					save_path(t_report *report, t_list *path, int save,
																	int print)
{
	t_list			*elem;
	size_t			c;
	size_t			size_of_valid_path;

	size_of_valid_path = sizeof(*report->valid_path) *
												(report->number_of_rooms + 1);
	report->valid_path = (t_room **)ft_memalloc(size_of_valid_path);
	elem = path;
	c = 0;
	while (elem)
	{
		report->valid_path[c] = *((t_room **)elem->content);
		c++;
		elem = elem->next;
	}
	report->valid_path[c] = 0;
	if (print)
		print_path(report->valid_path);
	if (save)
		ft_lstadd_e(report->lst_of_valid_paths, ft_lstnew(report->valid_path,
														size_of_valid_path));
	free(report->valid_path);
	report->valid_path = NULL;
	return ;
}

static int					add_next_room_to_path(t_report *report,
							t_room *room, t_input *input, t_list *adj_room_elem)
{
	t_list			*new_room_elem;
	int				result;

	result = 0;
	while (adj_room_elem)
	{
		room = (t_room *)adj_room_elem->content;
		if (!(report->visited_room[room->id / 32] & 1 << (room->id % 32)))
		{
			report->number_of_rooms++;
			new_room_elem = ft_lstnew(&room, sizeof(room));
			ft_lstadd(report->path, new_room_elem);
			report->visited_room[room->id / 32] |= 1 << (room->id % 32);
			if (is_road_to_start_room(room, input, report))
			{
				report->visited_room[room->id / 32] &= ~(1 << (room->id % 32));
				result = 1;
			}
			*report->path = (*report->path)->next;
			ft_lstdelone(&new_room_elem, del_path_2);
			report->number_of_rooms--;
		}
		adj_room_elem = adj_room_elem->next;
	}
	return (result);
}

int							is_road_to_start_room(t_room *room,
											t_input *input, t_report *report)
{
	int		result;

	if (room->id == (*input->start_room_ptr)->id)
	{
		if (report->opt & verbose)
			save_path(report, *report->path, 1, 1);
		else
			save_path(report, *report->path, 1, 0);
		result = 1;
	}
	else
	{
		if (report->opt & verbose)
			save_path(report, *report->path, 0, 1);
		result = add_next_room_to_path(report, room, input,
														room->connection_lst);
	}
	return (result);
}

t_report					*ants_transportation(t_input *input)
{
	t_report		*report;
	t_room			*room;
	int				result;

	report = (t_report *)ft_memalloc(sizeof(*report));
	report->error = 0;
	report->opt = input->opt;
	report->path = (t_list **)ft_memalloc(sizeof(*(report->path)));
	report->lst_of_valid_paths =
				(t_list **)ft_memalloc(sizeof(*(report->lst_of_valid_paths)));
	report->valid_path = NULL;
	room = *input->end_room_ptr;
	*(report->path) = ft_lstnew(&room, sizeof(room));
	report->visited_room = (size_t *)ft_memalloc(sizeof(*report->visited_room) *
										((input->num_of_rooms - 1) / 32 + 1));
	report->visited_room[room->id / 32] |= 1 << (room->id % 32);
	report->number_of_rooms = 1;
	result = add_next_room_to_path(report, room, input, room->connection_lst);
	ft_lstdel(report->path, del_path_2);
	free(report->path);
	report->path = NULL;
	free(report->visited_room);
	report->visited_room = NULL;
	return (report);
}
