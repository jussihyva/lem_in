/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transportation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 09:45:38 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/27 11:18:32 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void					del_path(void *room, size_t size)
{
	(void)size;
	(void)room;
	return ;
}

static void					save_path(t_transportation_report
										*transportation_report, t_list *path)
{
	t_list			*elem;
	size_t			c;

	transportation_report->valid_path =
		(t_room **)ft_memalloc(sizeof(*transportation_report->valid_path) *
								(transportation_report->number_of_rooms + 1));
	elem = path;
	c = 0;
	while (elem)
	{
		transportation_report->valid_path[c] = (t_room *)elem->content;
		c++;
		elem = elem->next;
	}
	transportation_report->valid_path[c] = 0;
	return ;
}

static void					add_next_room_to_path(t_transportation_report
							*transportation_report, t_list *current_room_elem,
							t_list *start_room_elem, int64_t *visited_room)
{
	t_room			*room;
	t_list			*adj_room_elem;
	t_list			**path;
	t_list			*old_path;

	room = (t_room *)current_room_elem->content;
	path = transportation_report->path;
	adj_room_elem = room->connection_lst;
	while (adj_room_elem)
	{
		room = (t_room *)adj_room_elem->content;
		if (visited_room[room->id / 64] & 1 << (room->id) % 64)
			adj_room_elem = adj_room_elem->next;
		else if (room->id == ((t_room *)start_room_elem->content)->id)
		{
			transportation_report->number_of_rooms++;
			ft_lstadd(path, ft_lstnew(room, adj_room_elem->content_size));
			save_path(transportation_report, *path);
			transportation_report->number_of_rooms--;
			break ;
		}
		else
		{
			ft_lstadd(path, ft_lstnew(room, adj_room_elem->content_size));
			visited_room[room->id / 64] |= 1 << (room->id % 64);
			transportation_report->number_of_rooms++;
			add_next_room_to_path(transportation_report, adj_room_elem,
												start_room_elem, visited_room);
			visited_room[room->id / 64] &= ~(1 << (room->id % 64));
			transportation_report->number_of_rooms--;
			old_path = *path;
			*path = (*path)->next;
			ft_lstdelone(&old_path, del_path);
			adj_room_elem = adj_room_elem->next;
		}
	}
	return ;
}

static void					print_path(t_room **path)
{
	size_t		c;

	c = 0;
	while (path[c])
	{
		ft_printf("%5s ", path[c]->name);
		free(path[c]);
		path[c] = NULL;
		c++;
	}
	ft_printf("\n");
	return ;
}

t_transportation_report		*ants_transportation(t_input *input)
{
	t_transportation_report		*transportation_report;
	int64_t						*visited_room;
	t_room						*room;

	transportation_report =
		(t_transportation_report *)ft_memalloc(sizeof(*transportation_report));
	transportation_report->error = 0;
	transportation_report->path =
				(t_list **)ft_memalloc(sizeof(*(transportation_report->path)));
	transportation_report->valid_path = NULL;
	room = (t_room *)input->end_room->content;
	*(transportation_report->path) =
								ft_lstnew(room, sizeof(t_room));
	visited_room = (int64_t *)ft_memalloc(sizeof(*visited_room) *
										((input->num_of_rooms - 1) / 64 + 1));
	visited_room[room->id / 64] |= 1 << (room->id % 64);
	transportation_report->number_of_rooms = 1;
	add_next_room_to_path(transportation_report, input->end_room,
											input->start_room, visited_room);
	if (transportation_report->valid_path)
	{
		print_path(transportation_report->valid_path);
		free(transportation_report->valid_path);
		transportation_report->valid_path = NULL;
	}
	ft_lstdel(transportation_report->path, del_path);
	free(transportation_report->path);
	transportation_report->path = NULL;
	free(visited_room);
	visited_room = NULL;
	return (transportation_report);
}
