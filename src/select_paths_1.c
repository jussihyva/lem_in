/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_paths_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pi <pi@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 10:16:44 by jkauppi           #+#    #+#             */
/*   Updated: 2020/03/27 08:47:59 by pi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void				update_best_room(t_room **next_room, t_room **best_room,
											t_validity *validity, int offset)
{
	if ((*next_room)->num_of_conn_to_end < (*best_room)->num_of_conn_to_end)
	{
		*best_room = *next_room;
		if (((*next_room)->num_of_conn_to_end + 1) <
											(*best_room)->num_of_conn_to_end)
			*validity = valid_room;
	}
	else if (((*next_room)->num_of_conn_to_end <=
									(*best_room)->num_of_conn_to_end + offset &&
									(*next_room)->num_of_conn_to_start != 1))
		*validity = many;
	return ;
}

static t_room			*get_next_best_room(t_list *adj_room_elem,
					t_room *end_room_ptr, t_validity *validity, int offset)
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

t_validity				add_rooms_to_path(t_input *input, t_list **path,
																	int offset)
{
	t_room			*best_room;
	t_validity		validity;
	t_list			*path_elem;
	t_list			*adj_room_elem;

	path_elem = *path;
	while (path_elem->next)
		path_elem = path_elem->next;
	adj_room_elem = (*(t_room **)path_elem->content)->connection_lst;
	best_room = NULL;
	while (best_room != input->end_room_ptr)
	{
		best_room = get_next_best_room(adj_room_elem, input->end_room_ptr,
															&validity, offset);
		if ((validity == valid_room) || (offset == -1 && validity == many))
		{
			validity = valid_room;
			best_room->is_visited = 1;
			ft_lstadd_e(path, ft_lstnew(&best_room, sizeof(best_room)));
			adj_room_elem = best_room->connection_lst;
		}
		else
			break ;
	}
	return (validity);
}

int						select_paths(t_input *input, t_report *report)
{
	size_t			max_num_of_paths;
	int				offset;

	if ((max_num_of_paths = count_max_num_of_paths(input)))
	{
		offset = max_num_of_paths - 2;
		report->number_of_paths = 0;
		preliminary_path_selection(input, report, max_num_of_paths, &offset);
		finalize_path_selection(input, report, &offset);
		if (report->number_of_paths)
			put_ants_to_paths(input, report);
		else
		{
			input->error = no_path_available;
			return (0);
		}
		return (1);
	}
	else
		return (0);
}
