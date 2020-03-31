/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/22 18:32:40 by pi                #+#    #+#             */
/*   Updated: 2020/03/31 14:30:59 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int						validate_instructions(t_output *output)
{
	t_list					*instruction_line_elem;
	t_list					*elem;
	t_instruction_line		*instruction_line;
	t_instruction			*instruction;
	int						result;

	result = 1;
	instruction_line_elem = *output->instruction_line_lst;
	while (instruction_line_elem && result)
	{
		instruction_line = (t_instruction_line *)instruction_line_elem->content;
		elem = *instruction_line->instruction_lst;
		while (elem && result)
		{
			instruction = (t_instruction *)elem->content;
			ft_printf("ANT: %s-%s  ", instruction->ant->name, instruction->room->name);
			if (!move_ant(instruction))
			{
				ft_printf("ANT: %s\n", instruction->ant->name);
				result = 0;
			}
			else
				ft_printf("\n");
			elem = elem->next;
		}
		instruction_line_elem = instruction_line_elem->next;
	}
	return (result);
}

void					print_instruction(t_output *output)
{
	t_list					*instruction_line_elem;
	t_list					*elem;
	t_instruction_line		*instruction_line;
	char					*ant_name;
	char					*room_name;

	instruction_line_elem = *output->instruction_line_lst;
	while (instruction_line_elem)
	{
		instruction_line = (t_instruction_line *)instruction_line_elem->content;
		elem = *instruction_line->instruction_lst;
		while (elem && ((t_instruction *)elem->content)->ant &&
										((t_instruction *)elem->content)->room)
		{
			ant_name = ((t_instruction *)elem->content)->ant->name;
			room_name = ((t_instruction *)elem->content)->room->name;
			ft_printf("%5s-%-3s", ant_name, room_name);
			elem = elem->next;
		}
		ft_printf("\n");
		instruction_line_elem = instruction_line_elem->next;
	}
	return ;
}

static int				add_instruction(char *instruction_string,
					t_input *input, t_output *output, t_list **instruction_lst)
{
	t_list				*elem;
	char				**instruction_array;
	size_t				num_of_elem;
	int					validity_result;
	t_instruction		instruction;

	instruction_array = ft_strsplit(instruction_string, '-');
	num_of_elem = 0;
	while (instruction_array[num_of_elem])
		num_of_elem++;
	if (num_of_elem == 2)
	{
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
	}
	else
		validity_result = invalid_instruction_line;
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
		input->error = add_instruction(instruction_string_array[c], input, output,
											instruction_line.instruction_lst);
	if (*instruction_line.instruction_lst)
	{
		elem = ft_lstnew(&instruction_line, sizeof(instruction_line));
		ft_lstadd_e(input->instruction_line_lst, elem);
	}
	ft_arraydel(instruction_string_array);
	return ;
}

void					read_instruction_data(char *line, t_input *input,
															t_output *output)
{
	t_list					*elem;

	if (line[0] == '#')
		;
	else
	{
		elem = ft_lstnew(line, sizeof(*line) * (ft_strlen(line) + 1));
		ft_lstadd(input->valid_input_lines, elem);
		split_instruction_line(line, input, output);
	}
	return ;
}
