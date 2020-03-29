/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connection_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:23:43 by jkauppi           #+#    #+#             */
/*   Updated: 2020/03/29 19:55:11 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void				add_connection(t_input *input, char **splitted_line,
																	char *line)
{
	t_list			*elem;
	t_room			*room1;
	t_room			*room2;

	room1 = get_room(splitted_line[0], input);
	room2 = get_room(splitted_line[1], input);
	if (room1 == room2)
		set_error(input, line, 0, "#WARNING: ");
	else if (room1 && room2)
	{
		elem = ft_lstnew(&room1, sizeof(&room1));
		room1->num_of_connections++;
		ft_lstadd(&room2->connection_lst, elem);
		elem = ft_lstnew(&room2, sizeof(&room2));
		room2->num_of_connections++;
		ft_lstadd(&room1->connection_lst, elem);
	}
	else
		set_error(input, line, invalid_connection_data, "#ERROR: ");
	return ;
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

static t_read_status	validate_connection_data(char *line, t_input *input,
													t_read_status read_status)
{
	char			**splitted_line;

	if (validate_line(line, &splitted_line))
	{
		add_connection(input, splitted_line, line);
		read_status = e_read_connection_data;
	}
	else
	{
		set_error(input, line, invalid_connection_data, "#ERROR: ");
		read_status = e_stop_reading;
	}
	ft_arraydel(splitted_line);
	return (read_status);
}

void					read_connection_data(char *line, t_input *input,
										t_read_status *read_status)
{
	t_list			*elem;

	elem = ft_lstnew(line, sizeof(*line) * (ft_strlen(line) + 1));
	ft_lstadd(input->valid_input_lines, elem);
	if (line[0] == '#')
		;
	else if (line[0] == '\0')
	{
		if (input->app == e_checker)
			*read_status = e_read_instruction_data;
		else
		{
			input->error = invalid_connection_data;
			set_error(input, line, input->error, "#ERROR ");
		}
	}
	else
		*read_status = validate_connection_data(line, input, *read_status);
	return ;
}
