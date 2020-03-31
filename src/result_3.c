/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   result_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/31 10:12:47 by ubuntu            #+#    #+#             */
/*   Updated: 2020/03/31 10:13:56 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			print_result(t_input *input, t_result *result)
{
	t_list			*elem;
	t_output		*output;

	elem = *result->output_lst;
	while (elem)
	{
		output = (t_output *)elem->content;
		print_output(input, output);
		elem = elem->next;
	}
	return ;
}
