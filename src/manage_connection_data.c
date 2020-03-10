/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_connection_data.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:23:43 by jkauppi           #+#    #+#             */
/*   Updated: 2020/03/10 09:51:13 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void				add_connection(t_room *room1, t_room *room2)
{
	t_list		*elem;

	elem = ft_lstnew(&room1, sizeof(room1));
	ft_lstadd(&room2->connection_lst, elem);
	elem = ft_lstnew(&room2, sizeof(room2));
	ft_lstadd(&room1->connection_lst, elem);
	return ;
}

static t_read_status	validate_connection_data(char *line, t_input *input,
													t_read_status read_status)
{
	char			**splitted_line;
	size_t			c;
	t_room			*room1;
	t_room			*room2;

	splitted_line = ft_strsplit(line, '-');
	c = 0;
	while (splitted_line[c])
		c++;
	if (c == 2)
	{
		room1 = get_room(splitted_line[0], input->room_array);
		room2 = get_room(splitted_line[1], input->room_array);
		if (room1 && room2)
			add_connection(room1, room2);
		else
			input->error = invalid_connection_data;
	}
	else
		input->error = invalid_connection_data;
	ft_arraydel(splitted_line);
	read_status = read_connection_data;
	return (read_status);
}

t_read_status			get_connection_data(char *line, t_input *input,
													t_read_status read_status)
{
	t_list			*elem;

	if (line[0] == '#')
		read_status = read_connection_data;
	else
	{
		read_status = validate_connection_data(line, input, read_status);
		elem = ft_lstnew(line, sizeof(*line) * (ft_strlen(line) + 1));
		if (*input->valid_input_lines)
			ft_lstadd(input->valid_input_lines, elem);
		else
			*input->valid_input_lines = elem;
	}
	return (read_status);
}
