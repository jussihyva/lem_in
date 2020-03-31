/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/29 12:20:21 by ubuntu            #+#    #+#             */
/*   Updated: 2020/03/31 09:10:21 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_output		*initialize_output(t_input *input)
{
	t_output		*output;

	output = (t_output *)ft_memalloc(sizeof(*output));
	output->error = 0;
	output->opt = input->opt;
	output->lst_of_valid_paths =
					(t_list **)ft_memalloc(sizeof(*output->lst_of_valid_paths));
	output->instruction_line_lst =
				(t_list **)ft_memalloc(sizeof(*output->instruction_line_lst));
	output->number_of_ants = input->number_of_ants;
	output->end_room_ptr = input->end_room_ptr;
	output->start_room_ptr = input->start_room_ptr;
	output->number_of_paths = 0;
	create_ants(output);
	return (output);
}
