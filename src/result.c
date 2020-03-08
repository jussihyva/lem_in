/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   result.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 09:28:18 by jkauppi           #+#    #+#             */
/*   Updated: 2020/03/08 09:36:16 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		print_room_data(t_room *room)
{
	t_list		*elem;

	ft_printf("Room: %10d %20s %5d %5d\n",
	room->id, room->name, room->coord_x, room->coord_y);
	elem = room->connection_lst;
	while (elem)
	{
		ft_printf("%60s\n", (*(t_room **)elem->content)->name);
		elem = elem->next;
	}
	return ;
}

void			print_line(t_input *input, char *line, int add_line)
{
	t_list			*elem;
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
			mod_line = (char *)ft_memalloc(sizeof(*mod_line) * 100);
			ft_sprintf(mod_line, "%s %d %d",
							(*((t_room **)input->room_lst->content))->name,
							(*((t_room **)input->room_lst->content))->coord_x,
							(*((t_room **)input->room_lst->content))->coord_y);
			elem = ft_lstnew(mod_line, sizeof(*mod_line) *
													(ft_strlen(mod_line) + 1));
			ft_lstadd(input->valid_input_lines, elem);
			ft_strdel(&mod_line);
		}
	}
	return ;
}

static void		print_valid_paths(t_list **lst_of_valid_paths)
{
	t_list			*elem;
	t_valid_path	*valid_path;

	elem = *lst_of_valid_paths;
	while (elem)
	{
		valid_path = (t_valid_path *)elem->content;
		print_path(valid_path->path);
		elem = elem->next;
	}
	return ;
}

void			print_path(t_room **path)
{
	size_t			c;
	static size_t	path_cnt;

	path_cnt++;
	ft_printf("Path: %5d:  ", path_cnt);
	c = 0;
	while (path[c])
	{
		ft_printf("%5s ", path[c]->name);
		c++;
	}
	ft_printf("\n");
	return ;
}

void			print_result(t_input *input, t_report *report)
{
	size_t		c;
	t_room		**room;
	t_list		*elem;

	room = input->room_array;
	if (input->opt & verbose)
	{
		c = 0;
		while (room[c])
		{
			print_room_data(room[c]);
			c++;
		}
	}
	elem = *input->valid_input_lines;
	while (elem)
	{
		ft_printf("%s\n", (char *)elem->content);
		elem = elem->next;
	}
	ft_printf("\nL1-3 L2-2\n");
	if (input->opt & verbose && *report->lst_of_valid_paths)
		print_valid_paths(report->lst_of_valid_paths);
	return ;
}
