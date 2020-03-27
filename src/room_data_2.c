/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_data_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pi <pi@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 09:48:49 by jkauppi           #+#    #+#             */
/*   Updated: 2020/03/27 10:10:17 by pi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void			create_new_room(char **splitted_line, t_input *input,
															t_room **room_ptr)
{
	static size_t	id;
	char			*endptr;

	*room_ptr = (t_room *)ft_memalloc(sizeof(**room_ptr));
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

	if (splitted_line[0][0] == 'L')
		input->error = invalid_room_name;
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
