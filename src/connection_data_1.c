/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connection_data_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:23:43 by jkauppi           #+#    #+#             */
/*   Updated: 2020/05/05 09:53:37 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
	int				is_valid_line;

	is_valid_line = 0;
	if (line[0] == '#')
		is_valid_line = 1;
	else if (line[0] == '\0')
	{
		if (input->app == e_checker)
		{
			is_valid_line = 1;
			*read_status = e_read_instruction_data;
		}
		else
		{
			input->error = invalid_connection_data;
			set_error(input, line, input->error, "#ERROR ");
		}
	}
	else
		*read_status = validate_connection_data(line, input, *read_status);
	if (is_valid_line || !input->error)
	{
		elem = ft_lstnew(line, sizeof(*line) * (ft_strlen(line) + 1));
		ft_lstadd(input->valid_input_lines, elem);
	}
}
