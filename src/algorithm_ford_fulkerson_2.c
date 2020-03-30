/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_ford_fulkerson_2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 14:55:23 by ubuntu            #+#    #+#             */
/*   Updated: 2020/03/30 17:25:38 by ubuntu           ###   ########.fr       */
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

static void		add_room_to_paths(t_list **lst_of_valid_paths, t_room *room)
{
	t_list			*elem;
	t_valid_path	*valid_path;

	elem = *lst_of_valid_paths;
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
	t_list			*elem;

	path = (t_list **)ft_memalloc(sizeof(*path));
	valid_path = create_valid_path(path, valid);
	elem = ft_lstnew(&valid_path, sizeof(valid_path));
	ft_lstadd(lst_of_valid_paths, elem);
	add_room_to_paths(lst_of_valid_paths, room);
	return (1);
}

static int		get_next_room(t_list **lst_of_valid_paths, t_room *current_room,
										t_room *start_room, t_room *end_room)
{
	int				return_code;
	t_list			*connection_elem;
	t_room			*next_room;

	return_code = 0;
	current_room->is_visited = 1;
	connection_elem = current_room->connection_lst;
	next_room = NULL;
	while (connection_elem && !return_code)
	{
		next_room = *(t_room **)connection_elem->content;
		if (next_room == end_room)
		{
			return_code = create_new_valid_path(lst_of_valid_paths, next_room);
		}
		else if (!next_room->is_visited && next_room != start_room)
		{
			if ((return_code = get_next_room(lst_of_valid_paths, next_room,
														start_room, end_room)))
				add_room_to_paths(lst_of_valid_paths, next_room);
		}
		connection_elem = connection_elem->next;
	}
	return (return_code);
}

int				algorithm_ford_fulkerson_2(t_output *output)
{
	t_room			*room;
	int				return_code;

	room = output->start_room_ptr;
	if (get_next_room(output->lst_of_valid_paths, room, room,
														output->end_room_ptr))
	{
		add_room_to_paths(output->lst_of_valid_paths, room);
		output->number_of_paths++;
	}
	return_code = put_ants_to_paths(output);
	return (return_code);
}
