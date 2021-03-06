/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connection_data_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 14:11:01 by ubuntu            #+#    #+#             */
/*   Updated: 2020/06/01 09:55:19 by ubuntu           ###   ########.fr       */
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
	if (room1 == room2 && room1)
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

static int			sort_ascending(t_list *elem1, t_list *elem2)
{
	t_room		*room1;
	t_room		*room2;

	room1 = *(t_room **)elem1->content;
	room2 = *(t_room **)elem2->content;
	if (room1->num_of_conn_to_end < room2->num_of_conn_to_end)
		return (-1);
	else
		return (1);
}

static int			sort_descending(t_list *elem1, t_list *elem2)
{
	t_room		*room1;
	t_room		*room2;

	room1 = *(t_room **)elem1->content;
	room2 = *(t_room **)elem2->content;
	if (room1->num_of_conn_to_end < room2->num_of_conn_to_end)
		return (1);
	else
		return (-1);
}

void				sort_connections(t_output *output, t_sort_order sort_order)
{
	t_list			*elem;
	t_list			*new_elem;
	t_list			*connection_lst;
	t_room			*room;
	size_t			c;

	c = -1;
	while (++c < output->num_of_rooms)
	{
		connection_lst = NULL;
		room = output->room_array[c];
		elem = room->connection_lst;
		while (elem)
		{
			new_elem = ft_lstnew(elem->content, elem->content_size);
			if (sort_order == e_ascending)
				ft_lstadd_sort(&connection_lst, new_elem, sort_ascending);
			else
				ft_lstadd_sort(&connection_lst, new_elem, sort_descending);
			elem = elem->next;
		}
		ft_lstdel(&room->connection_lst, del_path);
		room->connection_lst = connection_lst;
	}
	return ;
}
