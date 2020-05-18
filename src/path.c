/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 15:03:33 by ubuntu            #+#    #+#             */
/*   Updated: 2020/05/18 07:09:14 by ubuntu           ###   ########.fr       */
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
									((output->num_of_rooms / VECTOR_BITS) + 1));
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

static void		select_paths_2(t_output *output, t_list **path_lst,
								size_t *merged_room_vector, size_t barach_id,
										size_t *num_of_paths_in_branch_array)
{
	t_list			*elem;
	size_t			i;
	t_valid_path	*valid_path;
	static size_t	nr_instruction_lines = INT_MAX;

	if (barach_id < output->start_room_ptr->num_of_connections)
	{
		i = 0;
		if (output->path_array[barach_id][i])
		{
	//		while (output->path_array[barach_id][i] && i < (num_of_paths_in_branch_array[barach_id] / 5 + 1))
			while (output->path_array[barach_id][i] && i < 3)
			{
				valid_path = output->path_array[barach_id][i];
				if (nr_instruction_lines < (size_t)valid_path->num_of_conn_to_end)
					break ;
				else if (!is_room_colision(merged_room_vector,
								valid_path->room_vector, output->num_of_rooms))
				{
					elem = ft_lstnew(&valid_path, sizeof(valid_path));
					ft_lstadd_e(path_lst, elem);
					select_paths_2(output, path_lst, merged_room_vector,
								barach_id + 1, num_of_paths_in_branch_array);
					ft_lstrem(path_lst, elem);
					update_room_vector(output, valid_path, merged_room_vector);
				}
				i++;
			}
			select_paths_2(output, path_lst, merged_room_vector, barach_id + 1,
												num_of_paths_in_branch_array);
		}
		else
			select_paths_2(output, path_lst, merged_room_vector, barach_id + 1,
												num_of_paths_in_branch_array);
	}
	else if (*path_lst)
		update_num_of_instr_lines(output, path_lst, &nr_instruction_lines);
	return ;
}

void			select_paths_1(t_output *output)
{
	t_valid_path	*valid_path;
	size_t			i;
	size_t			*num_of_paths_in_branch_array;
	t_list			*path_lst;
	size_t			barach_id;
	size_t			*merged_room_vector;

	merged_room_vector = (size_t *)ft_memalloc(sizeof(*merged_room_vector) *
									((output->num_of_rooms / VECTOR_BITS) + 1));
	num_of_paths_in_branch_array =
				(size_t *)ft_memalloc(sizeof(*num_of_paths_in_branch_array) *
				output->start_room_ptr->num_of_connections);
	output->path_array =
					(t_valid_path ***)ft_memalloc(sizeof(*output->path_array) *
									output->start_room_ptr->num_of_connections);
	i = -1;
	while (++i < output->start_room_ptr->num_of_connections)
		output->path_array[i] =
					(t_valid_path **)ft_memalloc(sizeof(**output->path_array) *
													output->number_of_paths);
	i = -1;
	while (++i < output->number_of_paths)
	{
		valid_path = output->valid_paths[i];
		output->path_array[valid_path->branch_id]
			[num_of_paths_in_branch_array[valid_path->branch_id]] = valid_path;
		num_of_paths_in_branch_array[valid_path->branch_id]++;
	}
//	free(i_array);
	path_lst = NULL;
	barach_id = 0;
	select_paths_2(output, &path_lst, merged_room_vector, barach_id,
												num_of_paths_in_branch_array);
	return ;
}
