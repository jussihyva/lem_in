/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_data_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 15:50:13 by jkauppi           #+#    #+#             */
/*   Updated: 2020/06/11 09:40:25 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static char				*create_mod_line(t_room *room)
{
	char			*mod_line;
	char			*s;

	mod_line = (char *)ft_memalloc(sizeof(*mod_line) * 10000);
	ft_strcat(mod_line, room->name);
	ft_strcat(mod_line, " ");
	s = ft_itoa(room->coord_x);
	ft_strcat(mod_line, s);
	ft_strdel(&s);
	ft_strcat(mod_line, " ");
	s = ft_itoa(room->coord_y);
	ft_strcat(mod_line, s);
	ft_strdel(&s);
	return (mod_line);
}

static void				add_input_line(t_input *input, char *line, int add_line)
{
	t_list			*elem;
	t_room			*room;
	char			*mod_line;

	if (add_line)
	{
		if (add_line == 1)
		{
			elem = ft_lstnew(line, sizeof(*line) * (ft_strlen(line) + 1));
			ft_lstadd(input->valid_input_lines, elem);
		}
		else
		{
			room = *(t_room **)input->room_lst->content;
			mod_line = create_mod_line(room);
			elem = ft_lstnew(mod_line, sizeof(*mod_line) *
													(ft_strlen(mod_line) + 1));
			ft_lstadd(input->valid_input_lines, elem);
			ft_strdel(&mod_line);
		}
	}
	return ;
}

static t_read_status	validate_room_data(char *line, t_input *input,
													t_read_status read_status)
{
	char			**splitted_line;
	size_t			c;
	t_room			**room_ptr;

	splitted_line = ft_strsplit(line, ' ');
	c = 0;
	while (splitted_line[c])
		c++;
	if (c == 3)
	{
		room_ptr = add_room(splitted_line, input);
		if (read_status == e_read_start_room_data)
			input->start_room_ptr = *room_ptr;
		else if (read_status == e_read_end_room_data)
			input->end_room_ptr = *room_ptr;
	}
	else
		input->error = invalid_room_data;
	ft_arraydel(splitted_line);
	read_status = e_read_room_data;
	return (read_status);
}

void					read_room_data(char *line, t_input *input,
													t_read_status *read_status)
{
	int				add_line;

	add_line = 1;
	if (ft_strequ(line, "##start"))
		*read_status = e_read_start_room_data;
	else if (ft_strequ(line, "##end"))
		*read_status = e_read_end_room_data;
	else if (line[0] != '#')
	{
		add_line = 2;
		*read_status = validate_room_data(line, input, *read_status);
		if (input->error == invalid_room_data)
		{
			add_line = 1;
			input->room_array = create_room_array_2(input);
			input->error = 0;
			*read_status = e_read_connection_data;
			read_connection_data(line, input, read_status);
			return ;
		}
	}
	add_input_line(input, line, add_line);
	return ;
}
