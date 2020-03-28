/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/28 11:24:35 by ubuntu            #+#    #+#             */
/*   Updated: 2020/03/28 11:25:23 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
