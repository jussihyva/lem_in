/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_paths_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pi <pi@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 10:16:44 by jkauppi           #+#    #+#             */
/*   Updated: 2020/03/18 07:58:06 by pi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void				update_best_room(t_room **next_room, t_room **best_room,
											t_validity *validity, size_t offset)
{
	if ((*next_room)->num_of_conn_to_end < (*best_room)->num_of_conn_to_end)
	{
		*best_room = *next_room;
		if (((*next_room)->num_of_conn_to_end + 1) <
											(*best_room)->num_of_conn_to_end)
			*validity = valid_room;
	}
	else if (((*next_room)->num_of_conn_to_end <=
									(*best_room)->num_of_conn_to_end + offset - 1 &&
									(*next_room)->num_of_conn_to_start != 1))
		*validity = many_alternatives;
	return ;
}

static t_room			*get_next_best_room(t_list *adj_room_elem,
					t_room *end_room_ptr, t_validity *validity, size_t offset)
{
	t_room		*best_room;
	t_room		*next_room;
	size_t		num_of_conn_to_start;

	next_room = *(t_room **)adj_room_elem->content;
	num_of_conn_to_start = next_room->num_of_conn_to_start;
	best_room = NULL;
	*validity = no_room;
	while (adj_room_elem)
	{
		next_room = *(t_room **)adj_room_elem->content;
		if ((next_room == end_room_ptr) || (next_room->num_of_conn_to_end &&
														!next_room->is_visited))
		{
			if (best_room)
				update_best_room(&next_room, &best_room, validity, offset);
			else
			{
				best_room = next_room;
				*validity = valid_room;
			}
		}
		adj_room_elem = adj_room_elem->next;
	}
	return (best_room);
}

static t_validity		create_path(t_input *input, t_list **path,
										t_list *adj_room_elem, size_t offset)
{
	t_room			*best_room;
	t_validity		validity;

	while (1 == 1)
	{
		validity = no_room;
		best_room = get_next_best_room(adj_room_elem, input->end_room_ptr,
															&validity, offset);
		if ((validity == valid_room) ||
									(!offset && validity == many_alternatives))
		{
			validity = valid_room;
			best_room->is_visited = 1;
			ft_lstadd_e(path, ft_lstnew(&best_room, sizeof(best_room)));
			if (best_room == input->end_room_ptr)
				break ;
			adj_room_elem = best_room->connection_lst;
		}
		else
			break ;
	}
	return (validity);
}

static t_valid_path		*find_shortest_path(t_input *input, size_t offset)
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
	validity = create_path(input, path, adj_room_elem, offset);
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

int						select_paths(t_input *input, t_report *report)
{
	t_valid_path	*valid_path;
	size_t			max_num_of_paths;
	t_list			*elem;
	t_list			*tmp_elem;
	t_list			*path_elem;
	t_list			*adj_room_elem;
	t_validity		validity;
	size_t			offset;

	max_num_of_paths = count_max_num_of_paths(input);
	report->number_of_paths = 0;
	offset = 2;
	while (report->number_of_paths < max_num_of_paths)
	{
		valid_path = find_shortest_path(input, offset);
		if (valid_path)
		{
			ft_lstadd(report->lst_of_valid_paths, ft_lstnew(&valid_path,
															sizeof(valid_path)));
			report->number_of_paths++;
			print_path(report);
		}
	}
	elem = *(t_list **)report->lst_of_valid_paths;
	while (elem)
	{
		valid_path = *(t_valid_path **)elem->content;
		if (valid_path->validity == many_alternatives)
		{
			tmp_elem = elem->next;
			path_elem = *valid_path->path;
			while (path_elem->next)
				path_elem = path_elem->next;
			adj_room_elem = (*(t_room **)path_elem->content)->connection_lst;
			validity = create_path(input, valid_path->path, adj_room_elem, 0);
			if (validity == no_room)
				delete_valid_path(report, elem);
			else
				update_valid_path(valid_path);
			elem = tmp_elem;
		}
		else
			elem = elem->next;
	}
	if (report->number_of_paths)
		put_ants_to_paths(report);
	else
	{
		input->error = no_path_available;
		return (0);
	}
	return (1);
}
