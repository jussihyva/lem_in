/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pi <pi@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/20 18:59:24 by pi                #+#    #+#             */
/*   Updated: 2020/03/21 07:52:22 by pi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int				is_valid_line(t_input *input, char *line,
													t_read_status read_status)
{
	int			result;

	result = 1;
	if (read_status == e_read_num_of_ants)
	{
		if (line[0] == '\0')
			result = 0;
		else if (line[0] == '#' && line[1] == '#')
			result = 0;
		if (!result)
		{
			input->error = num_of_ants_error;
			set_error(input, line, num_of_ants_error, "#ERROR ");
		}
	}
	return (result);
}

static void				read_num_of_ants(char *line, t_input *input,
													t_read_status *read_status)
{
	char			*endptr;
	t_list			*elem;
	size_t			number_of_ants;

	elem = ft_lstnew(line, sizeof(*line) * (ft_strlen(line) + 1));
	ft_lstadd(input->valid_input_lines, elem);
	if (is_valid_line(input, line, *read_status))
	{
		if (line[0] == '#')
			;
		else
		{
			*read_status = e_read_room_data;
			endptr = NULL;
			number_of_ants = ft_strtoi(line, &endptr, 10);
			if (errno || *endptr)
			{
				input->error = num_of_ants_error;
				set_error(input, line, num_of_ants_error, "#ERROR ");
			}
			else if (!input->number_of_ants)
				input->number_of_ants = number_of_ants;
		}
	}
	return ;
}

static void				parse_line(char *line, t_input *input,
													t_read_status *read_status)
{
	if (*read_status == e_read_num_of_ants)
		read_num_of_ants(line, input, read_status);
	else
	{
		if (*read_status == e_read_room_data ||
					*read_status == e_read_start_room_data ||
					*read_status == e_read_end_room_data)
			*read_status = read_room_data(line, input, *read_status);
		if (*read_status == e_read_connection_data)
			*read_status = read_connection_data(line, input, *read_status);
	}
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
	input->number_of_ants = 0;
	input->input_line_cnt = 0;
	return ;
}

void					read_input_data(t_input *input, int *argc, char ***argv)
{
	t_read_status	read_status;
	char			*line;
	int				ret;
	int				fd;

	ft_step_args(argc, argv);
	init_input_structure(input);
	ft_read_opt(input, argc, argv);
	if (input->opt & map_file)
		fd = open(input->input_file, O_RDONLY);
	else
		fd = 0;
	line = NULL;
	if (fd < 0)
		input->error = file_open_failure;
	else
	{
		read_status = e_read_num_of_ants;
		while ((ret = ft_get_next_line(fd, &line)) > 0 && !input->error &&
												read_status != e_stop_reading)
		{
			input->input_line_cnt++;
			parse_line(line, input, &read_status);
			ft_strdel(&line);
		}
		ft_strdel(&line);
	}
	return ;
}
