/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_data_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 13:57:11 by jkauppi           #+#    #+#             */
/*   Updated: 2020/05/29 13:30:05 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				prepare_room_data(t_room **room_array, size_t num_of_rooms)
{
	size_t		i;
	t_room		*room;

	i = -1;
	while (++i < num_of_rooms)
	{
		room = room_array[i];
		room->is_blocked = 0;
		room->is_visited = 0;
	}
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

	if (input->room_lst)
	{
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
	}
	else
		room_array = NULL;
	ft_lstdel(&input->room_lst, del_path);
	return (room_array);
}

t_room				*get_room(char *name, t_input *input)
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
