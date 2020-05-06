/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 15:03:33 by ubuntu            #+#    #+#             */
/*   Updated: 2020/05/06 14:33:07 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_valid_path	*initialize_path(t_output *output, t_validity validity,
															size_t branch_id)
{
	static int		id;
	t_valid_path	*path;

	path = (t_valid_path *)ft_memalloc(sizeof(*path));
	path->room_lst = (t_list **)ft_memalloc(sizeof(*path->room_lst));
	path->room_vector = (size_t *)ft_memalloc(sizeof(*path->room_vector) *
											((output->num_of_rooms / 32) + 1));
	path->id = id++;
	path->validity = validity;
	path->branch_id = branch_id;
	path->num_of_conn_to_end = 0;
	return (path);
}

void			save_path(t_output *output, t_room *room, size_t branch_id)
{
	t_room			*parent_room;
	t_valid_path	*path;

	path = initialize_path(output, valid_room, branch_id);
	parent_room = room->parent_room;
	ft_lstadd(path->room_lst, ft_lstnew(&output->end_room_ptr,
												sizeof(output->end_room_ptr)));
	ft_lstadd(path->room_lst, ft_lstnew(&room, sizeof(room)));
	path->room_vector[room->id / 32] |= 1 << (room->id % 32);
	path->num_of_conn_to_end++;
	room->num_of_conn_to_end = path->num_of_conn_to_end;
	while (parent_room->parent_room)
	{
		path->room_vector[parent_room->id / 32] |= 1 << (parent_room->id % 32);
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

void			select_paths_1(t_output *output)
{
	t_list			*elem;
	t_valid_path	*valid_path;
	size_t			i;
	t_room			*room;
	size_t			*i_array;

	i_array = (size_t *)ft_memalloc(sizeof(*i_array) * output->start_room_ptr->num_of_connections);
	output->path_array = (t_valid_path ***)ft_memalloc(sizeof(*output->path_array) * output->start_room_ptr->num_of_connections);
	i = -1;
	while (++i < output->start_room_ptr->num_of_connections)
		output->path_array[i] = (t_valid_path **)ft_memalloc(sizeof(**output->path_array) * output->number_of_paths);
	i = -1;
	while (++i < output->number_of_paths)
	{
		valid_path = output->valid_paths[i];
		output->path_array[valid_path->branch_id][i_array[valid_path->branch_id]] = valid_path;
		i_array[valid_path->branch_id]++;
		elem = *(t_list **)valid_path->room_lst;
		if (elem->next)
		{
			room = *(t_room **)elem->next->content;
//			ft_printf("The first room in the path: %s %d(%d)\n", room->name, valid_path->branch_id, output->start_room_ptr->num_of_connections);
		}
	}
	free(i_array);
	return ;
}
