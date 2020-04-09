/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connection_data_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 14:11:01 by ubuntu            #+#    #+#             */
/*   Updated: 2020/04/09 14:12:39 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int			is_dublicate(t_room *room1, t_room *room2)
{
	t_list			*elem;

	elem = room1->connection_lst;
	while (elem)
	{
		if (room2 == *(t_room **)elem->content)
			return (1);
		elem = elem->next;
	}
	return (0);
}

void				add_connection(t_input *input, char **splitted_line,
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
		if (!is_dublicate(room1, room2))
		{
			elem = ft_lstnew(&room1, sizeof(&room1));
			room1->num_of_connections++;
			ft_lstadd_e(&room2->connection_lst, elem);
			elem = ft_lstnew(&room2, sizeof(&room2));
			room2->num_of_connections++;
			ft_lstadd_e(&room1->connection_lst, elem);
		}
	}
	else
		set_error(input, line, invalid_connection_data, "#ERROR: ");
	return ;
}
