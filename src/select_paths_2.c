/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_paths_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pi <pi@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/18 06:36:34 by pi                #+#    #+#             */
/*   Updated: 2020/03/18 17:17:13 by pi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

size_t					count_max_num_of_paths(t_input *input)
{
	size_t			num_of_paths;
	size_t			max_num_of_paths;
	t_list			*elem;

	if ((max_num_of_paths = input->number_of_ants))
	{
		elem = input->start_room_ptr->connection_lst;
		num_of_paths = 0;
		while (elem)
		{
			num_of_paths++;
			elem = elem->next;
		}
		if (num_of_paths < max_num_of_paths)
			max_num_of_paths = num_of_paths;
		elem = input->end_room_ptr->connection_lst;
		num_of_paths = 0;
		while (elem)
		{
			num_of_paths++;
			elem = elem->next;
		}
		if (num_of_paths < max_num_of_paths)
			max_num_of_paths = num_of_paths;
	}
	else
		input->error = num_of_ants_error;
	return (max_num_of_paths);
}

static t_valid_path		*find_shortest_path(t_input *input, int offset)
{
	t_valid_path	*valid_path;
	t_list			**path;
	t_list			*adj_room_elem;
	t_validity		validity;

	path = (t_list **)ft_memalloc(sizeof(*path));
	ft_lstadd_e(path, ft_lstnew(&input->start_room_ptr,
											sizeof(input->start_room_ptr)));
	adj_room_elem = input->start_room_ptr->connection_lst;
	input->start_room_ptr->is_visited = 1;
	validity = add_rooms_to_path(input, path, offset);
	if (validity != no_room)
		valid_path = create_valid_path(path, validity);
	else
	{
		valid_path = NULL;
		ft_lstdel_1(path);
		free(path);
	}
	return (valid_path);
}

void					preliminary_path_selection(t_input *input,
						t_report *report, size_t max_num_of_paths, int *offset)
{
	t_valid_path	*valid_path;

	while (report->number_of_paths < max_num_of_paths)
	{
		valid_path = find_shortest_path(input, *offset);
		if (valid_path)
		{
			report->number_of_paths++;
			valid_path->id = report->number_of_paths;
			ft_lstadd(report->lst_of_valid_paths, ft_lstnew(&valid_path,
															sizeof(valid_path)));
			if (report->opt && report->opt & verbose)
				print_path(report);
		}
		else
			break ;
	}
	return ;
}
