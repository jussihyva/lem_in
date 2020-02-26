/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transportation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 09:45:38 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/26 18:45:48 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void					del_path(void *room, size_t size)
{
	(void)size;
	free((t_room *)room);
	return ;
}

static int					navigate_to_start(t_list room_elem,
				int64_t *visited_room, t_list *start_room_elem, t_list **path)
{
	t_room			*room;
	int				result;
	t_list			*adj_room_elem;

	result = 0;
	adj_room_elem = &room_elem;
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
			{
				result = 1;
				break ;
			}
			else
			{
				visited_room[room->id / 64] |= 1 << room->id % 64;
				next jump to recurcive;
			}
		}
	}
	return (result);
}

static t_list				*get_path(t_input *input, t_list *start_room_elem,
														t_list *end_room_elem)
{
	t_list			*path;
	t_list			*adj_room_elem;
	int64_t			*visited_room;
	t_room			*room;

	adj_room_elem = ((t_room *)end_room_elem->content)->connection_lst;
	path = NULL;
	while (adj_room_elem)
	{
		visited_room = (int64_t *)ft_memalloc(sizeof(*visited_room) *
										((input->num_of_rooms - 1) / 64 + 1));
		room = (t_room *)end_room_elem->content;
		path = ft_lstnew(room, end_room_elem->content_size);
		visited_room[room->id / 64] |= 1 << room->id % 64;
		if (navigate_to_start(*adj_room_elem, visited_room, start_room_elem,
																		&path))
			break ;
		adj_room_elem = adj_room_elem->next;
		free(visited_room);
		visited_room = NULL;
	}
	return (path);
}

static int					add_next_room_to_path(t_transportation_report *transportation_report,
								 t_list *current_room_elem)
{
	room = (t_room *)current_room_elem->content;
	adj_room_elem = room->connection_lst;
	result = 0;
	while (adj_room_elem)
	{
		room = (t_room *)adj_room_elem->content;
		if (visited_room[room->id / 64] & 1 << (room->id) % 64)
			adj_room_elem = adj_room_elem->next;
		else if (room->id == ((t_room *)start_room_elem->content)->id)
		{
			save_path(transportation_report, path);
			break ;
		}
		else
		{
			ft_lstadd(path, ft_lstnew(room, adj_room_elem->content_size));
			visited_room[room->id / 64] |= 1 << (room->id % 64);
			add_next_room_to_path(transportation_report, adj_room_elem);
			visited_room[room->id / 64] &= ~(1 << (room->id % 64));
			ft_lstdelone(path, *path);
		}
			
	}
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
