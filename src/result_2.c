/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   result_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:21:57 by jkauppi           #+#    #+#             */
/*   Updated: 2020/03/09 21:05:28 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		print_instructions(t_report *report)
{
	size_t		c;
	t_list		*elem;
	t_room		*room;
	t_room		*next_room;

	elem = *(t_list **)report->ant_array[0].path;
	c = -1;
	while (++c < report->number_of_ants)
		report->ant_array[c].current_room_elem = elem;
	c = -1;
	while (++c < report->number_of_ants)
	{
		elem = report->ant_array[c].current_room_elem;
		room = *(t_room **)elem->content;
		if (room == *report->end_room_ptr)
			;
		else
		{
			elem = report->ant_array[c].current_room_elem->next;
			next_room = *(t_room **)elem->content;
			if (!next_room->ant || next_room == *report->end_room_ptr)
			{
				elem = report->ant_array[c].current_room_elem;
				room = *(t_room **)elem->content;
				room->ant = NULL;
				elem = report->ant_array[c].current_room_elem->next;
				report->ant_array[c].current_room_elem = elem;
				room = *(t_room **)elem->content;
				if (room != *report->end_room_ptr)
					room->ant = &report->ant_array[c];
				ft_printf("%s-%s ", report->ant_array[c].name, room->name);
				if (c + 1 == report->number_of_ants)
				{
					c = -1;
					ft_printf("\n");
				}
			}
			else
			{
				if (c + 1 == report->number_of_ants && room == *report->end_room_ptr)
					break ;
				c = -1;
				ft_printf("\n");
			}
		}
	}
	ft_printf("\n");
	return ;
}
