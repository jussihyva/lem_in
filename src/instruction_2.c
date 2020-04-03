/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/03 12:45:04 by ubuntu            #+#    #+#             */
/*   Updated: 2020/04/03 12:46:23 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int				faulty_instruction(t_input *input,
													t_instruction *instruction)
{
	char			*instruction_str;

	instruction_str = ft_strjoin(instruction->ant->name, "-");
	instruction_str = ft_strjoin(instruction_str, instruction->room->name);
	set_error(input, instruction_str, incorrect_move, "#ERROR ");
	ft_strdel(&instruction_str);
	return (0);
}

int						validate_instructions(t_input *input)
{
	t_list					*instruction_line_elem;
	t_list					*elem;
	t_instruction_line		*instruction_line;
	t_instruction			*instruction;
	int						result;

	result = 1;
	instruction_line_elem = *input->instruction_line_lst;
	while (instruction_line_elem && result)
	{
		instruction_line = (t_instruction_line *)instruction_line_elem->content;
		elem = *instruction_line->instruction_lst;
		while (elem && result)
		{
			instruction = (t_instruction *)elem->content;
			if (!move_ant(instruction, input->end_room_ptr))
				result = faulty_instruction(input, instruction);
			elem = elem->next;
		}
		instruction_line_elem = instruction_line_elem->next;
	}
	return (result);
}
