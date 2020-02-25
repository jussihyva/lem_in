/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   result.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 09:28:18 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/25 14:40:58 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		print_room_data(t_room *room)
{
	ft_printf("Room: Name: %20s %10d %5d %5d\n",
	room->name, room->id, room->coord_x, room->coord_y);
	return ;
}

// static void		print_valid_input_lines(t_list **line_lst)
// {
// 	t_list		*elem;

// 	elem = *line_lst;
// 	while (elem)
// 	{
// 		ft_printf("LINE: %s\n", (char *)elem->content);
// 		elem = elem->next;
// 	}
// 	return ;
// }

void			print_result(t_input *input)
{
	t_list		*elem;

	ft_printf("Number of ants: %20d\n", input->number_of_ants);
	elem = input->room_lst;
	while (elem)
	{
		print_room_data((t_room *)elem->content);
		elem = elem->next;
	}
//	print_valid_input_lines(&input->valid_input_lines);
	return ;
}
