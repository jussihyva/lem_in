/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 17:47:38 by ubuntu            #+#    #+#             */
/*   Updated: 2020/05/26 17:48:49 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			save_path(t_output *output, t_room *room, size_t branch_id)
{
	t_room			*parent_room;
	t_valid_path	*path;

	path = initialize_path(output, valid_room, branch_id);
	parent_room = room->parent_room;
	ft_lstadd(path->room_lst, ft_lstnew(&output->end_room_ptr,
												sizeof(output->end_room_ptr)));
	ft_lstadd(path->room_lst, ft_lstnew(&room, sizeof(room)));
	path->room_vector[room->id / VECTOR_BITS] |= 1 << (room->id % VECTOR_BITS);
	path->num_of_conn_to_end++;
	room->num_of_conn_to_end = path->num_of_conn_to_end;
	while (parent_room->parent_room)
	{
		path->room_vector[parent_room->id / VECTOR_BITS] |= 1 <<
												(parent_room->id % VECTOR_BITS);
		ft_lstadd(path->room_lst, ft_lstnew(&parent_room, sizeof(parent_room)));
		path->num_of_conn_to_end++;
		parent_room->num_of_conn_to_end = path->num_of_conn_to_end;
		parent_room = parent_room->parent_room;
	}
	ft_lstadd(path->room_lst, ft_lstnew(&output->start_room_ptr,
											sizeof(output->start_room_ptr)));
	path->num_of_conn_to_end++;
	ft_lstadd_e(output->lst_of_valid_paths, ft_lstnew(&path, sizeof(path)));
	return ;
}

void			update_lst_of_selectd_paths(t_output *output, t_list **path_lst,
												size_t *nr_instruction_lines)
{
	t_list			*elem;
	t_valid_path	*valid_path;
	t_list			*new_elem;

	elem = *path_lst;
	while (elem)
	{
		valid_path = *(t_valid_path **)elem->content;
		new_elem = ft_lstnew(&valid_path, sizeof(valid_path));
		ft_lstadd_e(output->lst_of_selectd_paths, new_elem);
		elem = elem->next;
	}
	output->number_of_selected_paths = ft_lstlen(output->lst_of_selectd_paths);
	if (output->opt && output->opt & verbose)
		ft_printf("Lines: %d(%d)\n", *nr_instruction_lines,
											output->number_of_selected_paths);
	return ;
}
