/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 15:25:14 by jkauppi           #+#    #+#             */
/*   Updated: 2020/03/09 16:34:55 by jkauppi          ###   ########.fr       */
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

void			del_report(void *elem, size_t size)
{
	t_valid_path	*valid_path;

	(void)size;
	valid_path = *(t_valid_path **)elem;
	ft_lstdel(valid_path->path, del_path);
	free(valid_path->path);
	free(valid_path);
	free(elem);
	return ;
}

void			release_report(t_report *report)
{
	ft_lstdel(report->lst_of_valid_paths, del_report);
	free(report->lst_of_valid_paths);
	report->lst_of_valid_paths = NULL;
	free(report->ant_array);
	report->ant_array = NULL;
	free(report);
	report = NULL;
	return ;
}
