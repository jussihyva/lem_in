/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 12:08:07 by jkauppi           #+#    #+#             */
/*   Updated: 2020/03/10 13:44:41 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_read_status	read_num_of_ants(char *line, t_input *input)
{
	char			*endptr;
	t_read_status	read_status;
	t_list			*elem;

	if (line[0] == '#')
		read_status = e_start_reading;
	else
	{
		read_status = e_read_room_data;
		elem = ft_lstnew(line, sizeof(*line) * (ft_strlen(line) + 1));
		ft_lstadd(input->valid_input_lines, elem);
		endptr = NULL;
		if (!input->number_of_ants)
		{
			input->number_of_ants = ft_strtoi(line, &endptr, 10);
			if (errno || *endptr)
			{
				input->error = num_of_ants_error;
				read_status = e_stop_reading;
			}
		}
	}
	return (read_status);
}

static void				init_input_structure(t_input *input)
{
	input->error = 0;
	input->input_file = NULL;
	input->opt = 0;
	input->start_room_ptr = NULL;
	input->room_lst = NULL;
	input->end_room_ptr = NULL;
	input->valid_input_lines =
					(t_list **)ft_memalloc(sizeof(*input->valid_input_lines));
	input->number_of_ants = 0;
	input->number_of_ants = 0;
	return ;
}

static t_read_status	parse_line(char *line, t_input *input,
													t_read_status read_status)
{
	if (read_status == e_start_reading)
		read_status = read_num_of_ants(line, input);
	else
	{
		if (read_status == e_read_room_data ||
					read_status == e_read_start_room_data ||
					read_status == e_read_end_room_data)
			read_status = read_room_data(line, input, read_status);
		if (read_status == e_read_connection_data)
			read_status = read_connection_data(line, input, read_status);
	}
	return (read_status);
}

static void				read_input_data(t_input *input,
													t_read_status read_status)
{
	char		*line;
	int			ret;
	int			fd;

	if (input->opt & map_file)
		fd = open(input->input_file, O_RDONLY);
	else
		fd = 0;
	line = NULL;
	if (fd < 0)
		input->error = file_open_failure;
	else
	{
		while ((ret = ft_get_next_line(fd, &line)) > 0 && !input->error &&
												read_status != e_stop_reading)
		{
			read_status = parse_line(line, input, read_status);
			ft_strdel(&line);
		}
		ft_strdel(&line);
	}
	return ;
}

int						main(int argc, char **argv)
{
	int				return_code;
	t_input			input;
	t_report		*report;

	ft_step_args(&argc, &argv);
	init_input_structure(&input);
	ft_read_opt(&input, &argc, &argv);
	read_input_data(&input, e_start_reading);
	return_code = 1;
	if (input.error)
		ft_printf("ERROR\n");
	else
	{
		calc_distance(&input);
		report = initialize_report(&input);
		select_paths(&input, report);
		transportation(report);
		print_result(&input, report);
		release_report(report);
		return_code = 0;
	}
	if (input.opt & leaks)
		system("leaks lem-in");
	return (return_code);
}
