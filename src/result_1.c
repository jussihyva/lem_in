/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   result_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 09:28:18 by jkauppi           #+#    #+#             */
/*   Updated: 2020/04/01 18:18:40 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		print_room_data(t_room *room)
{
	t_list		*elem;

	ft_printf("Room: %10d %5d %20s %5d %5d\n",
	room->id, room->num_of_conn_to_end, room->name, room->coord_x,
																room->coord_y);
	elem = room->connection_lst;
	while (elem)
	{
		ft_printf("%65s %5d\n", (*(t_room **)elem->content)->name,
							(*(t_room **)elem->content)->num_of_conn_to_end);
		elem = elem->next;
	}
	return ;
}

void			print_path(t_output *output)
{
	t_list			*elem;
	t_list			*valid_path_elem;
	t_valid_path	*valid_path;

	valid_path_elem = *output->lst_of_valid_paths;
	while (valid_path_elem)
	{
		valid_path = *(t_valid_path **)valid_path_elem->content;
		elem = *valid_path->path;
		ft_printf("#path: %d Rooms: %5d     ", valid_path->id,
												valid_path->num_of_conn_to_end);
		while (elem)
		{
			ft_printf(" %5s", (*(t_room **)elem->content)->name);
			elem = elem->next;
		}
		ft_printf("\n");
		valid_path_elem = valid_path_elem->next;
	}
	ft_printf("#\n");
	return ;
}

void			print_input_lines(t_input *input)
{
	t_list		*elem;

	elem = *input->valid_input_lines;
	while (elem->next)
		elem = elem->next;
	while (elem)
	{
		ft_putendl((char *)elem->content);
		elem = elem->prev;
	}
	return ;
}

void			print_output(t_input *input, t_output *output)
{
	size_t		c;
	t_room		**room;

	room = input->room_array;
	if (input->opt & verbose)
	{
		c = -1;
		while (room[++c])
			print_room_data(room[c]);
	}
	print_input_lines(input);
	print_path(output);
	print_instructions(output);
	ft_printf("#paths: %d\n", output->number_of_paths);
	return ;
}
