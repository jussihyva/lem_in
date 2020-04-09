/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   result_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/31 10:12:47 by ubuntu            #+#    #+#             */
/*   Updated: 2020/04/09 12:55:37 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			print_result(t_input *input, t_result *result)
{
	t_list			*elem;
	t_output		*output;
	t_output		*best_output;

	best_output = NULL;
	elem = *result->output_lst;
	while (elem)
	{
		output = (t_output *)elem->content;
		if (output->number_of_paths)
		{
			update_instructions(output);
			if (!best_output || output->number_of_instruction_line <
											best_output->number_of_instruction_line)
				best_output = output;
			if (output->opt && output->opt & verbose)
				print_output(input, output);
		}
		elem = elem->next;
	}
	if (best_output && !(output->opt && output->opt & verbose))
		print_output(input, best_output);
	return ;
}
