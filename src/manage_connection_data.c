/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_connection_data.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:23:43 by jkauppi           #+#    #+#             */
/*   Updated: 2020/03/12 12:13:02 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int				add_connection(t_input *input, char **splitted_line)
{
	t_list			*elem;
	t_room			*room1;
	t_room			*room2;
	int				result;

	room1 = get_room_2(splitted_line[0], input);
	room2 = get_room_2(splitted_line[1], input);
	if (room1 && room2 && room1 != room2)
	{
		elem = ft_lstnew(&room1, sizeof(&room1));
		ft_lstadd(&room2->connection_lst, elem);
		elem = ft_lstnew(&room2, sizeof(&room2));
		ft_lstadd(&room1->connection_lst, elem);
		result = 1;
	}
	else
		result = 0;
	return (result);
}

static int				validate_line(char *line, char ***splitted_line)
{
	size_t			c;

	*splitted_line = ft_strsplit(line, '-');
	c = 0;
	while ((*splitted_line)[c])
		c++;
	return (c == 2);
}

static void				set_error(t_input *input, char *line,
															t_input_error error)
{
	char			*error_line;
	t_list			*elem;

	if (input->opt && input->opt & errors)
	{
		error_line = ft_strjoin("#ERROR: ", line);
		elem = ft_lstnew(error_line, sizeof(char) *
												ft_strlen(error_line));
		ft_lstadd(input->valid_input_lines, elem);
	}
	else
		input->error = error;
	return ;
}

static t_read_status	validate_connection_data(char *line, t_input *input,
													t_read_status read_status)
{
	char			**splitted_line;

	if (validate_line(line, &splitted_line))
	{
		if (!add_connection(input, splitted_line))
			set_error(input, line, invalid_connection_data);
	}
	else
		set_error(input, line, invalid_connection_data);
	ft_arraydel(splitted_line);
	read_status = e_read_connection_data;
	return (read_status);
}

t_read_status			read_connection_data(char *line, t_input *input,
													t_read_status read_status)
{
	t_list			*elem;

	if (line[0] == '#')
		read_status = e_read_connection_data;
	else
	{
		read_status = validate_connection_data(line, input, read_status);
		elem = ft_lstnew(line, sizeof(*line) * (ft_strlen(line) + 1));
		ft_lstadd(input->valid_input_lines, elem);
	}
	return (read_status);
}
