/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_distance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 09:59:20 by jkauppi           #+#    #+#             */
/*   Updated: 2020/03/10 20:48:09 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

// static void					validate_adj_rooms_1(size_t *connection_counter,
// 												t_input *input, t_room *room)
// {
// 	t_room			*next_room;
// 	t_list			*adj_room_elem;

// 	(*connection_counter)++;
// 	room->num_of_conn_to_end = *connection_counter;
// 	adj_room_elem = room->connection_lst;
// 	while (adj_room_elem)
// 	{
// 		next_room = *(t_room **)adj_room_elem->content;
// 		if (next_room != *input->end_room_ptr)
// 		{
// 			if (!next_room->num_of_conn_to_end ||
// 				next_room->num_of_conn_to_end > (*connection_counter + 1))
// 				validate_adj_rooms_1(connection_counter, input, next_room);
// 		}
// 		adj_room_elem = adj_room_elem->next;
// 	}
// 	(*connection_counter)--;
// 	return ;
// }

static void					add_new_rooms(t_input *input, t_list *elem,
					t_list **new_room_element_lst, size_t connection_counter)
{
	t_room			*next_room;
	t_list			*new_elem;
	t_list			*tmp_elem;

	next_room = *(t_room **)elem->content;
	if (next_room != *input->end_room_ptr)
	{
		if (!next_room->num_of_conn_to_end)
		{
			next_room->num_of_conn_to_end = connection_counter;
			new_elem = next_room->connection_lst;
			while (new_elem)
			{
				tmp_elem = ft_lstnew(new_elem->content, new_elem->content_size);
				ft_lstadd(new_room_element_lst, tmp_elem);
				new_elem = new_elem->next;
			}
		}
	}
	return ;
}

static void					validate_adj_rooms_2(t_input *input,
												t_list **new_room_element_lst)
{
	t_list			*current_room_element_lst;
	t_list			*elem;
	size_t			connection_counter;

	connection_counter = 0;
	while (*new_room_element_lst)
	{
		connection_counter++;
		current_room_element_lst = *new_room_element_lst;
		*new_room_element_lst = NULL;
		elem = current_room_element_lst;
		while (elem)
		{
			add_new_rooms(input, elem, new_room_element_lst,
															connection_counter);
			elem = elem->next;
		}
		ft_lstdel(&current_room_element_lst, del_path);
	}
	return ;
}

void						calc_distance(t_input *input)
{
	t_room			*room;
	t_list			*new_room_element_lst;
	t_list			*elem;
	t_list			*tmp_elem;

	room = *input->end_room_ptr;
	new_room_element_lst = NULL;
	elem = room->connection_lst;
	while (elem)
	{
		tmp_elem = ft_lstnew(elem->content, elem->content_size);
		ft_lstadd(&new_room_element_lst, tmp_elem);
		elem = elem->next;
	}
	validate_adj_rooms_2(input, &new_room_element_lst);
//	validate_adj_rooms_1(&connection_counter, input, room);
	return ;
}
