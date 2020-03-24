/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pi <pi@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/22 18:32:40 by pi                #+#    #+#             */
/*   Updated: 2020/03/24 08:35:25 by pi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int				add_instruction(char *instruction_string,
																t_input *input)
{
	char		**instruction_array;
	size_t		num_of_elem;
	int			result;
	t_room		*room;
	t_ant		*ant;

	instruction_array = ft_strsplit(instruction_string, '-');
	num_of_elem = 0;
	while (instruction_array[num_of_elem])
		num_of_elem++;
	if (num_of_elem == 2)
	{
		room = get_room(instruction_array[1], input);
		ant = get_ant(instruction_array[0], input);
		ft_printf(" %10s", instruction_string);
		ft_printf("(%p)", ant);
		result = 1;
	}
	else
		result = 0;
	return (result);
}

static int				split_instruction_line(char *line, t_input *input)
{
	char		**instruction_string_array;
	size_t		c;
	int			result;

	instruction_string_array = ft_strsplit(line, ' ');
	result = 1;
	c = -1;
	while (instruction_string_array[++c] && result)
		result = add_instruction(instruction_string_array[c], input);
	ft_printf("\n");
	ft_arraydel(instruction_string_array);
	return (result);
}

void					read_instruction_data(char *line, t_input *input)
{
	t_list					*elem;
	t_instruction_line		*instruction_line;

	if (line[0] == '#')
		;
	else
	{
		elem = ft_lstnew(line, sizeof(*line) * (ft_strlen(line) + 1));
		ft_lstadd(input->valid_input_lines, elem);
		instruction_line =
				(t_instruction_line *)ft_memalloc(sizeof(*instruction_line));
		if (split_instruction_line(line, input))
		{
			elem = ft_lstnew(&instruction_line, sizeof(instruction_line));
			ft_lstadd(input->instruction_line_lst, elem);
		}
	}
	return ;
}
