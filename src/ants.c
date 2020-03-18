/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pi <pi@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/18 06:42:46 by pi                #+#    #+#             */
/*   Updated: 2020/03/18 06:45:54 by pi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				put_ants_to_paths(t_report *report)
{
	t_list			*elem;
	t_valid_path	*valid_path;
	size_t			c;
	char			*ant_id;

	elem = *(t_list **)report->lst_of_valid_paths;
	valid_path = *(t_valid_path **)elem->content;
	c = -1;
	while (++c < report->number_of_ants)
	{
		ant_id = ft_itoa(c + 1);
		report->ant_array[c].name = ft_strjoin("L", ant_id);
		ft_strdel(&ant_id);
		report->ant_array[c].path = valid_path->path;
	}
	return ;
}
