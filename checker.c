/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/20 13:27:08 by pi                #+#    #+#             */
/*   Updated: 2020/03/29 19:22:44 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			main(int argc, char **argv)
{
	int				return_code;
	t_input			input;
	t_result		result;

	return_code = 0;
	result.output_lst = (t_list **)ft_memalloc(sizeof(*result.output_lst));
	read_input_data(&input, &result, &argc, &argv, e_checker);
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
