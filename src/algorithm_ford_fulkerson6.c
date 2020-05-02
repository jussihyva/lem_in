/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_ford_fulkerson6.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 19:23:52 by ubuntu            #+#    #+#             */
/*   Updated: 2020/05/02 19:02:01 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void				print_valid_paths(t_output *output)
{
	t_valid_path	*path;
	t_list			*room_elem;
	size_t			c;
	size_t			i;
	t_room			*room;

	c = 0;
	ft_printf("\n");
	while (c < output->number_of_paths)
	{
		path = (t_valid_path *)output->valid_paths[c];
		ft_printf("%3d %3d", c, path->num_of_conn_to_end);
		room_elem = *path->room_lst;
		i = 25;
		while (room_elem && i--)
		{
			room = *(t_room **)room_elem->content;
			ft_printf(" %s", room->name);
			room_elem = room_elem->next;
		}
		ft_printf("\n");
		c++;
	}
	return ;
}

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
		if (connection->flow != 0  && adj_room != prev_room &&
			!(connection->flow - flow_step) && !adj_room->is_visited && !adj_room->is_blocked)
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
		if (connection->flow != 0 && adj_room != prev_room &&
			!(connection->flow + flow_step) && !adj_room->is_visited && !adj_room->is_blocked)
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
				current_room->is_blocked = 1;
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
					!adj_room->is_visited && !adj_room->is_blocked)
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
	current_room->is_blocked = 1;
	return (0);
}

// static int					is_capazity(t_connection *connection, t_room *room)
// {
// 	int				flow_step;

// 	if (room == connection->owner_room)
// 		flow_step = 1;
// 	else
// 		flow_step = -1;
// 	if (!connection->flow || !(connection->flow - flow_step))
// 		return (1);
// 	else
// 		return (0);
// }

static t_valid_path		*initialize_path(t_output *output, t_validity validity)
{
	static int		id;
	t_valid_path	*path;

	path = (t_valid_path *)ft_memalloc(sizeof(*path));
	path->room_lst = (t_list **)ft_memalloc(sizeof(*path->room_lst));
	path->room_vector = (size_t *)ft_memalloc(sizeof(*path->room_vector) *
											((output->num_of_rooms / 32) + 1));
	path->id = id++;
	path->validity = validity;
	path->num_of_conn_to_end = 0;
	return (path);
}

static void					save_path(t_output *output, t_room *room, size_t level)
{
	t_room			*source_room;
	t_room			*parent_room;
	t_valid_path	*path;

	(void)level;
	path = initialize_path(output, valid_room);
	parent_room = room->parent_room;
	ft_lstadd(path->room_lst, ft_lstnew(&output->end_room_ptr, sizeof(output->end_room_ptr)));
	ft_lstadd(path->room_lst, ft_lstnew(&room, sizeof(room)));
	path->room_vector[room->id / 32] |= 1 << (room->id % 32);
	path->num_of_conn_to_end++;
	room->num_of_conn_to_end = path->num_of_conn_to_end;
	while (parent_room->parent_room)
	{
		path->room_vector[parent_room->id / 32] |= 1 << (parent_room->id % 32);
		ft_lstadd(path->room_lst, ft_lstnew(&parent_room, sizeof(parent_room)));
		source_room = parent_room;
		path->num_of_conn_to_end++;
		parent_room->num_of_conn_to_end = path->num_of_conn_to_end;
		parent_room = parent_room->parent_room;
	}
	ft_lstadd(path->room_lst, ft_lstnew(&output->start_room_ptr, sizeof(output->start_room_ptr)));
	path->num_of_conn_to_end++;
	ft_lstadd_e(output->lst_of_valid_paths, ft_lstnew(&path, sizeof(path)));
//	ft_printf("%5s %5d\n", source_room->name, path->num_of_conn_to_end);
	return ;
}

static void				reset_level_counter(t_room **room_array, size_t num_of_rooms)
{
	t_room		*room;
	size_t		i;

	i = -1;
	while (++i < num_of_rooms)
	{
		room = room_array[i];
		room->num_of_conn_to_start = -1;
	}
	return ;
}

static void					bfs(t_output *output, t_list **room_elem_lst, size_t level)
{
	t_list			*elem;
	t_list			*adj_elem;
	t_room			*room;
	t_room			*adj_room;
	t_list			*new_room_elem_lst;
	t_connection	*connection;

	new_room_elem_lst = NULL;
	elem = *room_elem_lst;
	while (elem)
	{
		room = *(t_room **)elem->content;
		adj_elem = room->connection_lst;
		while (adj_elem)
		{
			adj_room = *(t_room **)adj_elem->content;
			connection = output->connection_array[room->id][adj_room->id];
			if (adj_room == output->end_room_ptr)
				save_path(output, room, level);
			else if (adj_room->num_of_conn_to_start == -1)
			{
				adj_room->num_of_conn_to_start = level;
				adj_room->parent_room = room;
				ft_lstadd(&new_room_elem_lst, ft_lstnew(&adj_room, sizeof(adj_room)));
			}
			adj_elem = adj_elem->next;
		}
		elem = elem->next;
	}
	if (new_room_elem_lst)
	{
		ft_lstdel(room_elem_lst, del_path);
		*room_elem_lst = new_room_elem_lst;
		bfs(output, room_elem_lst, level + 1);
	}
	return ;
}

static void				breadth_first_search(t_output *output)
{
	t_list			**room_elem_lst;
	t_list			*elem;
	t_room			*room;
	size_t			level;

	reset_level_counter(output->room_array, output->num_of_rooms);
	room_elem_lst = (t_list **)ft_memalloc(sizeof(*room_elem_lst));
	room = output->start_room_ptr;
	level = 0;
	room->num_of_conn_to_start = level;
	elem = room->connection_lst;
	while (elem)
	{
		room = *(t_room **)elem->content;
		*room_elem_lst = ft_lstnew(&room, sizeof(room));
		level = 1;
		room->num_of_conn_to_start = level;
		room->parent_room = output->start_room_ptr;
		bfs(output, room_elem_lst, level + 1);
		ft_lstdel(room_elem_lst, del_path);
		reset_level_counter(output->room_array, output->num_of_rooms);
		room = output->start_room_ptr;
		level = 0;
		room->num_of_conn_to_start = level;
		elem = elem->next;
	}
	free(room_elem_lst);
	return ;
}

int						algorithm_ford_fulkerson6(t_output *output)
{
	t_room			*start_room;
	t_room			*adj_room;
	t_list			*elem;
	t_connection	*connection;
	int				flow_step;
	t_list				*new_path_lst;
	size_t				*merged_room_vector;

	merged_room_vector = (size_t *)ft_memalloc(sizeof(*merged_room_vector) *
											((output->num_of_rooms / 32) + 1));
	output->lst_of_selectd_paths =
				(t_list **)ft_memalloc(sizeof(*output->lst_of_selectd_paths));
	create_connections(output);
	start_room = output->start_room_ptr;
	breadth_first_search(output);
	sort_connections(output);
	elem = start_room->connection_lst;
	while (1 == 2)
	{
		adj_room = *(t_room **)elem->content;
		connection = output->connection_array[start_room->id][adj_room->id];
		if (!connection->flow)
		{
			if (start_room == connection->owner_room)
				flow_step = 1;
			else
				flow_step = -1;
			ft_printf("%s %5s(%d:%d)", start_room->name, adj_room->name,
							adj_room->num_of_conn_to_end, connection->flow);
			connection->flow += flow_step;
			trace_path_1(output, adj_room, start_room, 1);
			ft_printf("\n\n");
			break ;
		}
		elem = elem->next;
	}
	output->number_of_paths = ft_lstlen(output->lst_of_valid_paths);
	output->valid_paths =
					(t_valid_path **)ft_memalloc(sizeof(*output->valid_paths) *
													output->number_of_paths);
	sort_valid_paths(output->lst_of_valid_paths, output->valid_paths);
	if (output->opt && output->opt & verbose1)
		print_valid_paths(output);
	new_path_lst = NULL;
	select_best_group(&new_path_lst, merged_room_vector, output, 0);
//	ft_printf("MOI\n");
	ft_lstdel(&new_path_lst, del_path);
	output->number_of_paths = ft_lstlen(output->lst_of_selectd_paths);
	put_ants_to_paths(output);
	return (1);
}
