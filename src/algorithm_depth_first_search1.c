/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_depth_first_search1.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 06:36:51 by ubuntu            #+#    #+#             */
/*   Updated: 2020/05/26 12:06:45 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void				print_valid_paths(t_output *output)
{
	t_valid_path	*path;
	t_list			*room_elem;
	size_t			c;
	size_t			i;
	t_room			*room;

	c = 0;
	ft_printf("\n");
	while (c < output->number_of_paths)
	{
		path = (t_valid_path *)output->valid_paths[c];
		ft_printf("%3d %3d", c, path->num_of_conn_to_end);
		room_elem = *path->room_lst;
		i = 50;
		while (room_elem && i--)
		{
			room = *(t_room **)room_elem->content;
			ft_printf(" %s", room->name);
			room_elem = room_elem->next;
		}
		ft_printf("\n");
		c++;
	}
	return ;
}

int						algorithm_depth_first_search1(t_output *output)
{
	size_t			*merged_room_vector;
	t_list			*new_path_lst;
	size_t			nr_instruction_lines;

	merged_room_vector = (size_t *)ft_memalloc(sizeof(*merged_room_vector) *
									((output->num_of_rooms / VECTOR_BITS) + 1));
	output->lst_of_selectd_paths =
				(t_list **)ft_memalloc(sizeof(*output->lst_of_selectd_paths));
	depth_first_search_2(output);
	sort_connections(output);
	output->number_of_paths = ft_lstlen(output->lst_of_valid_paths);
	output->valid_paths =
					(t_valid_path **)ft_memalloc(sizeof(*output->valid_paths) *
													output->number_of_paths);
	sort_valid_paths(output->lst_of_valid_paths, output->valid_paths);
	if (output->opt && output->opt & verbose)
		print_valid_paths(output);
	new_path_lst = NULL;
	nr_instruction_lines = INT_MAX;
	update_num_of_instr_lines(output, output->lst_of_valid_paths,
														&nr_instruction_lines);
	free(merged_room_vector);
	ft_lstdel(&new_path_lst, del_path);
	output->number_of_paths = ft_lstlen(output->lst_of_selectd_paths);
	return (put_ants_to_paths(output));
}
