/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_paths_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pi <pi@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/18 06:36:34 by pi                #+#    #+#             */
/*   Updated: 2020/03/18 08:01:28 by pi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_valid_path			*create_valid_path(t_list **path, t_validity validity)
{
	t_valid_path	*valid_path;
	t_list			*path_elem;

	valid_path = (t_valid_path *)ft_memalloc(sizeof(*valid_path));
	valid_path->path = path;
	valid_path->validity = validity;
	valid_path->num_of_conn_to_end = -1;
	path_elem = *valid_path->path;
	while (path_elem)
	{
		valid_path->num_of_conn_to_end++;
		path_elem = path_elem->next;
	}
	return (valid_path);
}

void					update_valid_path(t_valid_path *valid_path)
{
	t_list			*path_elem;

	valid_path->num_of_conn_to_end = -1;
	path_elem = *valid_path->path;
	while (path_elem)
	{
		valid_path->num_of_conn_to_end++;
		path_elem = path_elem->next;
	}
	return ;
}

void					delete_valid_path(t_report *report, t_list *elem)
{
	t_list			*tmp_elem;
	t_valid_path	*valid_path;

	tmp_elem = elem->next;
	valid_path = *(t_valid_path **)elem->content;
	elem->prev ? elem->prev->next = elem->next : 0;
	elem->next ? elem->next->prev = elem->prev : 0;
	if (!elem->prev)
		*report->lst_of_valid_paths = tmp_elem;
	ft_lstdel(valid_path->path, del_path);
	free(valid_path->path);
	free(valid_path);
	report->number_of_paths--;
	return ;
}

size_t					count_max_num_of_paths(t_input *input)
{
	size_t			num_of_paths;
	size_t			max_num_of_paths;
	t_list			*elem;

	max_num_of_paths = input->number_of_ants;
	elem = input->start_room_ptr->connection_lst;
	num_of_paths = 0;
	while (elem)
	{
		num_of_paths++;
		elem = elem->next;
	}
	if (num_of_paths < max_num_of_paths)
		max_num_of_paths = num_of_paths;
	elem = input->end_room_ptr->connection_lst;
	num_of_paths = 0;
	while (elem)
	{
		num_of_paths++;
		elem = elem->next;
	}
	if (num_of_paths < max_num_of_paths)
		max_num_of_paths = num_of_paths;
	return (max_num_of_paths);
}
