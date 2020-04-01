/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/20 13:27:08 by pi                #+#    #+#             */
/*   Updated: 2020/04/01 08:08:50 by ubuntu           ###   ########.fr       */
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
	read_input_data(&input, &output, &argc, &argv);
	if (input.error)
		print_error(&input);
	else
	{
		if (validate_instructions(&input))
			print_ok(&input);
		else
			print_error(&input);
	}
	release_output(output);
	release_input(&input);
	if (input.opt & leaks)
		system("leaks lem-in");
	return (return_code);
}
