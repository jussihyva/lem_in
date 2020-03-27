/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pi <pi@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 12:08:07 by jkauppi           #+#    #+#             */
/*   Updated: 2020/03/21 13:23:50 by pi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int						main(int argc, char **argv)
{
	int				return_code;
	t_input			input;
	t_report		*report;

	read_input_data(&input, &argc, &argv, e_lem_in);
	return_code = 1;
	if (input.error != invalid_connection_data && input.error)
		print_error(&input);
	else
	{
		calc_distance(&input);
		report = initialize_report(&input);
		if (select_paths(&input, report))
		{
			print_result(&input, report);
			release_report(report);
			return_code = 0;
		}
		else
			print_error(&input);
	}
	if (input.opt & leaks)
		system("leaks lem-in");
	release_input(&input);
	return (return_code);
}
