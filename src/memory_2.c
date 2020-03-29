/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/28 11:24:35 by ubuntu            #+#    #+#             */
/*   Updated: 2020/03/29 06:07:57 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		del_input(void *elem, size_t size)
{
	t_instruction_line	*instruction_line;

	(void)size;
	instruction_line = (t_instruction_line *)elem;
	ft_lstdel(instruction_line->instruction_lst, del_path);
	free(instruction_line->instruction_lst);
	free(elem);
	return ;
}

static void		release_room_array(t_input *input)
{
	size_t		c;

	c = -1;
	if (input->room_array)
	{
		while (++c < input->num_of_rooms)
		{
			ft_strdel(&input->room_array[c]->name);
			ft_lstdel(&input->room_array[c]->connection_lst, del_path);
			free(input->room_array[c]);
		}
		free(input->room_array);
	}
	return ;
}

void			release_input(t_input *input)
{
	size_t		c;

	ft_lstdel(input->algorithm_lst, del_path);
	free(input->algorithm_lst);
	ft_lstdel(input->valid_input_lines, del_path);
	free(input->valid_input_lines);
	ft_lstdel(input->instruction_line_lst, del_input);
	free(input->instruction_line_lst);
	c = -1;
	if (input->ant_array)
	{
		while (++c < input->number_of_ants)
		{
			ft_strdel(&input->ant_array[c]->name);
			free(input->ant_array[c]);
		}
		free(input->ant_array);
	}
	release_room_array(input);
	free(input->input_file);
	return ;
}
