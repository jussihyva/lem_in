/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/29 12:20:21 by ubuntu            #+#    #+#             */
/*   Updated: 2020/04/03 12:15:59 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_output		*initialize_output(t_input *input)
{
	t_output		*output;

	output = (t_output *)ft_memalloc(sizeof(*output));
	output->error = 0;
	output->opt = input->opt;
	output->lst_of_valid_paths =
					(t_list **)ft_memalloc(sizeof(*output->lst_of_valid_paths));
	output->instruction_line_lst =
				(t_list **)ft_memalloc(sizeof(*output->instruction_line_lst));
	output->number_of_ants = input->number_of_ants;
	output->end_room_ptr = input->end_room_ptr;
	output->start_room_ptr = input->start_room_ptr;
	output->num_of_rooms = input->num_of_rooms;
	output->number_of_paths = 0;
	create_ants(output);
	return (output);
}

static void		add_num_of_lines(t_output *output)
{
	char			*line;

	line = (char *)ft_memalloc(sizeof(*line) * 10000);
	ft_sprintf(line, "#lines: %d\n", output->number_of_instruction_line - 1);
	add_line(output->instruction_line_lst, line);
	ft_strdel(&line);
	return ;
}

void			update_instructions(t_output *output)
{
	size_t			c;
	t_list			*elem;
	int				all_ants_at_the_end;
	int				first;

	output->number_of_instruction_line = 0;
	all_ants_at_the_end = 0;
	while (!all_ants_at_the_end)
	{
		add_line(output->instruction_line_lst, "\n");
		first = 1;
		all_ants_at_the_end = 1;
		c = -1;
		while (++c < output->number_of_ants)
		{
			elem = output->ant_array[c]->current_room_elem;
			if (*(t_room **)elem->content != output->end_room_ptr)
				all_ants_at_the_end &= move_ant_next_room(output, c, &first);
		}
		output->number_of_instruction_line++;
	}
	add_num_of_lines(output);
	set_ants_to_start_room(output);
	return ;
}

void			print_instructions(t_output *output)
{
	t_list		*elem;

	elem = *output->instruction_line_lst;
	while (elem)
	{
		ft_printf((char *)elem->content);
		elem = elem->next;
	}
	return ;
}
