/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pi <pi@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/20 18:59:24 by pi                #+#    #+#             */
/*   Updated: 2020/03/27 09:41:21 by pi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int				is_valid_line(t_input *input, char *line,
													t_read_status read_status)
{
	t_list			*elem;

	if (line[0] == '\0')
	{
		if (read_status != e_read_connection_data)
			input->error = empty_line;
	}
	if (input->error)
	{
		elem = ft_lstnew(line, sizeof(*line) * (ft_strlen(line) + 1));
		ft_lstadd(input->valid_input_lines, elem);
		set_error(input, line, input->error, "#ERROR ");
		return (0);
	}
	else
		return (1);
}

static void				read_num_of_ants(char *line, t_input *input,
													t_read_status *read_status)
{
	char			*endptr;
	t_list			*elem;
	size_t			number_of_ants;

	if (line[0] == '#')
	{
		elem = ft_lstnew(line, sizeof(*line) * (ft_strlen(line) + 1));
		ft_lstadd(input->valid_input_lines, elem);
	}
	else
	{
		*read_status = e_read_room_data;
		number_of_ants = ft_strtoi(line, &endptr, 10);
		if (errno || *endptr)
		{
			input->error = num_of_ants_error;
			set_error(input, line, num_of_ants_error, "#ERROR ");
			elem = ft_lstnew(line, sizeof(*line) * (ft_strlen(line) + 1));
			ft_lstadd(input->valid_input_lines, elem);
		}
		else
			create_ants(input, number_of_ants);
	}
	return ;
}

static void				parse_line(char *line, t_input *input,
										t_read_status *read_status, t_app app)
{
	input->input_line_cnt++;
	if (is_valid_line(input, line, *read_status))
	{
		if (*read_status == e_read_num_of_ants)
			read_num_of_ants(line, input, read_status);
		else
		{
			if (*read_status == e_read_room_data ||
						*read_status == e_read_start_room_data ||
						*read_status == e_read_end_room_data)
				read_room_data(line, input, read_status, app);
			else if (*read_status == e_read_connection_data)
				read_connection_data(line, input, read_status, app);
			else if (*read_status == e_read_instruction_data)
				read_instruction_data(line, input);
		}
	}
	ft_strdel(&line);
	return ;
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
	input->instruction_line_lst =
				(t_list **)ft_memalloc(sizeof(*input->instruction_line_lst));
	input->number_of_ants = 0;
	input->num_of_rooms = 0;
	input->input_line_cnt = 0;
	return ;
}

void					read_input_data(t_input *input, int *argc, char ***argv,
																	t_app app)
{
	t_read_status	read_status;
	char			*line;
	int				ret;
	int				fd;

	ft_step_args(argc, argv);
	init_input_structure(input);
	ft_read_opt(input, argc, argv);
	fd = 0;
	if (input->opt & map_file)
		fd = open(input->input_file, O_RDONLY);
	line = NULL;
	if (fd < 0)
		input->error = file_open_failure;
	else
	{
		read_status = e_read_num_of_ants;
		while ((ret = ft_get_next_line(fd, &line)) > 0 && !input->error &&
												read_status != e_stop_reading)
			parse_line(line, input, &read_status, app);
		ft_strdel(&line);
	}
	return ;
}
