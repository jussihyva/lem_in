/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_paths_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pi <pi@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/18 17:01:51 by pi                #+#    #+#             */
/*   Updated: 2020/03/18 17:02:30 by pi               ###   ########.fr       */
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
