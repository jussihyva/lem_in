/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_room_data_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 09:48:49 by jkauppi           #+#    #+#             */
/*   Updated: 2020/03/10 14:04:39 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void			create_new_room(char **splitted_line, t_input *input,
															t_room **room_ptr)
{
	static size_t	id;
	char			*endptr;

	*room_ptr = (t_room *)ft_memalloc(sizeof(t_room));
	(*room_ptr)->name = ft_strdup(splitted_line[0]);
	endptr = NULL;
	(*room_ptr)->coord_x = ft_strtoi(splitted_line[1], &endptr, 10) * 30;
	if (errno || *endptr)
		input->error = faulty_room_data;
	(*room_ptr)->coord_y = ft_strtoi(splitted_line[2], &endptr, 10) * 100;
	if (errno || *endptr)
		input->error = faulty_room_data;
	(*room_ptr)->id = id++;
	(*room_ptr)->connection_lst = NULL;
	return ;
}

t_room				**add_room(char **splitted_line, t_input *input)
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

t_room				**create_room_array_1(t_input *input)
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

t_room				*get_room_1(char *name, t_input *input)
{
	t_room		*room;
	size_t		c;

	room = NULL;
	c = -1;
	while (++c < input->num_of_rooms)
	{
		if (!ft_strcmp(input->room_array[c]->name, name))
		{
			room = input->room_array[c];
			break ;
		}
	}
	return (room);
}
