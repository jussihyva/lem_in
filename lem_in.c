/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 12:08:07 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/24 12:36:57 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_read_status	read_num_of_ants(char *line, t_input *input)
{
	char			*endptr;
	t_read_status	read_status;

	endptr = NULL;
	read_status = stop_reading;
	input->number_of_ants = ft_strtoi(line, &endptr, 10);
	if (errno || *endptr)
		input->error = num_of_ants_error;
	else
		read_status = read_room_name;
	ft_printf("%s\n", line);
	return (read_status);
}

static void				read_input_data(void)
{
	char			*line;
	int				ret;
	t_read_status	read_status;
	t_input			input;

	line = NULL;
	read_status = start_reading;
	input.error = 0;
	while ((ret = ft_get_next_line(0, &line)) > 0 && !input.error &&
													read_status != stop_reading)
	{
		if (read_status == start_reading)
			read_status = read_num_of_ants(line, &input);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	return ;
}

int						main(int argc, char **argv)
{
	int		return_code;
	t_opt	opt;

	argc--;
	argv++;
	opt = ft_read_opt(&argc, &argv);
	read_input_data();
	return_code = 0;
	if (opt & leaks)
		system("leaks lem-in");
	return (return_code);
}
