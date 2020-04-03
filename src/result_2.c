/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   result_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:21:57 by jkauppi           #+#    #+#             */
/*   Updated: 2020/04/03 12:15:59 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			add_line(t_list **instruction_line_lst, char *line)
{
	t_list			*elem;

	elem = ft_lstnew(line, sizeof(*line) * (ft_strlen(line) + 1));
	ft_lstadd_e(instruction_line_lst, elem);
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

void			print_ok(t_input *input)
{
	if (input->opt && input->opt & errors)
	{
		print_input_lines(input);
		ft_printf("OK: %d\n", input->error);
	}
	else
		ft_printf("OK\n");
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
