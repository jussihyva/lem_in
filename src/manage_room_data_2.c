/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_room_data_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 13:57:11 by jkauppi           #+#    #+#             */
/*   Updated: 2020/03/10 14:32:38 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room				**create_room_array_2(t_input *input)
{
	t_room		**room_array;
	t_list		*elem;
	size_t		id;
	size_t		c;
	size_t		num_of_rooms;

	num_of_rooms = input->num_of_rooms;
	room_array =
			(t_room **)ft_memalloc(sizeof(*room_array) * (num_of_rooms + 1));
	elem = input->room_lst;
	id = -1;
	room_array[++id] = *(t_room **)elem->content;
	elem = elem->next;
	while (elem)
	{
		c = ++id;
		while (c && (ft_strcmp(room_array[c - 1]->name, (*(t_room **)elem->content)->name) > 0))
		{
			room_array[c] = room_array[c - 1];
			c--;
		}
		room_array[c] = *(t_room **)elem->content;
		elem = elem->next;
	}
	room_array[num_of_rooms] = NULL;
	id = -1;
	while (++id < num_of_rooms)
	{
		if ((*input->start_room_ptr)->id == room_array[id]->id)
			input->start_room_ptr = &room_array[id];
		if ((*input->end_room_ptr)->id == room_array[id]->id)
			input->end_room_ptr = &room_array[id];
		room_array[id]->id = id;
	}
	return (room_array);
}

t_room				*get_room_2(char *name, t_input *input)
{
	t_room		*room;
	size_t		low;
	size_t		middle;
	size_t		high;
	int			result;

	room = NULL;
	low = 0;
	high = input->num_of_rooms - 1;
	while (low <= high)
	{
		middle = (high + low) / 2;
		result = ft_strcmp(name, input->room_array[middle]->name);
		if (!result)
		{
			room = input->room_array[middle];
			break ;
		}
		else if (result < 0)
			high = middle - 1;
		else
			low = middle + 1;
	}
	return (room);
}
