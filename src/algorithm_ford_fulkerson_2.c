/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_ford_fulkerson_2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 14:55:23 by ubuntu            #+#    #+#             */
/*   Updated: 2020/03/30 14:56:05 by ubuntu           ###   ########.fr       */
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

static int		get_next_room(t_list **path, t_room *current_room,
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
			add_room_to_path(path, next_room);
			return_code = 1;
		}
		else if (!next_room->is_visited && next_room != start_room)
		{
			if ((return_code = get_next_room(path, next_room, start_room,
																	end_room)))
				add_room_to_path(path, next_room);
		}
		connection_elem = connection_elem->next;
	}
	return (return_code);
}

int				algorithm_ford_fulkerson_2(t_output *output)
{
	t_list			*elem;
	t_room			*room;
	t_valid_path	*valid_path;
	t_list			**path;
	int				return_code;

	room = output->start_room_ptr;
	path = (t_list **)ft_memalloc(sizeof(*path));
	while (get_next_room(path, room, room, output->end_room_ptr))
	{
		elem = ft_lstnew(&room, sizeof(room));
		ft_lstadd(path, elem);
		valid_path = create_valid_path(path, valid);
		elem = ft_lstnew(&valid_path, sizeof(valid_path));
		ft_lstadd(output->lst_of_valid_paths, elem);
		output->number_of_paths++;
		path = (t_list **)ft_memalloc(sizeof(*path));
	}
	free(path);
	return_code = put_ants_to_paths(output);
	return (return_code);
}
