/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/20 13:27:08 by pi                #+#    #+#             */
/*   Updated: 2020/03/31 12:08:02 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			main(int argc, char **argv)
{
	int				return_code;
	t_input			input;
	t_result		result;
	t_output		*output;

	init_input_structure(&input, e_checker);
	output = NULL;
	return_code = 0;
	result.output_lst = (t_list **)ft_memalloc(sizeof(*result.output_lst));
	read_input_data(&input, output, &argc, &argv);
	if (input.error)
		print_error(&input);
	else
	{
		print_instruction(&input);
		if (!validate_instructions(&input))
			print_error(&input);
	}
	return (return_code);
}
