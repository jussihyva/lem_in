/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_ford_fulkerson_2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 14:55:23 by ubuntu            #+#    #+#             */
/*   Updated: 2020/04/01 20:04:01 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		add_room_to_path(t_list **path, t_room *room)
{
	t_list			*elem;

	elem = ft_lstnew(&room, sizeof(room));
	ft_lstadd(path, elem);
	return ;
}

static void		add_room_to_paths(t_list **lst_of_valid_paths, t_room *room,
															size_t num_of_paths)
{
	t_list			*elem;
	t_valid_path	*valid_path;

	elem = *lst_of_valid_paths;
	while (elem && num_of_paths)
	{
		num_of_paths--;
		elem = elem->next;
	}
	while (elem)
	{
		valid_path = *(t_valid_path **)elem->content;
		valid_path->num_of_conn_to_end++;
		add_room_to_path(valid_path->path, room);
		elem = elem->next;
	}
	return ;
}

static int		create_new_valid_path(t_list **lst_of_valid_paths, t_room *room)
{
	t_list			**path;
	t_valid_path	*valid_path;
	static int		id;
	t_list			*elem;

	path = (t_list **)ft_memalloc(sizeof(*path));
	valid_path = create_valid_path(path, valid);
	valid_path->num_of_conn_to_end++;
	add_room_to_path(valid_path->path, room);
	valid_path->id = id++;
	elem = ft_lstnew(&valid_path, sizeof(valid_path));
	ft_lstadd_e(lst_of_valid_paths, elem);
	return (1);
}

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

static int		get_next_room(t_list **lst_of_valid_paths, t_room *current_room,
										t_room *start_room, t_room *end_room)
{
	int				return_code;
	t_list			*connection_elem;
	t_room			*next_room;
	size_t			num_of_paths;

	num_of_paths = count_num_of_paths(lst_of_valid_paths);
	return_code = 0;
	current_room->is_visited = 1;
	if (current_room->num_of_conn_to_end == 1)
		return_code = create_new_valid_path(lst_of_valid_paths, end_room);
	else
	{
		connection_elem = current_room->connection_lst;
		while (connection_elem)
		{
			next_room = *(t_room **)connection_elem->content;
			if (!next_room->is_visited && next_room != start_room)
				return_code |= get_next_room(lst_of_valid_paths, next_room,
														start_room, end_room);
			connection_elem = connection_elem->next;
		}
	}
	if (return_code)
	{
		add_room_to_paths(lst_of_valid_paths, current_room, num_of_paths);
		current_room->is_visited = 0;
	}
	return (return_code);
}

int				algorithm_ford_fulkerson_2(t_output *output)
{
	t_room			*room;
	int				return_code;
	size_t			num_of_paths;

	num_of_paths = 0;
	room = output->start_room_ptr;
	if (get_next_room(output->lst_of_valid_paths, room, room,
														output->end_room_ptr))
		output->number_of_paths =
								count_num_of_paths(output->lst_of_valid_paths);
	return_code = put_ants_to_paths(output);
	return (return_code);
}
