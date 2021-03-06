/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_ford_fulkerson3_1.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 09:30:36 by ubuntu            #+#    #+#             */
/*   Updated: 2020/05/31 19:34:35 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		update_ants_in_start_room(int *ants_in_start_room,
						t_valid_path *valid_path, size_t nr_connection_to_end,
						size_t c)
{
	(*ants_in_start_room)--;
	if (c > 1)
		*ants_in_start_room -= (valid_path->num_of_conn_to_end -
												nr_connection_to_end) * (c - 1);
	return ;
}

size_t			count_num_of_instruction_lines(t_list **path_lst,
							size_t number_of_ants, size_t nr_instruction_lines)
{
	t_valid_path	*valid_path;
	t_list			*elem;
	size_t			nr_connection_to_end;
	size_t			c;
	int				ants_in_start_room;

	ants_in_start_room = (int)number_of_ants;
	c = 0;
	nr_connection_to_end = 0;
	elem = *path_lst;
	while (elem && ants_in_start_room > 0)
	{
		c++;
		valid_path = *(t_valid_path **)elem->content;
		update_ants_in_start_room(&ants_in_start_room, valid_path,
												nr_connection_to_end, c);
		nr_connection_to_end = valid_path->num_of_conn_to_end;
		if (nr_instruction_lines > ants_in_start_room / c +
						((ants_in_start_room % c) > 0) + nr_connection_to_end)
			nr_instruction_lines = ants_in_start_room / c +
						((ants_in_start_room % c) > 0) + nr_connection_to_end;
		elem = elem->next;
	}
	return (nr_instruction_lines);
}

int				algorithm_ford_fulkerson3(t_output *output)
{
	size_t				*merged_room_vector;
	t_list				*new_path_lst;

	prepare_room_data(output->room_array, output->num_of_rooms);
	merged_room_vector = (size_t *)ft_memalloc(sizeof(*merged_room_vector) *
									((output->num_of_rooms / VECTOR_BITS) + 1));
	output->lst_of_selectd_paths =
				(t_list **)ft_memalloc(sizeof(*output->lst_of_selectd_paths));
	sort_connections(output, e_ascending);
	output->first = 1;
	if (get_next_room(output, output->start_room_ptr, output->start_room_ptr,
														output->end_room_ptr))
	{
		output->number_of_paths = ft_lstlen(output->lst_of_valid_paths);
		output->valid_paths =
					(t_valid_path **)ft_memalloc(sizeof(*output->valid_paths) *
													output->number_of_paths);
		sort_valid_paths(output->lst_of_valid_paths, output->valid_paths);
		new_path_lst = NULL;
		select_best_group(&new_path_lst, merged_room_vector, output, 0);
		ft_lstdel(&new_path_lst, del_path);
		output->number_of_paths = ft_lstlen(output->lst_of_selectd_paths);
	}
	free(merged_room_vector);
	return (put_ants_to_paths(output));
}
