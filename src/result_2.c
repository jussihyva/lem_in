/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   result_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:21:57 by jkauppi           #+#    #+#             */
/*   Updated: 2020/03/29 18:50:25 by ubuntu           ###   ########.fr       */
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

void			print_instructions(t_output *output)
{
	size_t			c;
	t_list			*elem;
	int				all_ants_at_the_end;
	size_t			line_c;
	int				first;

	line_c = 0;
	all_ants_at_the_end = 0;
	while (!all_ants_at_the_end)
	{
		ft_printf("\n");
		first = 1;
		all_ants_at_the_end = 1;
		c = -1;
		while (++c < output->number_of_ants)
		{
			elem = output->ant_array[c]->current_room_elem;
			if (*(t_room **)elem->content != output->end_room_ptr)
				all_ants_at_the_end &= move_ant_next_room(output, c, &first);
		}
		line_c++;
	}
	ft_printf("#lines: %d\n", line_c - 1);
	return ;
}

void			print_result(t_input *input, t_result *result)
{
	t_list			*elem;
	t_output		*output;

	elem = *result->output_lst;
	while (elem)
	{
		output = (t_output *)elem->content;
		print_output(input, output);
		elem = elem->next;
	}
	return ;
}
