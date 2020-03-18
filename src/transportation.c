/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transportation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pi <pi@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 10:25:46 by jkauppi           #+#    #+#             */
/*   Updated: 2020/03/18 13:34:43 by pi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				transportation(t_report *report)
{
	t_list			*elem;
	t_list			*valid_path_elem;
	t_valid_path	*valid_path;
	t_room			*room;

	valid_path_elem = *report->lst_of_valid_paths;
	while (valid_path_elem)
	{
		valid_path = *(t_valid_path **)valid_path_elem->content;
		elem = *valid_path->path;
		while (elem)
		{
			room = *(t_room **)elem->content;
			elem = elem->next;
		}
		valid_path_elem = valid_path_elem->next;
	}
	return ;
}
