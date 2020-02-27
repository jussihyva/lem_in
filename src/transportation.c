/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transportation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 09:45:38 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/27 14:10:08 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void					del_path(void *room, size_t size)
{
	(void)size;
	(void)room;
	return ;
}

static void					save_path(t_report *report, t_list *path)
{
	t_list			*elem;
	size_t			c;

	report->valid_path = (t_room **)ft_memalloc(sizeof(*report->valid_path) *
								(report->number_of_rooms + 1));
	elem = path;
	c = 0;
	while (elem)
	{
		report->valid_path[c] = (t_room *)elem->content;
		c++;
		elem = elem->next;
	}
	report->valid_path[c] = 0;
	return ;
}

static void					add_next_room_to_path(t_report *report,
							t_list *adj_room_elem,
							t_list *start_room_elem, int64_t *visited_room)
{
	t_room			*room;
	t_list			*new_room_elem;

	while (adj_room_elem)
	{
		room = (t_room *)adj_room_elem->content;
		if (!(visited_room[room->id / 64] & 1 << (room->id) % 64))
		{
			report->number_of_rooms++;
			new_room_elem = ft_lstnew(room, adj_room_elem->content_size);
			ft_lstadd(report->path, new_room_elem);
			visited_room[room->id / 64] |= 1 << (room->id % 64);
			if (room->id == ((t_room *)start_room_elem->content)->id)
				save_path(report, *report->path);
			else
				add_next_room_to_path(report, room->connection_lst,
												start_room_elem, visited_room);
			visited_room[room->id / 64] &= ~(1 << (room->id % 64));
			*report->path = (*report->path)->next;
			ft_lstdelone(&new_room_elem, del_path);
			report->number_of_rooms--;
		}
		adj_room_elem = adj_room_elem->next;
	}
	return ;
}

static void					print_path(t_report *report)
{
	size_t		c;
	t_room		**path;

	if (report->valid_path)
	{
		path = report->valid_path;
		c = 0;
		while (path[c])
		{
			ft_printf("%5s ", path[c]->name);
			free(path[c]);
			path[c] = NULL;
			c++;
		}
		ft_printf("\n");
		free(report->valid_path);
		report->valid_path = NULL;
	}
	return ;
}

t_report					*ants_transportation(t_input *input)
{
	t_report		*report;
	int64_t			*visited_room;
	t_room			*room;

	report = (t_report *)ft_memalloc(sizeof(*report));
	report->error = 0;
	report->path = (t_list **)ft_memalloc(sizeof(*(report->path)));
	report->valid_path = NULL;
	room = (t_room *)input->end_room->content;
	*(report->path) = ft_lstnew(room, sizeof(t_room));
	visited_room = (int64_t *)ft_memalloc(sizeof(*visited_room) *
										((input->num_of_rooms - 1) / 64 + 1));
	visited_room[room->id / 64] |= 1 << (room->id % 64);
	report->number_of_rooms = 1;
	add_next_room_to_path(report, room->connection_lst,
											input->start_room, visited_room);
	print_path(report);
	ft_lstdel(report->path, del_path);
	free(report->path);
	report->path = NULL;
	free(visited_room);
	visited_room = NULL;
	return (report);
}
