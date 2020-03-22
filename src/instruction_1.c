/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pi <pi@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/22 18:32:40 by pi                #+#    #+#             */
/*   Updated: 2020/03/22 19:37:45 by pi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void					read_instruction_data(char *line, t_input *input,
													t_read_status *read_status)
{
	t_list			*elem;

	elem = ft_lstnew(line, sizeof(*line) * (ft_strlen(line) + 1));
	ft_lstadd(input->valid_input_lines, elem);
	if (*input->instruction_line_lst)
	{
		;
	}
	else
	{
		ft_printf("First line(%d): %s\n", *read_status, line);
	}
	return ;
}
