/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 15:25:14 by jkauppi           #+#    #+#             */
/*   Updated: 2020/03/05 15:08:33 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			del_path(void *room, size_t size)
{
	(void)size;
	(void)room;
	return ;
}

void			del_path_2(void *room, size_t size)
{
	(void)size;
	free(room);
	room = NULL;
	return ;
}

void			release_report(t_report *report)
{
	ft_lstdel(report->lst_of_valid_paths, del_path_2);
	free(report->lst_of_valid_paths);
	report->lst_of_valid_paths = NULL;
	free(report->valid_path);
	report->valid_path = NULL;
	free(report);
	report = NULL;
	return ;
}
