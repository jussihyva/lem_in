/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_room_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 15:50:13 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/24 19:21:52 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_list	*add_room(t_input *input, t_room *room)
{
	t_list		*room_elem;

	room_elem = ft_lstnew(room, sizeof(*room));
	free(room);
	room = NULL;
	if (input->room_lst)
		ft_lstadd(&input->room_lst, room_elem);
	else
		input->room_lst = room_elem;
	return (room_elem);
}

t_room			*create_new_room(char **splitted_line, t_input *input)
{
	t_room			*room;
	static size_t	id;
	char			*endptr;

	room = (t_room *)ft_memalloc(sizeof(*room));
	room->name = ft_strdup(splitted_line[0]);
	endptr = NULL;
	room->coord_x = ft_strtoi(splitted_line[1], &endptr, 10);
	if (errno || *endptr)
		input->error = faulty_room_data;
	room->coord_y = ft_strtoi(splitted_line[2], &endptr, 10);
	if (errno || *endptr)
		input->error = faulty_room_data;
	room->id = id++;
	return (room);
}

t_read_status	validate_room_data(char *line, t_input *input,
													t_read_status read_status)
{
	char			**splitted_line;
	size_t			c;
	t_room			*room;
	t_list			*room_elem;

	ft_printf("Get start room data: %s\n", line);
	splitted_line = ft_strsplit(line, ' ');
	c = 0;
	while (splitted_line[c])
		c++;
	if (c == 3)
	{
		room = create_new_room(splitted_line, input);
		room_elem = add_room(input, room);
		if (read_status == read_start_room_data)
			input->start_room = room_elem;
		else if (read_status == read_end_room_data)
			input->end_room = room_elem;
	}
	else
		input->error = invalid_room_data;
	ft_arraydel(splitted_line);
	read_status = read_room_data;
	return (read_status);
}

t_read_status	get_room_data(char *line, t_input *input,
													t_read_status read_status)
{
	ft_printf("Get room data: %s\n", line);
	if (ft_strequ(line, "##start"))
		read_status = read_start_room_data;
	else if (ft_strequ(line, "##end"))
		read_status = read_end_room_data;
	else
	{
		read_status = validate_room_data(line, input, read_status);
		if (input->error == invalid_room_data)
		{
			input->error = 0;
//			read_status = read_connection_data;
//			read_status = validate_connection_data(line, input, read_status);
		}
	}
	return (read_status);
}
