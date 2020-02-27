/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   result.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 09:28:18 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/27 17:09:18 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		print_room_data(t_room *room)
{
	t_list		*elem;

	ft_printf("Room: %10d %20s %5d %5d\n",
	room->id, room->name, room->coord_x, room->coord_y);
	elem = room->connection_lst;
	while (elem)
	{
		ft_printf("%60s\n", ((t_room *)elem->content)->name);
		elem = elem->next;
	}
	return ;
}

static void		print_valid_input_lines(t_list **line_lst)
{
	t_list		*elem;

	elem = *line_lst;
	while (elem)
	{
		ft_printf("LINE: %s\n", (char *)elem->content);
		elem = elem->next;
	}
	return ;
}

void			print_result(t_input *input)
{
	size_t		c;
	t_room		**room;

	ft_printf("Number of ants: %20d\n", input->number_of_ants);
	room = input->room_array;
	c = 0;
	while (room[c])
	{
		print_room_data(room[c]);
		c++;
	}
	print_valid_input_lines(&input->valid_input_lines);
	return ;
}
