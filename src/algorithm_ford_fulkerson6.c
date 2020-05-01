/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_ford_fulkerson6.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 19:23:52 by ubuntu            #+#    #+#             */
/*   Updated: 2020/05/01 19:57:20 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void				create_connection_array(t_output *output)
{
	size_t		c;

	output->connection_array =
			(t_connection ***)ft_memalloc(sizeof(**output->connection_array));
	c = -1;
	while (++c < output->num_of_rooms)
		output->connection_array[c] =
			(t_connection **)ft_memalloc(sizeof(*output->connection_array));
	return;
}

static void				initialize_connection_array(t_output *output)
{
	t_room		*room;
	size_t		c;

	create_connection_array(output);
	c = -1;
	while (++c < output->num_of_rooms)
	{
		room = output->room_array[c];
//		ft_printf("Room: %s\n", room->name);
	}
	return ;
}

static void				create_connections(t_output *output)
{
	initialize_connection_array(output);
	return ;
}

int						algorithm_ford_fulkerson6(t_output *output)
{
	output->lst_of_selectd_paths =
				(t_list **)ft_memalloc(sizeof(*output->lst_of_selectd_paths));
	create_connections(output);
	return (1);
}
