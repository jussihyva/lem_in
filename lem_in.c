/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 12:08:07 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/25 16:38:57 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_read_status	get_num_of_ants(char *line, t_input *input)
{
	char			*endptr;
	t_read_status	read_status;

	endptr = NULL;
	read_status = stop_reading;
	input->number_of_ants = ft_strtoi(line, &endptr, 10);
	if (errno || *endptr)
		input->error = num_of_ants_error;
	else
		read_status = read_room_data;
	return (read_status);
}

static void				init_input_structure(t_input *input)
{
	input->error = 0;
	input->input_file = NULL;
	input->opt = 0;
	input->start_room = NULL;
	input->room_lst = NULL;
	input->end_room = NULL;
	input->valid_input_lines = NULL;
	input->number_of_ants = 0;
	return ;
}

static int				open_input_file(t_input *input)
{
	int		fd;

	if (input->opt & map_file)
		fd = open(input->input_file, O_RDONLY);
	else
		fd = 0;
	return (fd);
}

static void				read_input_data(t_input *input,
											int fd, t_read_status read_status)
{
	char			*line;
	int				ret;
	t_list			*elem;

	line = NULL;
	while ((ret = ft_get_next_line(fd, &line)) > 0 && !input->error &&
													read_status != stop_reading)
	{
		if (read_status == start_reading)
			read_status = get_num_of_ants(line, input);
		else
		{
			if (read_status == read_room_data ||
						read_status == read_start_room_data ||
						read_status == read_end_room_data)
				read_status = get_room_data(line, input, read_status);
			if (read_status == read_connection_data)
				read_status = get_connection_data(line, input, read_status);
		}
		elem = ft_lstnew(line, sizeof(*line) * (ft_strlen(line) + 1));
		ft_lstadd_e(&input->valid_input_lines, elem);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	return ;
}

int						main(int argc, char **argv)
{
	int				return_code;
	t_input			input;
	t_read_status	read_status;
	int				fd;

	argc--;
	argv++;
	init_input_structure(&input);
	ft_read_opt(&input, &argc, &argv);
	read_status = start_reading;
	fd = open_input_file(&input);
	read_input_data(&input, fd, read_status);
	if (!input.error)
	{
		ft_printf("Number of ants: %20d\n", input.number_of_ants);
		print_result(&input);
	}
	return_code = 0;
	if (input.opt & leaks)
		system("leaks lem-in");
	return (return_code);
}
