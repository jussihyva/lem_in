/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_ford_fulkerson2_2.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/03 13:01:45 by ubuntu            #+#    #+#             */
/*   Updated: 2020/05/26 13:15:49 by ubuntu           ###   ########.fr       */
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

void			add_room_to_paths(t_output *output, t_room *room,
										t_room *start_room, size_t num_of_paths)
{
	t_list			*elem;
	t_valid_path	*valid_path;

	elem = *output->lst_of_valid_paths;
	while (elem && num_of_paths)
	{
		num_of_paths--;
		elem = elem->next;
	}
	while (elem)
	{
		valid_path = *(t_valid_path **)elem->content;
		valid_path->num_of_conn_to_end++;
		if (room != start_room)
			valid_path->room_vector[room->id / VECTOR_BITS] |= 1 <<
													(room->id % VECTOR_BITS);
		add_room_to_path(valid_path->room_lst, room);
		elem = elem->next;
	}
	room->is_visited = 0;
	return ;
}

int				create_new_valid_path(t_output *output, t_room *room)
{
	t_list			**path;
	t_valid_path	*valid_path;
	static int		id;
	t_list			*elem;

	path = (t_list **)ft_memalloc(sizeof(*path));
	valid_path = create_valid_path(path, valid);
	valid_path->num_of_conn_to_end++;
	add_room_to_path(valid_path->room_lst, room);
	valid_path->id = id++;
	valid_path->room_vector =
					(size_t *)ft_memalloc(sizeof(*valid_path->room_vector) *
									((output->num_of_rooms / VECTOR_BITS) + 1));
	elem = ft_lstnew(&valid_path, sizeof(valid_path));
	ft_lstadd_e(output->lst_of_valid_paths, elem);
	return (1);
}

static void		add_path(t_valid_path **valid_paths, t_valid_path *valid_path)
{
	size_t			c;
	t_valid_path	*tmp_valid_path;

	c = 0;
	while (1)
	{
		if (valid_paths[c])
		{
			if (valid_paths[c]->num_of_conn_to_end >
												valid_path->num_of_conn_to_end)
			{
				tmp_valid_path = valid_paths[c];
				valid_paths[c] = valid_path;
				valid_path = tmp_valid_path;
			}
		}
		else
		{
			valid_paths[c] = valid_path;
			break ;
		}
		c++;
	}
	return ;
}

void			sort_valid_paths(t_list **lst_of_valid_paths,
													t_valid_path **valid_paths)
{
	t_list			*elem;
	t_valid_path	*valid_path;

	elem = *lst_of_valid_paths;
	while (elem)
	{
		valid_path = *(t_valid_path **)elem->content;
		add_path(valid_paths, valid_path);
		elem = elem->next;
	}
	return ;
}
