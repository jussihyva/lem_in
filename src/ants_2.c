/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 08:59:46 by pi                #+#    #+#             */
/*   Updated: 2020/07/02 12:26:00 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static char			*print_inst(int *first_instruction, char *ant_name,
																char *room_name)
{
	char					*line;

	line = (char *)ft_memalloc(sizeof(*line) * 10000);
	if (*first_instruction)
	{
		ft_strcat(line, ant_name);
		ft_strcat(line, "-");
		ft_strcat(line, room_name);
		*first_instruction = 0;
	}
	else
	{
		ft_strcat(line, " ");
		ft_strcat(line, ant_name);
		ft_strcat(line, "-");
		ft_strcat(line, room_name);
	}
	return (line);
}

int					move_ant_next_room(t_output *output, size_t c,
														int *first_instruction)
{
	t_list					*elem;
	t_room					*room;
	t_room					*next_room;
	char					*line;

	elem = output->ant_array[c]->current_room_elem->next;
	next_room = *(t_room **)elem->content;
	if (!next_room->ant || next_room == output->end_room_ptr)
	{
		elem = output->ant_array[c]->current_room_elem;
		room = *(t_room **)elem->content;
		room->ant = NULL;
		elem = output->ant_array[c]->current_room_elem->next;
		output->ant_array[c]->current_room_elem = elem;
		room = *(t_room **)elem->content;
		if (room != output->end_room_ptr)
			room->ant = output->ant_array[c];
		line = print_inst(first_instruction, output->ant_array[c]->name,
																	room->name);
		add_line(output->instruction_line_lst, line);
		ft_strdel(&line);
	}
	return (0);
}

int					move_ant(t_instruction *instruction, t_room *end_room)
{
	t_list		*elem;
	t_room		*current_room;
	int			result;
	t_room		*next_room;
	t_ant		*ant;

	result = 0;
	next_room = instruction->room;
	ant = instruction->ant;
	current_room = (t_room *)ant->current_room;
	elem = current_room->connection_lst;
	while (elem && !result)
	{
		if (*(t_room **)elem->content == next_room && (!next_room->ant ||
														next_room == end_room))
		{
			result = 1;
			ant->current_room = next_room;
			next_room->ant = ant;
			current_room->ant = NULL;
		}
		elem = elem->next;
	}
	return (result);
}

void				read_num_of_ants(char *line, t_input *input,
													t_read_status *read_status)
{
	char			*endptr;
	int				number_of_ants;
	char			*newline;

	*read_status = e_read_room_data;
	number_of_ants = ft_strtoi(line, &endptr, 10);
	if (errno || *endptr || number_of_ants < 1)
	{
		add_valid_input_line(input->valid_input_lines, line);
		set_error(input, line, num_of_ants_error, "#ERROR ");
	}
	else
	{
		if (!input->number_of_ants)
			input->number_of_ants = number_of_ants;
		newline = ft_itoa(input->number_of_ants);
		add_valid_input_line(input->valid_input_lines, newline);
		ft_strdel(&newline);
	}
	return ;
}
