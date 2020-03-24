/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pi <pi@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/18 06:42:46 by pi                #+#    #+#             */
/*   Updated: 2020/03/24 08:50:40 by pi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void			add_ants(t_input *input, size_t *c,
											t_valid_path *selected_valid_path)
{
	t_list			*path_elem;
	size_t			ants_to_add;

	ants_to_add = 1;
	while (ants_to_add--)
	{
		input->ant_array[*c]->path = selected_valid_path->path;
		path_elem = *(t_list **)input->ant_array[*c]->path;
		input->ant_array[*c]->current_room_elem = path_elem;
		selected_valid_path->num_of_ants++;
		(*c)++;
	}
	return ;
}

void				create_ants(t_input *input)
{
	size_t			c;
	char			*ant_id;

	input->ant_array = (t_ant **)ft_memalloc(sizeof(*input->ant_array) *
												(input->number_of_ants + 1));
	c = -1;
	while (++c < input->number_of_ants)
	{
		input->ant_array[c] = (t_ant *)ft_memalloc(sizeof(**input->ant_array));
		ant_id = ft_itoa(c + 1);
		input->ant_array[c]->name = ft_strjoin("L", ant_id);
		ft_strdel(&ant_id);
	}
	input->ant_array[c] = (t_ant *)ft_memalloc(sizeof(**input->ant_array));
	return ;
}

t_ant				*get_ant(char *name, t_input *input)
{
	t_ant		*ant;
	size_t		c;

	ant = NULL;
	c = -1;
	while (++c < input->number_of_ants)
	{
		if (!ft_strcmp(input->ant_array[c]->name, name))
		{
			ant = input->ant_array[c];
			break ;
		}
	}
	return (ant);
}

void				put_ants_to_paths(t_input *input, t_report *report)
{
	t_list			*elem;
	t_valid_path	*valid_path;
	t_valid_path	*selected_valid_path;
	size_t			c;

	c = 0;
	while (c < input->number_of_ants)
	{
		elem = *(t_list **)report->lst_of_valid_paths;
		selected_valid_path = *(t_valid_path **)elem->content;
		while (elem)
		{
			valid_path = *(t_valid_path **)elem->content;
			if (selected_valid_path)
			{
				if (valid_path->num_of_conn_to_end + valid_path->num_of_ants <
						selected_valid_path->num_of_conn_to_end +
											selected_valid_path->num_of_ants)
					selected_valid_path = valid_path;
			}
			elem = elem->next;
		}
		if (selected_valid_path)
			add_ants(input, &c, selected_valid_path);
	}
	return ;
}
