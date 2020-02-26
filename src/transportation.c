/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transportation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 09:45:38 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/26 11:38:52 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void					del_path(void *room, size_t size)
{
	(void)size;
	free((t_room *)room);
	return ;
}

static t_list				*get_path(t_list *start_room_elem,
														t_list *end_room_elem)
{
	t_list			*path;
	t_list			*adj_room_elem;

	adj_room_elem = ((t_room *)end_room_elem->content)->connection_lst;
	if (adj_room_elem)
	{
		path = ft_lstnew(end_room_elem->content, end_room_elem->content_size);
		while (adj_room_elem)
		{
			ft_lstadd(&path, ft_lstnew(adj_room_elem->content,
												adj_room_elem->content_size));
			if (((t_room *)adj_room_elem->content)->id ==
									((t_room *)start_room_elem->content)->id)
				break ;
			else
				adj_room_elem =
							((t_room *)adj_room_elem->content)->connection_lst;
		}
	}
	else
		path = NULL;
	return (path);
}

static void					print_path(t_list *path)
{
	t_list		*elem;

	elem = path;
	while (elem)
	{
		ft_printf("%5s ", ((t_room *)elem->content)->name);
		elem = elem->next;
	}
	ft_printf("\n");
	return ;
}

t_transportation_report		ants_transportation(t_input *input)
{
	t_transportation_report		transportation_report;
	t_list						*path;

	transportation_report.error = 0;
	path = get_path(input->start_room, input->end_room);
	if (path)
	{
		print_path(path);
		ft_lstdel(&path, del_path);
	}
	return (transportation_report);
}
