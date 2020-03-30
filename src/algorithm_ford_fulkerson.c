/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_ford_fulkerson.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 05:53:21 by ubuntu            #+#    #+#             */
/*   Updated: 2020/03/30 11:03:03 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

// static int	get_next_room(t_room *current_room, t_room *start_room,
// 															t_room *end_room)
// {
// 	int				return_code;
// 	t_list			*connection_elem;

// 	connection_elem = room->connection_lst;
// 	while (connection_elem && room != output->end_room_ptr)
// 	{
// 	}
// }

int			algorithm_ford_fulkerson(t_output *output)
{
	t_list			*connection_elem;
	t_list			*elem;
	t_room			*room;
	t_valid_path	*valid_path;
	t_list			**path;
	t_validity		validity;
	int				return_code;

	path = (t_list **)ft_memalloc(sizeof(*path));
	room = output->start_room_ptr;
	ft_printf("%20s\n", room->name);
	elem = ft_lstnew(&room, sizeof(room));
	ft_lstadd_e(path, elem);
	connection_elem = room->connection_lst;
	while (connection_elem && room != output->end_room_ptr)
	{
		room = *(t_room **)connection_elem->content;
		if (room->is_visited || room == output->start_room_ptr)
			connection_elem = connection_elem->next;
		else
		{
			ft_printf("%20s\n", room->name);
			elem = ft_lstnew(&room, sizeof(room));
			ft_lstadd_e(path, elem);
			if (room != output->end_room_ptr)
				room->is_visited = 1;
			connection_elem = room->connection_lst;
		}
	}
	validity = valid;
	valid_path =create_valid_path(path, validity);
	elem = ft_lstnew(&valid_path, sizeof(valid_path));
	ft_lstadd(output->lst_of_valid_paths, elem);
	output->number_of_paths++;
	if (output->number_of_paths)
	{
		put_ants_to_paths(output);
		return_code = 1;
	}
	else
		return_code = 0;
	return (return_code);
}
