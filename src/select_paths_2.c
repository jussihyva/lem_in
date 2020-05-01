/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_paths_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/18 06:36:34 by pi                #+#    #+#             */
/*   Updated: 2020/05/01 19:09:12 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

size_t					count_max_num_of_paths(t_output *output)
{
	size_t			max_num_of_paths;

	max_num_of_paths = output->number_of_ants;
	if (output->start_room_ptr->num_of_connections < max_num_of_paths)
		max_num_of_paths = output->start_room_ptr->num_of_connections;
	if (output->end_room_ptr->num_of_connections < max_num_of_paths)
		max_num_of_paths = output->end_room_ptr->num_of_connections;
	return (max_num_of_paths);
}

static t_valid_path		*find_shortest_path(t_output *output, int offset)
{
	t_valid_path	*valid_path;
	t_list			**path;
	t_list			*adj_room_elem;
	t_validity		validity;

	path = (t_list **)ft_memalloc(sizeof(*path));
	ft_lstadd_e(path, ft_lstnew(&output->start_room_ptr,
											sizeof(output->start_room_ptr)));
	adj_room_elem = output->start_room_ptr->connection_lst;
	output->start_room_ptr->is_visited = 1;
	validity = add_rooms_to_path(output, path, offset);
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

void					preliminary_path_selection(t_output *output,
										size_t max_num_of_paths, int *offset)
{
	t_valid_path	*valid_path;

	while (output->number_of_paths < max_num_of_paths)
	{
		valid_path = find_shortest_path(output, *offset);
		if (valid_path)
		{
			output->number_of_paths++;
			valid_path->id = output->number_of_paths;
			ft_lstadd(output->lst_of_valid_paths, ft_lstnew(&valid_path,
														sizeof(valid_path)));
		}
		else
			break ;
	}
	return ;
}

void					finalize_path_selection(t_output *output, int *offset)
{
	t_list			*elem;
	t_list			*tmp_elem;
	t_valid_path	*valid_path;

	while (--(*offset) >= -1)
	{
		elem = *(t_list **)output->lst_of_valid_paths;
		while (elem)
		{
			tmp_elem = elem->next;
			valid_path = *(t_valid_path **)elem->content;
			if (valid_path->validity == many)
			{
				valid_path->validity = add_rooms_to_path(output,
												valid_path->room_lst, *offset);
				if (valid_path->validity == no_room)
					delete_valid_path(output, elem);
				else
					update_valid_path(valid_path);
			}
			elem = tmp_elem;
		}
	}
}
