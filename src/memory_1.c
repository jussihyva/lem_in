/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 15:25:14 by jkauppi           #+#    #+#             */
/*   Updated: 2020/05/01 21:49:45 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			del_path(void *room, size_t size)
{
	(void)size;
	free(room);
	room = NULL;
	return ;
}

void			del_output(void *elem, size_t size)
{
	t_valid_path	*valid_path;

	(void)size;
	valid_path = *(t_valid_path **)elem;
	ft_lstdel(valid_path->room_lst, del_path);
	free(valid_path->room_lst);
	free(valid_path->room_vector);
	free(valid_path);
	free(elem);
	return ;
}

void			release_output(t_output *output)
{
	size_t		c;

	ft_lstdel(output->instruction_line_lst, del_path);
	free(output->instruction_line_lst);
	ft_lstdel(output->lst_of_valid_paths, del_output);
	if (*output->lst_of_selectd_paths)
		ft_lstdel(output->lst_of_selectd_paths, del_path);
	free(output->lst_of_selectd_paths);
	free(output->lst_of_valid_paths);
	output->lst_of_valid_paths = NULL;
	release_connection_array(output);
	c = -1;
	if (output->ant_array)
	{
		while (++c < output->number_of_ants)
		{
			ft_strdel(&output->ant_array[c]->name);
			free(output->ant_array[c]);
		}
		free(output->ant_array);
	}
	free(output->valid_paths);
	free(output);
	return ;
}

void			release_result(t_result *result)
{
	t_list			*elem;
	t_list			*tmp_elem;
	t_output		*output;

	elem = *result->output_lst;
	while (elem)
	{
		tmp_elem = elem->next;
		output = (t_output *)elem->content;
		release_output(output);
		free(elem);
		elem = tmp_elem;
	}
	free(result->output_lst);
	return ;
}
