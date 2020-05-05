/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_ford_fulkerson3_2.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 10:16:33 by ubuntu            #+#    #+#             */
/*   Updated: 2020/05/05 23:26:10 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		is_room_colision(size_t *merged_room_vector,
									size_t *room_vector, size_t num_of_rooms)
{
	size_t			c;
	size_t			vector_size;

	vector_size = (num_of_rooms / 32) + 1;
	c = -1;
	while (++c < vector_size)
	{
		if (merged_room_vector[c] & room_vector[c])
			return (1);
	}
	c = -1;
	while (++c < vector_size)
		merged_room_vector[c] |= room_vector[c];
	return (0);
}

static void		update_num_of_instr_lines(t_output *output,
								t_list **path_lst, size_t *nr_instruction_lines)
{
	size_t		tmp_nr_instruction_lines;

	if (*output->lst_of_selectd_paths)
	{
		tmp_nr_instruction_lines = count_num_of_instruction_lines(path_lst,
							output->number_of_ants, *nr_instruction_lines);
		if (*nr_instruction_lines > tmp_nr_instruction_lines)
		{
			ft_lstdel(output->lst_of_selectd_paths, del_path);
			*nr_instruction_lines = tmp_nr_instruction_lines;
			update_lst_of_selectd_paths(output, path_lst, nr_instruction_lines);
		}
	}
	else
	{
		*nr_instruction_lines = count_num_of_instruction_lines(path_lst,
							output->number_of_ants, *nr_instruction_lines);
		update_lst_of_selectd_paths(output, path_lst, nr_instruction_lines);
	}
	return ;
}

static void		update_room_vector(t_output *output, t_valid_path *valid_path,
													size_t *merged_room_vector)
{
	size_t			c;
	size_t			vector_size;

	vector_size = (output->num_of_rooms / 32) + 1;
	c = -1;
	while (++c < vector_size)
		merged_room_vector[c] &= ~valid_path->room_vector[c];
	return ;
}

static int		selection_timeout(t_output *output)
{
	static size_t	path_verification_cnt = 1;

//	if (!(path_verification_cnt % 900000))
	if (1 == 2)
	{
		if (output->opt && output->opt & verbose)
			ft_printf("Timeout: %d\n", path_verification_cnt);
		return (1);
	}
	else
	{
		path_verification_cnt++;
		return (0);
	}
}

void			select_best_group(t_list **path_lst,
				size_t *merged_room_vector, t_output *output, size_t path_index)
{
	t_valid_path	*valid_path;
	t_list			*elem;
	static size_t	nr_instruction_lines = INT_MAX;

	if (selection_timeout(output))
		return ;
	if (path_index < output->number_of_paths)
	{
		valid_path = output->valid_paths[path_index];
		if (nr_instruction_lines > (size_t)valid_path->num_of_conn_to_end &&
				!is_room_colision(merged_room_vector, valid_path->room_vector,
				output->num_of_rooms))
		{
			elem = ft_lstnew(&valid_path, sizeof(valid_path));
			ft_lstadd(path_lst, elem);
			select_best_group(path_lst, merged_room_vector, output,
																path_index + 1);
			ft_lstrem(path_lst, elem);
			update_room_vector(output, valid_path, merged_room_vector);
		}
		select_best_group(path_lst, merged_room_vector, output, path_index + 1);
	}
	else if (*path_lst)
		update_num_of_instr_lines(output, path_lst, &nr_instruction_lines);
	return ;
}
