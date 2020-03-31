/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   result_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:21:57 by jkauppi           #+#    #+#             */
/*   Updated: 2020/03/31 10:27:12 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			add_line(t_list **instruction_line_lst, char *line)
{
	t_list			*elem;

	elem = ft_lstnew(line, sizeof(*line) * (ft_strlen(line) + 1));
	ft_lstadd_e(instruction_line_lst, elem);
//	ft_printf(line);
	return ;
}

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
		ft_sprintf(error_line, "%s (line %d): %s", text, input->input_line_cnt,
																		line);
		elem = ft_lstnew(error_line, sizeof(char) *
												(ft_strlen(error_line) + 1));
		ft_lstadd(input->valid_input_lines, elem);
		ft_strdel(&error_line);
	}
	else
		input->error = error;
	return ;
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
