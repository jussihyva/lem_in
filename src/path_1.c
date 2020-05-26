/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 15:03:33 by ubuntu            #+#    #+#             */
/*   Updated: 2020/05/26 17:48:49 by ubuntu           ###   ########.fr       */
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

static void		update_path_to_lst(t_output *output, t_best_paths *best_paths,
								size_t branch_id, size_t nr_instruction_lines)
{
	size_t			i;
	t_list			*elem;
	t_valid_path	*valid_path;

	i = 0;
	while (output->path_array[branch_id][i] && i < 3)
	{
		valid_path = output->path_array[branch_id][i];
		if (nr_instruction_lines < (size_t)valid_path->num_of_conn_to_end)
			break ;
		else if (!is_room_colision(best_paths->merged_room_vector,
						valid_path->room_vector, output->num_of_rooms))
		{
			elem = ft_lstnew(&valid_path, sizeof(valid_path));
			ft_lstadd_e(best_paths->path_lst, elem);
			select_paths_2(output, best_paths, branch_id + 1);
			ft_lstrem(best_paths->path_lst, elem);
			update_room_vector(output, valid_path,
												best_paths->merged_room_vector);
		}
		i++;
	}
	return ;
}

void			select_paths_2(t_output *output, t_best_paths *best_paths,
															size_t branch_id)
{
	static size_t	nr_instruction_lines = INT_MAX;

	if (branch_id < output->start_room_ptr->num_of_connections)
	{
		update_path_to_lst(output, best_paths, branch_id, nr_instruction_lines);
		select_paths_2(output, best_paths, branch_id + 1);
	}
	else if (*best_paths->path_lst)
		update_num_of_instr_lines(output, best_paths->path_lst,
														&nr_instruction_lines);
	return ;
}

void			save_valid_path(t_output *output,
										size_t *num_of_paths_in_branch_array)
{
	t_valid_path	*valid_path;
	size_t			i;

	i = -1;
	while (++i < output->number_of_paths)
	{
		valid_path = output->valid_paths[i];
		output->path_array[valid_path->branch_id]
			[num_of_paths_in_branch_array[valid_path->branch_id]] = valid_path;
		num_of_paths_in_branch_array[valid_path->branch_id]++;
	}
	return ;
}

void			select_paths_1(t_output *output)
{
	size_t			i;
	size_t			*num_of_paths_in_branch_array;
	t_best_paths	best_paths;

	best_paths.path_lst = (t_list **)ft_memalloc(sizeof(*best_paths.path_lst));
	best_paths.merged_room_vector =
				(size_t *)ft_memalloc(sizeof(*best_paths.merged_room_vector) *
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
	save_valid_path(output, num_of_paths_in_branch_array);
	select_paths_2(output, &best_paths, 0);
	free(best_paths.merged_room_vector);
	free(best_paths.path_lst);
	free(num_of_paths_in_branch_array);
	return ;
}
