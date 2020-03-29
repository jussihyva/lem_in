/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   report.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/29 12:20:21 by ubuntu            #+#    #+#             */
/*   Updated: 2020/03/29 12:35:51 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_report		*initialize_report(t_input *input)
{
	t_report		*report;

	report = (t_report *)ft_memalloc(sizeof(*report));
	report->error = 0;
	report->opt = input->opt;
	report->lst_of_valid_paths =
				(t_list **)ft_memalloc(sizeof(*report->lst_of_valid_paths));
	report->number_of_ants = input->number_of_ants;
	report->end_room_ptr = input->end_room_ptr;
	report->start_room_ptr = input->start_room_ptr;
//	report->ant_array = input->ant_array;
	create_ants(input, report);
	return (report);
}

