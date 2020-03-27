/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pi <pi@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 15:25:14 by jkauppi           #+#    #+#             */
/*   Updated: 2020/03/23 09:15:25 by pi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			del_path(void *room, size_t size)
{
	(void)size;
	free(room);
	room = NULL;
	return ;
}

void			del_report(void *elem, size_t size)
{
	t_valid_path	*valid_path;

	(void)size;
	valid_path = *(t_valid_path **)elem;
	ft_lstdel(valid_path->path, del_path);
	free(valid_path->path);
	free(valid_path);
	free(elem);
	return ;
}

void			del_input(void *elem, size_t size)
{
	t_instruction_line	*instruction_line;

	(void)size;
	instruction_line = (t_instruction_line *)elem;
	ft_lstdel(instruction_line->instruction_lst, del_path);
	free(instruction_line->instruction_lst);
	free(elem);
	return ;
}

void			release_report(t_report *report)
{
	size_t		c;

	ft_lstdel(report->lst_of_valid_paths, del_report);
	free(report->lst_of_valid_paths);
	report->lst_of_valid_paths = NULL;
	c = -1;
	while (++c < report->number_of_ants)
	{
		ft_strdel(&report->ant_array[c]->name);
		free(report->ant_array[c]);
	}
	free(report->ant_array);
	report->ant_array = NULL;
	free(report);
	report = NULL;
	return ;
}

void			release_input(t_input *input)
{
	size_t		c;

	ft_lstdel(input->valid_input_lines, del_path);
	free(input->valid_input_lines);
	input->valid_input_lines = NULL;
	ft_lstdel(input->instruction_line_lst, del_input);
	free(input->instruction_line_lst);
	input->instruction_line_lst = NULL;
	c = -1;
	while (++c < input->number_of_ants)
	{
		ft_strdel(&input->ant_array[c]->name);
		free(input->ant_array[c]);
	}
	free(input->ant_array);
	input->ant_array = NULL;
	c = -1;
	while (++c < input->num_of_rooms)
	{
		ft_strdel(&input->room_array[c]->name);
		ft_lstdel(&input->room_array[c]->connection_lst, del_path);
		free(input->room_array[c]);
	}
	free(input->input_file);
	input->input_file = NULL;
	free(input->room_array);
	input->room_array = NULL;
	return ;
}
