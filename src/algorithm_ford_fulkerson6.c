/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_ford_fulkerson6.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 19:23:52 by ubuntu            #+#    #+#             */
/*   Updated: 2020/05/02 01:48:29 by ubuntu           ###   ########.fr       */
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
	return;
}

static void				create_connection_array(t_output *output)
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
	return;
}

static void				initialize_connection_array(t_output *output)
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
				connection = (t_connection *)ft_memalloc(sizeof(*connection));
				connection->capazity = 1;
				connection->owner_room = room;
				output->connection_array[room->id][adj_room->id] = connection;
				output->connection_array[adj_room->id][room->id] = connection;
			}
			elem = elem->next;
		}
//		ft_printf("Room: %s\n", room->name);
	}
	return ;
}

static void				create_connections(t_output *output)
{
	initialize_connection_array(output);
	return ;
}

static int				trace_path_1(t_output *output, t_room *current_room,
											t_room *prev_room, size_t conn_cnt)
{
	t_list			*elem;
	t_room			*adj_room;
	t_connection	*connection;
	int				flow_step;
	int				go_back;

	go_back = 0;
	current_room->is_visited = 1;
	elem = current_room->connection_lst;
	while (elem)
	{
		adj_room = *(t_room **)elem->content;
		connection = output->connection_array[current_room->id][adj_room->id];
		if (current_room == connection->owner_room)
			flow_step = 1;
		else
			flow_step = -1;
		if ((connection->flow == 1 || connection->flow == -1) && adj_room != prev_room &&
			!(connection->flow - flow_step) && !adj_room->is_visited)
			go_back = 1;
		elem = elem->next;
	}
	elem = current_room->connection_lst;
	while (elem && go_back)
	{
		adj_room = *(t_room **)elem->content;
		connection = output->connection_array[current_room->id][adj_room->id];
		if (current_room == connection->owner_room)
			flow_step = 1;
		else
			flow_step = -1;
		if ((connection->flow == 1 || connection->flow == -1) && adj_room != prev_room &&
			!(connection->flow + flow_step) && !adj_room->is_visited)
		{
			ft_printf(" %5s(%d:%d)", adj_room->name, adj_room->num_of_conn_to_end, connection->flow);
			connection->flow += flow_step;
			if (trace_path_1(output, adj_room, current_room, conn_cnt + 1))
			{
				current_room->is_visited = 0;
				return (1);
			}
			else
			{
				current_room->is_visited = 0;
				return (0);
			}
		}
		elem = elem->next;
	}
	elem = current_room->connection_lst;
	while (elem)
	{
		adj_room = *(t_room **)elem->content;
		connection = output->connection_array[current_room->id][adj_room->id];
		if (current_room == connection->owner_room)
			flow_step = 1;
		else
			flow_step = -1;
		if (adj_room == output->end_room_ptr &&
					(connection->flow + flow_step) < 2 && (connection->flow + flow_step) > -2)
		{
			ft_printf(" %s(%d):%d", adj_room->name, connection->flow, conn_cnt);
			connection->flow += flow_step;
			current_room->is_visited = 0;
			return (1);
		}
		else if (adj_room != prev_room && adj_room != output->start_room_ptr &&
					(connection->flow + flow_step) < 2 && (connection->flow + flow_step) > -2 &&
					!adj_room->is_visited)
		{
			ft_printf(" %5s(%d:%d)", adj_room->name, adj_room->num_of_conn_to_end, connection->flow);
			connection->flow += flow_step;
			if (trace_path_1(output, adj_room, current_room, conn_cnt + 1))
			{
				current_room->is_visited = 0;
				return (1);
			}
		}
		elem = elem->next;
	}
	current_room->is_visited = 0;
	return (0);
}

int						algorithm_ford_fulkerson6(t_output *output)
{
	t_room			*start_room;
	t_room			*adj_room;
	t_list			*elem;
	t_connection	*connection;

	output->lst_of_selectd_paths =
				(t_list **)ft_memalloc(sizeof(*output->lst_of_selectd_paths));
	create_connections(output);
	start_room = output->start_room_ptr;
	elem = start_room->connection_lst;
	while (elem)
	{
		adj_room = *(t_room **)elem->content;
		connection = output->connection_array[start_room->id][adj_room->id];
		ft_printf(" %5s(%d:%d)", adj_room->name, adj_room->num_of_conn_to_end, connection->flow);
		trace_path_1(output, adj_room, start_room, 1);
		ft_printf("\n\n");
		elem = elem->next;
	}
	return (1);
}
