/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pi <pi@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/22 18:32:40 by pi                #+#    #+#             */
/*   Updated: 2020/03/24 10:11:37 by pi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int				add_instruction(char *instruction_string,
									t_input *input, t_list **instruction_lst)
{
	t_list				*elem;
	char				**instruction_array;
	size_t				num_of_elem;
	int					result;
	t_instruction		instruction;

	(void)instruction_lst;
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

static int				split_instruction_line(char *line, t_input *input)
{
	t_list					*elem;
	char					**instruction_string_array;
	size_t					c;
	int						result;
	t_list					*instruction_lst;
	char					*ant_name;
	char					*room_name;

	instruction_lst = NULL;
	instruction_string_array = ft_strsplit(line, ' ');
	result = 1;
	c = -1;
	while (instruction_string_array[++c] && result)
		result = add_instruction(instruction_string_array[c], input,
															&instruction_lst);
	if (instruction_lst)
	{
		elem = instruction_lst;
		while (elem)
		{
			ant_name = ((t_instruction *)elem->content)->ant->name;
			room_name = ((t_instruction *)elem->content)->room->name;
			ft_printf("%5s-%-3s", ant_name, room_name);
			elem = elem->next;
		}
		ft_printf("\n");
		elem = ft_lstnew(instruction_lst, sizeof(*instruction_lst));
		ft_lstadd(input->instruction_line_lst, elem);
	}
	ft_arraydel(instruction_string_array);
	return (result);
}

void					read_instruction_data(char *line, t_input *input)
{
	t_list					*elem;
//	t_list					*instruction_lst;
	t_instruction_line		*instruction_line;
	// char					*ant_name;
	// char					*room_name;

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
	// instruction_lst = *input->instruction_line_lst;
	// if (instruction_lst)
	// {
	// 	elem = instruction_lst;
	// 	while (elem)
	// 	{
	// 		ant_name = ((t_instruction *)elem->content)->ant->name;
	// 		room_name = ((t_instruction *)elem->content)->room->name;
	// 		ft_printf("%5s-%-3s", ant_name, room_name);
	// 		elem = elem->next;
	// 	}
	// 	ft_printf("\n");
	// 	elem = ft_lstnew(instruction_lst, sizeof(*instruction_lst));
	// 	ft_lstadd(input->instruction_line_lst, elem);
	// }
	return ;
}
