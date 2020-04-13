/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_distance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 09:59:20 by jkauppi           #+#    #+#             */
/*   Updated: 2020/04/13 19:13:24 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void					add_new_rooms(t_input *input, t_list *elem,
					t_list **new_room_element_lst, size_t connection_counter)
{
	t_room			*next_room;
	t_room			*new_room;
	t_list			*new_elem;
	t_list			*tmp_elem;

	next_room = *(t_room **)elem->content;
	if (next_room != input->end_room_ptr)
	{
		if (!next_room->num_of_conn_to_end)
		{
			next_room->num_of_conn_to_end = connection_counter;
			new_elem = next_room->connection_lst;
			while (new_elem)
			{
				new_room = *(t_room **)new_elem->content;
				if (new_room == input->start_room_ptr)
					next_room->num_of_conn_to_start = 1;
				tmp_elem = ft_lstnew(new_elem->content, new_elem->content_size);
				ft_lstadd(new_room_element_lst, tmp_elem);
				new_elem = new_elem->next;
			}
		}
	}
	return ;
}

void						ft_lstdel_1(t_list **lst_ptr)
{
	t_list		*elem;
	t_list		*next_elem;

	if (lst_ptr)
	{
		elem = *lst_ptr;
		while (elem)
		{
			next_elem = elem->next;
			free((t_room **)elem->content);
			free(elem);
			elem = next_elem;
		}
		*lst_ptr = NULL;
	}
	return ;
}

static void					validate_adj_rooms_2(t_input *input,
												t_list **new_room_element_lst)
{
	t_list			**current_room_element_lst;
	t_list			*elem;
	size_t			connection_counter;

	current_room_element_lst =
					(t_list **)ft_memalloc(sizeof(*current_room_element_lst));
	connection_counter = 0;
	while (*new_room_element_lst)
	{
		connection_counter++;
		*current_room_element_lst = *new_room_element_lst;
		*new_room_element_lst = NULL;
		elem = *current_room_element_lst;
		while (elem)
		{
			add_new_rooms(input, elem, new_room_element_lst,
															connection_counter);
			elem = elem->next;
		}
		ft_lstdel_1(current_room_element_lst);
	}
	free(current_room_element_lst);
	return ;
}

void						calc_distance(t_input *input)
{
	t_room			*room;
	t_list			**new_room_element_lst;
	t_list			*elem;
	t_list			*tmp_elem;
	size_t			c;

	sort_connections(input);
	new_room_element_lst =
						(t_list **)ft_memalloc(sizeof(*new_room_element_lst));
	room = input->end_room_ptr;
	elem = room->connection_lst;
	c = 0;
	while (elem)
	{
		tmp_elem = ft_lstnew(elem->content, sizeof(elem->content_size));
		ft_lstadd_e(new_room_element_lst, tmp_elem);
		elem = elem->next;
		c++;
	}
	validate_adj_rooms_2(input, new_room_element_lst);
	free(new_room_element_lst);
	return ;
}
