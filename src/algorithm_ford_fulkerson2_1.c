/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_ford_fulkerson2_1.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 14:55:23 by ubuntu            #+#    #+#             */
/*   Updated: 2020/04/03 16:46:27 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static size_t	count_num_of_paths(t_list **lst_of_valid_paths)
{
	size_t			num_of_paths;
	t_list			*elem;

	num_of_paths = 0;
	elem = *lst_of_valid_paths;
	while (elem)
	{
		num_of_paths++;
		elem = elem->next;
	}
	return (num_of_paths);
}

static int		get_next_room(t_output *output, t_room *current_room,
										t_room *start_room, t_room *end_room)
{
	int				return_code;
	t_list			*connection_elem;
	t_room			*next_room;
	size_t			num_of_paths;

	num_of_paths = count_num_of_paths(output->lst_of_valid_paths);
	return_code = 0;
	current_room->is_visited = 1;
	if (current_room->num_of_conn_to_end == 1)
		return_code = create_new_valid_path(output, end_room);
	else
	{
		connection_elem = current_room->connection_lst;
		while (connection_elem)
		{
			next_room = *(t_room **)connection_elem->content;
			if (!next_room->is_visited && next_room != start_room)
				return_code |= get_next_room(output, next_room,
														start_room, end_room);
			connection_elem = connection_elem->next;
		}
	}
	if (return_code)
		add_room_to_paths(output, current_room, start_room, num_of_paths);
	return (return_code);
}

static int		check_room_colision(size_t *current_room_vector,
									size_t *room_vector, size_t num_of_rooms)
{
	size_t			c;

	c = -1;
	while (++c < ((num_of_rooms / 32) + 1))
	{
		if (current_room_vector[c] & room_vector[c])
			return (1);
	}
	c = -1;
	while (++c < ((num_of_rooms / 32) + 1))
		current_room_vector[c] |= room_vector[c];
	return (0);
}

static t_list	**select_best_group_of_paths(t_output *output)
{
	t_list			**path_lst;
	t_list			*new_elem;
	t_valid_path	*valid_path;
	size_t			*current_room_vector;
	size_t			c;

	current_room_vector = (size_t *)ft_memalloc(sizeof(*current_room_vector) *
											((output->num_of_rooms / 32) + 1));
	path_lst = (t_list **)ft_memalloc(sizeof(*path_lst));
	c = -1;
	while (++c < output->number_of_paths)
	{
		valid_path = output->valid_paths[c];
		if (!check_room_colision(current_room_vector, valid_path->room_vector,
														output->num_of_rooms))
		{
			new_elem = ft_lstnew(&valid_path, sizeof(valid_path));
			ft_lstadd_e(path_lst, new_elem);
		}
	}
	free(current_room_vector);
	return (path_lst);
}

int				algorithm_ford_fulkerson2(t_output *output)
{
	t_room			*room;
	int				return_code;

	room = output->start_room_ptr;
	if (get_next_room(output, room, room, output->end_room_ptr))
	{
		output->number_of_paths =
								count_num_of_paths(output->lst_of_valid_paths);
		output->valid_paths =
					(t_valid_path **)ft_memalloc(sizeof(*output->valid_paths) *
													output->number_of_paths);
		sort_valid_paths(output->lst_of_valid_paths, output->valid_paths);
		output->lst_of_selectd_paths = select_best_group_of_paths(output);
		output->number_of_paths =
							count_num_of_paths(output->lst_of_selectd_paths);
	}
	return_code = put_ants_to_paths(output);
	return (return_code);
}
