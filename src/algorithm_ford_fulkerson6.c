/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_ford_fulkerson6.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 19:23:52 by ubuntu            #+#    #+#             */
/*   Updated: 2020/06/24 23:19:14 by ubuntu           ###   ########.fr       */
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

	c = -1;
	ft_printf("\n");
	while (++c < output->number_of_paths)
	{
		path = (t_valid_path *)output->valid_paths[c];
		ft_printf("%3d %3d", c, path->num_of_conn_to_end);
		room_elem = *path->room_lst;
		i = 25;
		while (room_elem && i--)
		{
			room = *(t_room **)room_elem->content;
			ft_printf(" %s", room->name);
			room_elem = room_elem->next;
		}
		ft_printf("\n");
	}
	return ;
}

int						algorithm_ford_fulkerson6(t_output *output)
{
	int				return_code;
	t_list			*new_path_lst;
	size_t			*merged_room_vector;

	prepare_room_data(output->room_array, output->num_of_rooms);
	merged_room_vector = (size_t *)ft_memalloc(sizeof(*merged_room_vector) *
									((output->num_of_rooms / VECTOR_BITS) + 1));
	output->lst_of_selectd_paths =
				(t_list **)ft_memalloc(sizeof(*output->lst_of_selectd_paths));
	initialize_connection_array(output);
	sort_connections(output, e_ascending);
	breadth_first_search(output);
	output->number_of_paths = ft_lstlen(output->lst_of_valid_paths);
	output->valid_paths = (t_valid_path **)ft_memalloc(
					sizeof(*output->valid_paths) * output->number_of_paths);
	sort_valid_paths(output->lst_of_valid_paths, output->valid_paths);
	if (output->opt && output->opt & verbose)
		print_valid_paths(output);
	new_path_lst = NULL;
	select_best_group(&new_path_lst, merged_room_vector, output, 0);
	free(merged_room_vector);
	ft_lstdel(&new_path_lst, del_path);
	output->number_of_paths = ft_lstlen(output->lst_of_selectd_paths);
	return_code = put_ants_to_paths(output);
	return (return_code);
}
