/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pi <pi@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/22 18:32:40 by pi                #+#    #+#             */
/*   Updated: 2020/03/26 09:58:55 by pi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int						validate_instructions(t_input *input)
{
	t_list					*instruction_line_elem;
	t_list					*elem;
	t_instruction_line		*instruction_line;
	t_ant					*ant;
	t_room					*room;
	int						result;

	result = 1;
	instruction_line_elem = *input->instruction_line_lst;
	while (instruction_line_elem && result)
	{
		instruction_line = (t_instruction_line *)instruction_line_elem->content;
		elem = *instruction_line->instruction_lst;
		while (elem && result)
		{
			ant = ((t_instruction *)elem->content)->ant;
			room = ((t_instruction *)elem->content)->room;
			if (!move_ant(ant, room))
				result = 0;
			elem = elem->next;
		}
		instruction_line_elem = instruction_line_elem->next;
	}
	return (result);
}

void					print_instruction(t_input *input)
{
	t_list					*instruction_line_elem;
	t_list					*elem;
	t_instruction_line		*instruction_line;
	char					*ant_name;
	char					*room_name;

	instruction_line_elem = *input->instruction_line_lst;
	while (instruction_line_elem)
	{
		instruction_line = (t_instruction_line *)instruction_line_elem->content;
		elem = *instruction_line->instruction_lst;
		while (elem)
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
									t_input *input, t_list **instruction_lst)
{
	t_list				*elem;
	char				**instruction_array;
	size_t				num_of_elem;
	int					result;
	t_instruction		instruction;

	instruction_array = ft_strsplit(instruction_string, '-');
	num_of_elem = 0;
	while (instruction_array[num_of_elem])
		num_of_elem++;
	if (num_of_elem == 2)
	{
		instruction.room = get_room(instruction_array[1], input);
		instruction.ant = get_ant(instruction_array[0], input);
		result = 1;
		elem = ft_lstnew(&instruction, sizeof(instruction));
		ft_lstadd_e(instruction_lst, elem);
	}
	else
		result = 0;
	return (result);
}

static void				split_instruction_line(char *line, t_input *input)
{
	t_list					*elem;
	char					**instruction_string_array;
	size_t					c;
	int						result;
	t_instruction_line		instruction_line;

	instruction_line.instruction_lst = (t_list **)ft_memalloc(sizeof(*instruction_line.instruction_lst));
	instruction_string_array = ft_strsplit(line, ' ');
	result = 1;
	c = -1;
	while (instruction_string_array[++c] && result)
		result = add_instruction(instruction_string_array[c], input,
											instruction_line.instruction_lst);
	if (*instruction_line.instruction_lst)
	{
		elem = ft_lstnew(&instruction_line, sizeof(instruction_line));
		ft_lstadd_e(input->instruction_line_lst, elem);
	}
	ft_arraydel(instruction_string_array);
	return ;
}

void					read_instruction_data(char *line, t_input *input)
{
	t_list					*elem;

	if (line[0] == '#')
		;
	else
	{
		elem = ft_lstnew(line, sizeof(*line) * (ft_strlen(line) + 1));
		ft_lstadd(input->valid_input_lines, elem);
		split_instruction_line(line, input);
	}
	return ;
}
