/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_ford_fulkerson4.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 16:03:12 by ubuntu            #+#    #+#             */
/*   Updated: 2020/04/09 08:31:19 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				algorithm_ford_fulkerson4(t_output *output)
{
	t_room				*room;
	int					return_code;
	size_t				path_index;
	size_t				*merged_room_vector;
	t_list				*new_path_lst;

	room = output->start_room_ptr;
	path_index = 0;
	merged_room_vector = (size_t *)ft_memalloc(sizeof(*merged_room_vector) *
											((output->num_of_rooms / 32) + 1));
	output->lst_of_selectd_paths =
				(t_list **)ft_memalloc(sizeof(*output->lst_of_selectd_paths));
	output->first = 1;
	if (get_next_room(output, room, room, output->end_room_ptr))
	{
		output->number_of_paths =
								ft_lstlen(output->lst_of_valid_paths);
		output->valid_paths =
					(t_valid_path **)ft_memalloc(sizeof(*output->valid_paths) *
													output->number_of_paths);
		sort_valid_paths(output->lst_of_valid_paths, output->valid_paths);
		new_path_lst = NULL;
		select_best_group(&new_path_lst, merged_room_vector, output,
																	path_index);
		ft_lstdel(&new_path_lst, del_path);
		output->number_of_paths =
							ft_lstlen(output->lst_of_selectd_paths);
	}
	free(merged_room_vector);
	return_code = put_ants_to_paths(output);
	return (return_code);
}
