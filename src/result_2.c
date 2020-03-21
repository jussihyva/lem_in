/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   result_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pi <pi@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:21:57 by jkauppi           #+#    #+#             */
/*   Updated: 2020/03/21 08:05:52 by pi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			print_error(t_input *input)
{
	if (input->opt && input->opt & errors)
	{
		print_input_lines(input);
		ft_printf("ERROR: %d\n", input->error);
	}
	else
		ft_printf("ERROR\n");
	return ;
}

void			set_error(t_input *input, char *line, t_input_error error,
																	char *text)
{
	char			*error_line;
	t_list			*elem;

	if (input->opt && input->opt & errors)
	{
		error_line = (char *)ft_memalloc(sizeof(char) * 10000);
		ft_sprintf(error_line, "%s (line %d): %s", text, input->input_line_cnt, line, 0);
		elem = ft_lstnew(error_line, sizeof(char) *
												ft_strlen(error_line));
		ft_lstadd(input->valid_input_lines, elem);
		ft_strdel(&error_line);
	}
	else
		input->error = error;
	return ;
}

static int		move_ant_next_room(t_report *report, size_t c)
{
	t_list					*elem;
	t_room					*room;
	t_room					*next_room;
	int						all_ants_at_the_end;

	all_ants_at_the_end = 0;
	elem = report->ant_array[c].current_room_elem->next;
	next_room = *(t_room **)elem->content;
	if (!next_room->ant || next_room == report->end_room_ptr)
	{
		all_ants_at_the_end = 0;
		elem = report->ant_array[c].current_room_elem;
		room = *(t_room **)elem->content;
		room->ant = NULL;
		elem = report->ant_array[c].current_room_elem->next;
		report->ant_array[c].current_room_elem = elem;
		room = *(t_room **)elem->content;
		if (room != report->end_room_ptr)
			room->ant = &report->ant_array[c];
		ft_printf("%s-%s ", report->ant_array[c].name, room->name);
	}
	return (all_ants_at_the_end);
}

void			print_instructions(t_report *report)
{
	size_t			c;
	t_list			*elem;
	t_room			*room;
	int				all_ants_at_the_end;
	size_t			line_c;

	ft_printf("\n");
	line_c = 0;
	all_ants_at_the_end = 0;
	while (!all_ants_at_the_end)
	{
		all_ants_at_the_end = 1;
		c = -1;
		while (++c < report->number_of_ants)
		{
			elem = report->ant_array[c].current_room_elem;
			room = *(t_room **)elem->content;
			if (room != report->end_room_ptr)
				all_ants_at_the_end &= move_ant_next_room(report, c);
			if (c + 1 == report->number_of_ants)
			{
				line_c++;
				ft_printf("\n");
			}
		}
	}
	ft_printf("#lines: %d\n", line_c - 1);
	return ;
}
