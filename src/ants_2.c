/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 08:59:46 by pi                #+#    #+#             */
/*   Updated: 2020/03/29 18:56:18 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void			print_inst(int *first_instruction, char *ant_name,
																char *room_name)
{
	if (*first_instruction)
	{
		ft_printf("%s-%s", ant_name, room_name);
		*first_instruction = 0;
	}
	else
		ft_printf(" %s-%s", ant_name, room_name);
	return ;
}

int					move_ant_next_room(t_output *output, size_t c,
														int *first_instruction)
{
	t_list					*elem;
	t_room					*room;
	t_room					*next_room;
	int						all_ants_at_the_end;

	all_ants_at_the_end = 0;
	elem = output->ant_array[c]->current_room_elem->next;
	next_room = *(t_room **)elem->content;
	if (!next_room->ant || next_room == output->end_room_ptr)
	{
		all_ants_at_the_end = 0;
		elem = output->ant_array[c]->current_room_elem;
		room = *(t_room **)elem->content;
		room->ant = NULL;
		elem = output->ant_array[c]->current_room_elem->next;
		output->ant_array[c]->current_room_elem = elem;
		room = *(t_room **)elem->content;
		if (room != output->end_room_ptr)
			room->ant = output->ant_array[c];
		print_inst(first_instruction, output->ant_array[c]->name, room->name);
	}
	return (all_ants_at_the_end);
}

int					move_ant(t_instruction *instruction)
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
		if (*(t_room **)elem->content == next_room)
		{
			result = 1;
			ant->current_room = next_room;
		}
		elem = elem->next;
	}
	return (result);
}

void				read_num_of_ants(char *line, t_input *input,
													t_read_status *read_status)
{
	char			*endptr;
	size_t			number_of_ants;
	char			*newline;

	*read_status = e_read_room_data;
	number_of_ants = ft_strtoi(line, &endptr, 10);
	if (errno || *endptr)
	{
		add_valid_input_line(input->valid_input_lines, line);
		set_error(input, line, num_of_ants_error, "#ERROR ");
	}
	else
	{
		if (!input->number_of_ants)
			input->number_of_ants = number_of_ants;
//		create_ants(input);
		newline = ft_itoa(input->number_of_ants);
		add_valid_input_line(input->valid_input_lines, newline);
		ft_strdel(&newline);
	}
	return ;
}
