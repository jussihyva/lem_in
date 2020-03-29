/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 15:25:14 by jkauppi           #+#    #+#             */
/*   Updated: 2020/03/29 06:04:12 by ubuntu           ###   ########.fr       */
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
	free(report);
	report = NULL;
	return ;
}

void			release_result(t_result *result)
{
	t_list			*elem;
	t_list			*tmp_elem;
	t_report		*report;

	elem = *result->report_lst;
	while (elem)
	{
		tmp_elem = elem->next;
		report = (t_report *)elem->content;
		release_report(report);
		free(elem);
		elem = tmp_elem;
	}
	free(result->report_lst);
	return ;
}
