/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/22 18:32:40 by pi                #+#    #+#             */
/*   Updated: 2020/04/03 12:45:58 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_input_error	create_instruction(char **instruction_array,
					t_input *input, t_output *output, t_list **instruction_lst)
{
	t_list				*elem;
	t_input_error		validity_result;
	t_instruction		instruction;

	instruction.room = get_room(instruction_array[1], input);
	instruction.ant = get_ant(instruction_array[0], output);
	if (instruction.room && instruction.ant)
	{
		validity_result = 0;
		elem = ft_lstnew(&instruction, sizeof(instruction));
		ft_lstadd_e(instruction_lst, elem);
	}
	else
		validity_result = invalid_instruction_line;
	return (validity_result);
}

static t_input_error	add_instruction(char *instruction_string,
					t_input *input, t_output *output, t_list **instruction_lst)
{
	char				**instruction_array;
	size_t				num_of_elem;
	t_input_error		validity_result;

	instruction_array = ft_strsplit(instruction_string, '-');
	num_of_elem = 0;
	while (instruction_array[num_of_elem])
		num_of_elem++;
	if (num_of_elem == 2)
		validity_result = create_instruction(instruction_array, input, output,
															instruction_lst);
	else
		validity_result = invalid_instruction_line;
	ft_arraydel(instruction_array);
	return (validity_result);
}

static void				split_instruction_line(char *line, t_input *input,
															t_output *output)
{
	t_list					*elem;
	char					**instruction_string_array;
	size_t					c;
	t_instruction_line		instruction_line;

	instruction_line.instruction_lst =
			(t_list **)ft_memalloc(sizeof(*instruction_line.instruction_lst));
	instruction_string_array = ft_strsplit(line, ' ');
	input->error = 0;
	c = -1;
	while (instruction_string_array[++c] && !input->error)
		input->error = add_instruction(instruction_string_array[c], input,
									output, instruction_line.instruction_lst);
	if (*instruction_line.instruction_lst)
	{
		elem = ft_lstnew(&instruction_line, sizeof(instruction_line));
		ft_lstadd_e(input->instruction_line_lst, elem);
	}
	ft_arraydel(instruction_string_array);
	return ;
}

void					read_instruction_data(char *line, t_input *input,
															t_output **output)
{
	t_list					*elem;

	if (!*output)
		*output = initialize_output(input);
	if (line[0] == '#')
		;
	else
	{
		elem = ft_lstnew(line, sizeof(*line) * (ft_strlen(line) + 1));
		ft_lstadd(input->valid_input_lines, elem);
		split_instruction_line(line, input, *output);
	}
	return ;
}
