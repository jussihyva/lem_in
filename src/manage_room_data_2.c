/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_room_data_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 13:57:11 by jkauppi           #+#    #+#             */
/*   Updated: 2020/03/11 17:02:59 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void			set_start_end_ptr(t_input *input, t_room **room_array)
{
	size_t		id;
	size_t		start_id;
	size_t		end_id;

	id = -1;
	start_id = 0;
	end_id = 0;
	while (++id < input->num_of_rooms)
	{
		if ((*input->start_room_ptr)->id == room_array[id]->id)
		{
			input->start_room_ptr = &room_array[id];
			start_id = id;
		}
		if ((*input->end_room_ptr)->id == room_array[id]->id)
		{
			input->end_room_ptr = &room_array[id];
			end_id = id;
		}
	}
	room_array[start_id]->id = start_id;
	room_array[end_id]->id = end_id;
	id = -1;
	while (++id < input->num_of_rooms)
		room_array[id]->id = id;
}

static void			add_room_to_array(t_room **room_array, t_list *elem,
																size_t index)
{
	size_t		c;

	c = index;
	while (c && (ft_strcmp(room_array[c - 1]->name,
									(*(t_room **)elem->content)->name) > 0))
	{
		room_array[c] = room_array[c - 1];
		c--;
	}
	room_array[c] = *(t_room **)elem->content;
	return ;
}

t_room				**create_room_array_2(t_input *input)
{
	t_room		**room_array;
	t_list		*elem;
	size_t		index;

	room_array = (t_room **)ft_memalloc(sizeof(*room_array) *
													(input->num_of_rooms + 1));
	elem = input->room_lst;
	index = -1;
	room_array[++index] = *(t_room **)elem->content;
	elem = elem->next;
	while (elem)
	{
		add_room_to_array(room_array, elem, ++index);
		elem = elem->next;
	}
	room_array[input->num_of_rooms] = NULL;
	set_start_end_ptr(input, room_array);
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
