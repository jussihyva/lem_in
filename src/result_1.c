/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   result_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 09:28:18 by jkauppi           #+#    #+#             */
/*   Updated: 2020/03/09 20:39:36 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		print_room_data(t_room *room)
{
	t_list		*elem;

	ft_printf("Room: %10d %5d %20s %5d %5d\n",
	room->id, room->num_of_conn_to_end, room->name, room->coord_x,
																room->coord_y);
	elem = room->connection_lst;
	while (elem)
	{
		ft_printf("%65s %5d\n", (*(t_room **)elem->content)->name,
							(*(t_room **)elem->content)->num_of_conn_to_end);
		elem = elem->next;
	}
	return ;
}

void			print_line(t_input *input, char *line, int add_line)
{
	t_list			*elem;
	char			*mod_line;

	if (add_line)
	{
		if (add_line == 1)
		{
			elem = ft_lstnew(line, sizeof(*line) * (ft_strlen(line) + 1));
			ft_lstadd(input->valid_input_lines, elem);
		}
		else
		{
			mod_line = (char *)ft_memalloc(sizeof(*mod_line) * 100);
			ft_sprintf(mod_line, "%s %d %d",
							(*((t_room **)input->room_lst->content))->name,
							(*((t_room **)input->room_lst->content))->coord_x,
							(*((t_room **)input->room_lst->content))->coord_y);
			elem = ft_lstnew(mod_line, sizeof(*mod_line) *
													(ft_strlen(mod_line) + 1));
			ft_lstadd(input->valid_input_lines, elem);
			ft_strdel(&mod_line);
		}
	}
	return ;
}

static void		print_path(t_report *report)
{
	t_list			*elem;
	t_list			*valid_path_elem;
	t_valid_path	*valid_path;
	t_list			**path_lst;

	path_lst = ((t_list *)report->lst_of_valid_paths)->content;
	valid_path_elem = *report->lst_of_valid_paths;
	while (valid_path_elem)
	{
		valid_path = *(t_valid_path **)valid_path_elem->content;
		elem = *valid_path->path;
		ft_printf("#path: ");
		while (elem)
		{
			ft_printf(" %10s", (*(t_room **)elem->content)->name);
			elem = elem->next;
		}
		ft_printf("\n");
		valid_path_elem = valid_path_elem->next;
	}
	return ;
}

t_report		*initialize_report(t_input *input)
{
	t_report		*report;

	report = (t_report *)ft_memalloc(sizeof(*report));
	report->error = 0;
	report->opt = input->opt;
	report->lst_of_valid_paths =
				(t_list **)ft_memalloc(sizeof(*report->lst_of_valid_paths));
	report->ant_array = (t_ant *)ft_memalloc(sizeof(*report->ant_array) *
														input->number_of_ants);
	report->number_of_ants = input->number_of_ants;
	report->end_room_ptr = input->end_room_ptr;
	return (report);
}

void			print_result(t_input *input, t_report *report)
{
	size_t		c;
	t_room		**room;
	t_list		*elem;

	room = input->room_array;
	if (input->opt & verbose)
	{
		c = -1;
		while (room[++c])
			print_room_data(room[c]);
	}
	elem = *input->valid_input_lines;
	while (elem->next)
		elem = elem->next;
	while (elem)
	{
		ft_printf("%s\n", (char *)elem->content);
		elem = elem->prev;
	}
	print_path(report);
	print_instructions(report);
	return ;
}