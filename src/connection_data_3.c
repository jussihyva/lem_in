/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connection_data_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 14:54:33 by ubuntu            #+#    #+#             */
/*   Updated: 2020/05/03 14:59:16 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void					release_connection_array(t_output *output)
{
	size_t			i1;
	size_t			i2;

	i1 = -1;
	while (++i1 < output->num_of_rooms)
	{
		i2 = -1;
		while (++i2 < output->num_of_rooms)
		{
			if (output->connection_array[i1][i2])
			{
				free(output->connection_array[i1][i2]);
				output->connection_array[i1][i2] = NULL;
				output->connection_array[i2][i1] = NULL;
			}
		}
		free(output->connection_array[i1]);
	}
	free(output->connection_array);
	output->connection_array = NULL;
	return ;
}

void					create_connection_array(t_output *output)
{
	size_t		i;

	output->connection_array =
			(t_connection ***)ft_memalloc(sizeof(*output->connection_array) *
														output->num_of_rooms);
	i = -1;
	while (++i < output->num_of_rooms)
		output->connection_array[i] =
			(t_connection **)ft_memalloc(sizeof(**output->connection_array) *
														output->num_of_rooms);
	return ;
}

static t_connection		*create_connection(t_room *room)
{
	t_connection	*connection;

	connection = (t_connection *)ft_memalloc(sizeof(*connection));
	connection->capazity = 1;
	connection->owner_room = room;
	return (connection);
}

void					initialize_connection_array(t_output *output)
{
	t_room			*room;
	t_room			*adj_room;
	size_t			p;
	t_list			*elem;
	t_connection	*connection;

	create_connection_array(output);
	p = -1;
	while (++p < output->num_of_rooms)
	{
		room = output->room_array[p];
		elem = room->connection_lst;
		while (elem)
		{
			adj_room = *(t_room **)elem->content;
			if (!output->connection_array[room->id][adj_room->id])
			{
				connection = create_connection(room);
				output->connection_array[room->id][adj_room->id] = connection;
				output->connection_array[adj_room->id][room->id] = connection;
			}
			elem = elem->next;
		}
	}
	return ;
}
