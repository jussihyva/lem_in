/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_room_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 15:50:13 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/28 09:44:54 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void				create_new_room(char **splitted_line, t_input *input,
															t_room **room)
{
	static size_t	id;
	char			*endptr;
//	t_room			*room;

	*room = (t_room *)ft_memalloc(sizeof(t_room));
//	room_ptr = &room;
	(*room)->name = ft_strdup(splitted_line[0]);
	endptr = NULL;
	(*room)->coord_x = ft_strtoi(splitted_line[1], &endptr, 10);
	if (errno || *endptr)
		input->error = faulty_room_data;
	(*room)->coord_y = ft_strtoi(splitted_line[2], &endptr, 10);
	if (errno || *endptr)
		input->error = faulty_room_data;
	(*room)->id = id++;
	(*room)->connection_lst = NULL;
	return ;
}

static t_room			**add_room(char **splitted_line, t_input *input)
{
	t_list		*room_elem;
	t_room		**room_ptr;

	room_ptr = (t_room **)ft_memalloc(sizeof(*room_ptr));
	create_new_room(splitted_line, input, room_ptr);
	room_elem = ft_lstnew(room_ptr, sizeof(*room_ptr));
	free(room_ptr);
	room_ptr = NULL;
	if (input->room_lst)
		ft_lstadd(&input->room_lst, room_elem);
	else
		input->room_lst = room_elem;
	input->num_of_rooms++;
	return (room_elem->content);
}

static t_read_status	validate_room_data(char *line, t_input *input,
													t_read_status read_status)
{
	char			**splitted_line;
	size_t			c;
	t_room			**room;

	splitted_line = ft_strsplit(line, ' ');
	c = 0;
	while (splitted_line[c])
		c++;
	if (c == 3)
	{
		room = add_room(splitted_line, input);
		if (read_status == read_start_room_data)
			input->start_room_ptr = room;
		else if (read_status == read_end_room_data)
			input->end_room_ptr = room;
	}
	else
		input->error = invalid_room_data;
	ft_arraydel(splitted_line);
	read_status = read_room_data;
	return (read_status);
}

static t_room			**create_room_array(t_input *input)
{
	t_room		**room_array;
	t_list		*elem;
	size_t		id;
	size_t		num_of_rooms;

	num_of_rooms = input->num_of_rooms;
	room_array =
			(t_room **)ft_memalloc(sizeof(*room_array) * (num_of_rooms + 1));
	elem = input->room_lst;
	while (elem)
	{
		id = (*(t_room **)elem->content)->id;
		room_array[id] = *(t_room **)elem->content;
		if ((*input->start_room_ptr)->id == id)
			input->start_room_ptr = &room_array[id];
		if ((*input->end_room_ptr)->id == id)
			input->end_room_ptr = &room_array[id];
		elem = elem->next;
	}
	room_array[num_of_rooms] = NULL;
	return (room_array);
}

t_read_status			get_room_data(char *line, t_input *input,
													t_read_status read_status)
{
	if (ft_strequ(line, "##start"))
		read_status = read_start_room_data;
	else if (ft_strequ(line, "##end"))
		read_status = read_end_room_data;
	else if (line[0] == '#')
		;
	else
	{
		read_status = validate_room_data(line, input, read_status);
		if (input->error == invalid_room_data)
		{
			input->room_array = create_room_array(input);
			ft_lstdel(&input->room_lst, del_path_2);
			input->error = 0;
			read_status = read_connection_data;
		}
	}
	return (read_status);
}
