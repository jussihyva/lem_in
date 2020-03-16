/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 10:16:44 by jkauppi           #+#    #+#             */
/*   Updated: 2020/03/12 20:07:56 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void				update_best_room(t_room **next_room, t_room **best_room,
														t_validity *validity)
{
	if ((*next_room)->num_of_conn_to_end < (*best_room)->num_of_conn_to_end)
	{
		*best_room = *next_room;
		if (((*next_room)->num_of_conn_to_end + 1) <
											(*best_room)->num_of_conn_to_end)
			*validity = valid_room;
	}
	else if ((((*next_room)->num_of_conn_to_end - 1) <=
											(*best_room)->num_of_conn_to_end) &&
											(*best_room)->num_of_conn_to_start > 1)
		*validity = many_alternatives;
	return ;
}

static t_room			*get_next_best_room(t_list *adj_room_elem,
									t_room *end_room_ptr, t_validity *validity)
{
	t_room		*best_room;
	t_room		*next_room;
	size_t		num_of_conn_to_start;

	num_of_conn_to_start = ((t_room *)adj_room_elem)->num_of_conn_to_start;
	best_room = NULL;
	*validity = no_room;
	while (adj_room_elem)
	{
		next_room = *(t_room **)adj_room_elem->content;
		next_room->num_of_conn_to_start = num_of_conn_to_start;
		if ((next_room == end_room_ptr) || (next_room->num_of_conn_to_end &&
														!next_room->is_visited))
		{
			if (best_room)
				update_best_room(&next_room, &best_room, validity);
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
											t_list *adj_room_elem, int forced)
{
	int				end_room_reached;
	t_room			*best_room;
	t_validity		validity;

	end_room_reached = 0;
	while (!end_room_reached)
	{
		validity = no_room;
		best_room = get_next_best_room(adj_room_elem, input->end_room_ptr,
																&validity);
		if ((validity == valid_room) ||
									(!forced && validity == many_alternatives))
		{
			validity = valid_room;
			best_room->is_visited = 1;
			ft_lstadd_e(path, ft_lstnew(&best_room, sizeof(best_room)));
			if (best_room == input->end_room_ptr)
				end_room_reached = 1;
			else
				adj_room_elem = best_room->connection_lst;
		}
		else
			break ;
	}
	return (validity);
}

static t_valid_path		*find_shortest_path(t_input *input, int forced)
{
	t_valid_path	*valid_path;
	t_list			**path;
	t_list			*adj_room_elem;
	t_validity		validity;

	path = (t_list **)ft_memalloc(sizeof(*path));
	ft_lstadd_e(path, ft_lstnew(&input->start_room_ptr,
											sizeof(input->start_room_ptr)));
	adj_room_elem = input->start_room_ptr->connection_lst;
	((t_room *)adj_room_elem)->num_of_conn_to_start = 1;
	validity = create_path(input, path, adj_room_elem, forced);
	if (validity != no_room)
	{
		valid_path = (t_valid_path *)ft_memalloc(sizeof(*valid_path));
		valid_path->path = path;
		valid_path->validity = validity;
		valid_path->num_of_conn_to_end =
								input->start_room_ptr->num_of_conn_to_end;
	}
	else
	{
		valid_path = NULL;
		ft_lstdel_1(path);
		free(path);
	}
	return (valid_path);
}

static void				put_ants_to_paths(t_report *report)
{
	t_list			*elem;
	t_valid_path	*valid_path;
	size_t			c;
	char			*ant_id;

	elem = *(t_list **)report->lst_of_valid_paths;
	valid_path = *(t_valid_path **)elem->content;
	c = -1;
	while (++c < report->number_of_ants)
	{
		ant_id = ft_itoa(c + 1);
		report->ant_array[c].name = ft_strjoin("L", ant_id);
		ft_strdel(&ant_id);
		report->ant_array[c].path = valid_path->path;
	}
	return ;
}

int						select_paths(t_input *input, t_report *report)
{
	t_valid_path	*valid_path;
	size_t			num_of_paths;
	t_list			*elem;
	t_list			*path_elem;
	t_list			*adj_room_elem;
	t_validity		validity;

	num_of_paths = 0;
	elem = input->start_room_ptr->connection_lst;
	while (elem)
	{
		num_of_paths++;
		elem = elem->next;
	}
	report->number_of_paths = 0;
	valid_path = find_shortest_path(input, num_of_paths - 1);
	while (valid_path && num_of_paths)
	{
		ft_lstadd(report->lst_of_valid_paths, ft_lstnew(&valid_path,
														sizeof(valid_path)));
		report->number_of_paths++;
		num_of_paths--;
		if (num_of_paths)
			valid_path = find_shortest_path(input, num_of_paths);
	}
	elem = *(t_list **)report->lst_of_valid_paths;
	while (elem)
	{
		valid_path = *(t_valid_path **)elem->content;
		if (valid_path->validity == many_alternatives)
		{
			path_elem = *valid_path->path;
			while (path_elem->next)
				path_elem = path_elem->next;
			adj_room_elem = (*(t_room **)path_elem->content)->connection_lst;
			validity = create_path(input, valid_path->path, adj_room_elem, 0);
		}
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
