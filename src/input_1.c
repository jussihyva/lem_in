/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/20 18:59:24 by pi                #+#    #+#             */
/*   Updated: 2020/04/13 19:32:47 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int			is_valid_line(t_input *input, char *line,
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

static void			parse_line(char *line, t_input *input, t_output **output,
													t_read_status *read_status)
{
	input->input_line_cnt++;
	if (is_valid_line(input, line, *read_status))
	{
		if (*read_status == e_read_num_of_ants)
		{
			if (line[0] == '#')
				add_valid_input_line(input->valid_input_lines, line);
			else
				read_num_of_ants(line, input, read_status);
		}
		else if (input->number_of_ants)
		{
			if (*read_status == e_read_room_data ||
						*read_status == e_read_start_room_data ||
						*read_status == e_read_end_room_data)
				read_room_data(line, input, read_status);
			else if (*read_status == e_read_connection_data)
				read_connection_data(line, input, read_status);
			else if (*read_status == e_read_instruction_data)
				read_instruction_data(line, input, output);
		}
	}
	ft_strdel(&line);
	return ;
}

void				init_input_structure(t_input *input, t_app app)
{
	input->app = app;
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
	input->algorithm_lst =
				(t_list **)ft_memalloc(sizeof(*input->algorithm_lst));
	input->number_of_ants = 0;
	input->room_array = NULL;
	input->input_file = NULL;
	input->num_of_rooms = 0;
	input->input_line_cnt = 0;
	return ;
}

static int			open_fd(t_input *input)
{
	int		fd;

	fd = 0;
	if (input->opt & map_file)
		fd = open(input->input_file, O_RDONLY);
	return (fd);
}

void				read_input_data(t_input *input, t_output **output,
											int *argc, char ***argv)
{
	t_read_status	read_status;
	char			*line;
	int				ret;
	int				fd;

	*output = NULL;
	ft_step_args(argc, argv);
	select_algorithms(input->algorithm_lst);
	ft_read_opt(input, argc, argv);
	fd = open_fd(input);
	line = NULL;
	if (fd < 0)
		input->error = file_open_failure;
	read_status = e_read_num_of_ants;
	while ((ret = ft_get_next_line(fd, &line)) > 0 && !input->error &&
											read_status != e_stop_reading)
		parse_line(line, input, output, &read_status);
	ft_strdel(&line);
	if (!input->room_array && input->num_of_rooms)
	{
		input->room_array = create_room_array_2(input);
		input->error = no_connection_data;
	}
	return ;
}
