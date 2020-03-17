/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   result_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:21:57 by jkauppi           #+#    #+#             */
/*   Updated: 2020/03/12 20:16:36 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			set_error(t_input *input, char *line, t_input_error error,
																	char *text)
{
	char			*error_line;
	t_list			*elem;

	if (input->opt && input->opt & errors)
	{
		error_line = ft_strjoin(text, line);
		elem = ft_lstnew(error_line, sizeof(char) *
												ft_strlen(error_line));
		ft_lstadd(input->valid_input_lines, elem);
		ft_strdel(&error_line);
	}
	else
		input->error = error;
	return ;
}

static void		put_ants_to_valid_path(t_report *report)
{
	t_list					*elem;
	size_t					c;

	elem = *(t_list **)report->ant_array[0].path;
	c = -1;
	while (++c < report->number_of_ants)
		report->ant_array[c].current_room_elem = elem;
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

	put_ants_to_valid_path(report);
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
	ft_printf("#lines: %d\n", line_c);
	return ;
}
