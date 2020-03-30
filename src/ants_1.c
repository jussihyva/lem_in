/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/18 06:42:46 by pi                #+#    #+#             */
/*   Updated: 2020/03/30 12:29:58 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void			add_ants(t_output *output, size_t *c,
											t_valid_path *selected_valid_path)
{
	t_list			*path_elem;
	size_t			ants_to_add;

	ants_to_add = 1;
	while (ants_to_add-- && selected_valid_path)
	{
		output->ant_array[*c]->path = selected_valid_path->path;
		path_elem = *(t_list **)output->ant_array[*c]->path;
		output->ant_array[*c]->current_room_elem = path_elem;
		selected_valid_path->num_of_ants++;
		(*c)++;
	}
	return ;
}

void				create_ants(t_output *output)
{
	size_t			c;
	char			*ant_id;

	output->ant_array = (t_ant **)ft_memalloc(sizeof(*output->ant_array) *
														output->number_of_ants);
	c = -1;
	while (++c < output->number_of_ants)
	{
		output->ant_array[c] =
							(t_ant *)ft_memalloc(sizeof(**output->ant_array));
		ant_id = ft_itoa(c + 1);
		output->ant_array[c]->name = ft_strjoin("L", ant_id);
		output->ant_array[c]->current_room = output->start_room_ptr;
		ft_strdel(&ant_id);
	}
	return ;
}

t_ant				*get_ant(char *name, t_output *output)
{
	t_ant		*ant;
	size_t		c;

	ant = NULL;
	c = -1;
	while (++c < output->number_of_ants)
	{
		if (!ft_strcmp(output->ant_array[c]->name, name))
		{
			ant = output->ant_array[c];
			break ;
		}
	}
	return (ant);
}

int					put_ants_to_paths(t_output *output)
{
	t_list			*elem;
	t_valid_path	*valid_path;
	t_valid_path	*selected_valid_path;
	int				return_code;
	size_t			c;

	return_code = 0;
	selected_valid_path = NULL;
	c = 0;
	while (c < output->number_of_ants && output->number_of_paths)
	{
		elem = *(t_list **)output->lst_of_valid_paths;
		while (elem)
		{
			return_code = 1;
			valid_path = *(t_valid_path **)elem->content;
			if (!selected_valid_path || (valid_path->num_of_conn_to_end +
			valid_path->num_of_ants < selected_valid_path->num_of_conn_to_end +
											selected_valid_path->num_of_ants))
				selected_valid_path = valid_path;
			elem = elem->next;
		}
		add_ants(output, &c, selected_valid_path);
	}
	return (return_code);
}
