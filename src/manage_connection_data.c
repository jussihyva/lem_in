/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_connection_data.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:23:43 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/26 13:39:27 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_room			*get_room(char *name, t_list *room_lst)
{
	t_room		*room;
	t_list		*elem;

	room = NULL;
	elem = room_lst;
	while (elem)
	{
		if (ft_strequ(((t_room *)elem->content)->name, name))
		{
			room = ((t_room *)elem->content);
			break ;
		}
		elem = elem->next;
	}
	return (room);
}

static void				add_connection(t_room *room, t_room *dest_room)
{
	t_list		*elem;

	elem = ft_lstnew(dest_room, sizeof(*dest_room));
	if (room->connection_lst)
		ft_lstadd_e(&(room->connection_lst), elem);
	else
		room->connection_lst = elem;
	return ;
}

static t_read_status	validate_connection_data(char *line, t_input *input,
													t_read_status read_status)
{
	char			**splitted_line;
	size_t			c;
	t_room			*room1;
	t_room			*room2;

	splitted_line = ft_strsplit(line, '-');
	c = 0;
	while (splitted_line[c])
		c++;
	if (c == 2)
	{
		room1 = get_room(splitted_line[0], input->room_lst);
		room2 = get_room(splitted_line[1], input->room_lst);
		if (room1 && room2)
		{
			add_connection(room1, room2);
			add_connection(room2, room1);
		}
	}
	else
		input->error = invalid_connection_data;
	ft_arraydel(splitted_line);
	read_status = read_connection_data;
	return (read_status);
}

t_read_status			get_connection_data(char *line, t_input *input,
													t_read_status read_status)
{
	read_status = validate_connection_data(line, input, read_status);
	return (read_status);
}
