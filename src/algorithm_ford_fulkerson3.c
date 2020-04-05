/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_ford_fulkerson3.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 09:30:36 by ubuntu            #+#    #+#             */
/*   Updated: 2020/04/05 15:42:40 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void			ft_lstrem(t_list **lst, t_list *elem)
{
	t_list			*tmp_elem;
	t_valid_path	*valid_path;

	tmp_elem = elem->next;
	valid_path = *(t_valid_path **)elem->content;
	elem->prev ? elem->prev->next = elem->next : 0;
	elem->next ? elem->next->prev = elem->prev : 0;
	if (!elem->prev)
		*lst = tmp_elem;
	free(elem->content);
	free(elem);
	return ;
}

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

static void		select_best_group_of_paths(t_list **path_lst,
				size_t *merged_room_vector, t_output *output, size_t path_index)
{
	t_valid_path	*valid_path;
	t_list			*elem;
	t_list			*new_elem;
	size_t			c;
	static size_t	nr_valid_paths = 0;

	valid_path = output->valid_paths[path_index];
	if (path_index < output->number_of_paths)
	{
		if (!is_room_colision(merged_room_vector, valid_path->room_vector,
														output->num_of_rooms))
		{
			elem = ft_lstnew(&valid_path, sizeof(valid_path));
			ft_lstadd_e(path_lst, elem);
			nr_valid_paths++;
			select_best_group_of_paths(path_lst, merged_room_vector, output,
																path_index + 1);
			ft_lstrem(path_lst, elem);
			nr_valid_paths--;
			c = -1;
			while (++c < ((output->num_of_rooms / 32) + 1))
				merged_room_vector[c] &= ~valid_path->room_vector[c];
			select_best_group_of_paths(path_lst, merged_room_vector, output,
																path_index + 1);
		}
		else
			select_best_group_of_paths(path_lst, merged_room_vector, output,
																path_index + 1);
	}
	else
	{
		if (*path_lst)
		{
			if (*output->lst_of_selectd_paths)
			{
				if (nr_valid_paths > output->number_of_selected_paths)
				{
					ft_lstdel(output->lst_of_selectd_paths, del_path);
					elem = *path_lst;
					while (elem)
					{
						valid_path = *(t_valid_path **)elem->content;
						new_elem = ft_lstnew(&valid_path, sizeof(valid_path));
						ft_lstadd_e(output->lst_of_selectd_paths, new_elem);
						elem = elem->next;
					}
					output->number_of_selected_paths = ft_lstlen(output->lst_of_selectd_paths);
				}
			}
			else
			{
				elem = *path_lst;
				while (elem)
				{
					valid_path = *(t_valid_path **)elem->content;
					new_elem = ft_lstnew(&valid_path, sizeof(valid_path));
					ft_lstadd_e(output->lst_of_selectd_paths, new_elem);
					elem = elem->next;
				}
				output->number_of_selected_paths = ft_lstlen(output->lst_of_selectd_paths);
			}
		}
	}
	return ;
}

int				algorithm_ford_fulkerson3(t_output *output)
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
	if (get_next_room(output, room, room, output->end_room_ptr))
	{
		output->number_of_paths =
								ft_lstlen(output->lst_of_valid_paths);
		output->valid_paths =
					(t_valid_path **)ft_memalloc(sizeof(*output->valid_paths) *
													output->number_of_paths);
		sort_valid_paths(output->lst_of_valid_paths, output->valid_paths);
		new_path_lst = NULL;
		select_best_group_of_paths(&new_path_lst, merged_room_vector, output,
																	path_index);
		ft_lstdel(&new_path_lst, del_path);
		output->number_of_paths =
							ft_lstlen(output->lst_of_selectd_paths);
	}
	free(merged_room_vector);
	return_code = put_ants_to_paths(output);
	return (return_code);
}
