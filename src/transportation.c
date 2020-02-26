/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transportation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 09:45:38 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/26 18:20:42 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void					del_path(void *room, size_t size)
{
	(void)size;
	free((t_room *)room);
	return ;
}

static void					navigate_to_start(t_list *adj_room_elem,
				int64_t *visited_room, t_list *start_room_elem, t_list **path)
{
	t_room			*room;

	while (adj_room_elem)
	{
		room = (t_room *)adj_room_elem->content;
		if (visited_room[room->id / 64] & 1 << (room->id) % 64)
			adj_room_elem = adj_room_elem->next;
		else
		{
			visited_room[room->id / 64] |= 1 << room->id;
			ft_lstadd(path, ft_lstnew(room, adj_room_elem->content_size));
			if (room->id == ((t_room *)start_room_elem->content)->id)
				break ;
			else
				adj_room_elem = room->connection_lst;
		}
	}
	return ;
}

static t_list				*get_path(t_input *input, t_list *start_room_elem,
														t_list *end_room_elem)
{
	t_list			*path;
	t_list			*adj_room_elem;
	int64_t			*visited_room;
	t_room			*room;

	visited_room = (int64_t *)ft_memalloc(sizeof(*visited_room) *
										((input->num_of_rooms - 1) / 64 + 1));
	adj_room_elem = ((t_room *)end_room_elem->content)->connection_lst;
	if (adj_room_elem)
	{
		room = (t_room *)end_room_elem->content;
		path = ft_lstnew(room, end_room_elem->content_size);
		visited_room[room->id / 64] |= 1 << room->id % 64;
		navigate_to_start(adj_room_elem, visited_room, start_room_elem, &path);
	}
	else
		path = NULL;
	free(visited_room);
	visited_room = NULL;
	return (path);
}

static void					print_path(t_list *path)
{
	t_list		*elem;

	elem = path;
	while (elem)
	{
		ft_printf("%5s ", ((t_room *)elem->content)->name);
		elem = elem->next;
	}
	ft_printf("\n");
	return ;
}

t_transportation_report		ants_transportation(t_input *input)
{
	t_transportation_report		transportation_report;
	t_list						*path;

	transportation_report.error = 0;
	path = get_path(input, input->start_room, input->end_room);
	if (path)
	{
		print_path(path);
		ft_lstdel(&path, del_path);
	}
	return (transportation_report);
}
