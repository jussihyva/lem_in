/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_ford_fulkerson3_2.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 10:16:33 by ubuntu            #+#    #+#             */
/*   Updated: 2020/04/23 13:53:11 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		is_room_colision(size_t *merged_room_vector,
									size_t *room_vector, size_t num_of_rooms)
{
	size_t			c;

	c = -1;
	while (++c < ((num_of_rooms / 32) + 1))
	{
		if (merged_room_vector[c] & room_vector[c])
			return (1);
	}
	c = -1;
	while (++c < ((num_of_rooms / 32) + 1))
		merged_room_vector[c] |= room_vector[c];
	return (0);
}

static void		update_lst_of_selectd_paths(t_output *output, t_list **path_lst)
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
	return ;
}

static void		update_num_of_instruction_lines(t_output *output,
								t_list **path_lst, size_t *nr_instruction_lines)
{
	if (*output->lst_of_selectd_paths)
	{
		if (*nr_instruction_lines > count_num_of_instruction_lines(path_lst,
							output->number_of_ants, *nr_instruction_lines))
		{
			ft_lstdel(output->lst_of_selectd_paths, del_path);
			update_lst_of_selectd_paths(output, path_lst);
			output->number_of_selected_paths =
								ft_lstlen(output->lst_of_selectd_paths);
			*nr_instruction_lines = count_num_of_instruction_lines(path_lst,
							output->number_of_ants, *nr_instruction_lines);
		}
	}
	else
	{
		update_lst_of_selectd_paths(output, path_lst);
		output->number_of_selected_paths =
								ft_lstlen(output->lst_of_selectd_paths);
		*nr_instruction_lines = count_num_of_instruction_lines(path_lst,
							output->number_of_ants, *nr_instruction_lines);
	}
	return ;
}

static void		update_room_vector(t_output *output, t_valid_path *valid_path,
													size_t *merged_room_vector)
{
	size_t			c;

	c = -1;
	while (++c < ((output->num_of_rooms / 32) + 1))
		merged_room_vector[c] &= ~valid_path->room_vector[c];
	return ;
}

void			select_best_group(t_list **path_lst,
				size_t *merged_room_vector, t_output *output, size_t path_index)
{
	t_valid_path	*valid_path;
	t_list			*elem;
	static size_t	nr_instruction_lines = INT_MAX;

	while (path_index < output->number_of_paths)
	{
		valid_path = output->valid_paths[path_index];
		if (!is_room_colision(merged_room_vector, valid_path->room_vector,
														output->num_of_rooms))
		{
			elem = ft_lstnew(&valid_path, sizeof(valid_path));
			ft_lstadd_e(path_lst, elem);
			select_best_group(path_lst, merged_room_vector, output, path_index + 1);
			ft_lstrem(path_lst, elem);
			update_room_vector(output, valid_path, merged_room_vector);
//			select_best_group(path_lst, merged_room_vector, output, path_index);
		}
//		else
//			select_best_group(path_lst, merged_room_vector, output, path_index + 1);
		path_index++;
	}
	if (*path_lst)
		update_num_of_instruction_lines(output, path_lst,
														&nr_instruction_lines);
	return ;
}
