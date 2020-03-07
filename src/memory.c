/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 15:25:14 by jkauppi           #+#    #+#             */
/*   Updated: 2020/03/07 13:13:53 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			del_path_2(void *room, size_t size)
{
	(void)size;
	free(room);
	room = NULL;
	return ;
}

void			del_report(void *elem, size_t size)
{
	(void)size;
	free(((t_valid_path *)elem)->path);
	((t_valid_path *)elem)->path = NULL;
	free((t_valid_path *)elem);
	elem = NULL;
	return ;
}

void			release_report(t_report *report)
{
	ft_lstdel(report->lst_of_valid_paths, del_report);
	free(report->lst_of_valid_paths);
	report->lst_of_valid_paths = NULL;
	free(report);
	report = NULL;
	return ;
}
