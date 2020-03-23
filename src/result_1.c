/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   result_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pi <pi@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 09:28:18 by jkauppi           #+#    #+#             */
/*   Updated: 2020/03/23 10:02:11 by pi               ###   ########.fr       */
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

void		print_path(t_report *report)
{
	t_list			*elem;
	t_list			*valid_path_elem;
	t_valid_path	*valid_path;

	valid_path_elem = *report->lst_of_valid_paths;
	while (valid_path_elem)
	{
		valid_path = *(t_valid_path **)valid_path_elem->content;
		elem = *valid_path->path;
		ft_printf("#path: %d Rooms: %d     ", valid_path->id, valid_path->num_of_conn_to_end);
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

t_report		*initialize_report(t_input *input)
{
	t_report		*report;
	size_t			c;

	report = (t_report *)ft_memalloc(sizeof(*report));
	report->error = 0;
	report->opt = input->opt;
	report->lst_of_valid_paths =
				(t_list **)ft_memalloc(sizeof(*report->lst_of_valid_paths));
	report->ant_array = (t_ant **)ft_memalloc(sizeof(*report->ant_array) *
														input->number_of_ants);
	c = -1;
	while (++c < input->number_of_ants)
		report->ant_array[c] = (t_ant *)ft_memalloc(sizeof(**report->ant_array));
	report->ant_array[c] = (t_ant *)ft_memalloc(sizeof(**report->ant_array));
	report->number_of_ants = input->number_of_ants;
	report->end_room_ptr = input->end_room_ptr;
	return (report);
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

void			print_result(t_input *input, t_report *report)
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
	print_path(report);
	print_instructions(report);
	if (report->opt && report->opt & verbose)
		print_path(report);
	ft_printf("#paths: %d\n", report->number_of_paths);
	return ;
}
