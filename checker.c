/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pi <pi@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/20 13:27:08 by pi                #+#    #+#             */
/*   Updated: 2020/03/26 09:57:23 by pi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			main(int argc, char **argv)
{
	int			return_code;
	t_input		input;

	return_code = 0;
	read_input_data(&input, &argc, &argv, e_checker);
	if (input.error)
		print_error(&input);
	else
	{
		print_instruction(&input);
		validate_instructions(&input);
	}
	return (return_code);
}
