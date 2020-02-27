/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 13:51:44 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/27 13:40:59 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include <stdlib.h>
# include "ft_printf.h"
# include "libft.h"
# include "limits.h"
# include "errno.h"
# include <fcntl.h>

typedef enum				e_read_status
{
	start_reading,
	num_of_ants,
	comment,
	read_start_room_data,
	read_end_room_data,
	read_room_data,
	read_connection_data,
	stop_reading
}							t_read_status;

typedef enum				e_opt
{
	leaks = 0x1,
	map_file = 0x2
}							t_opt;

typedef struct				s_room
{
	char			*name;
	int				coord_x;
	int				coord_y;
	size_t			id;
	t_list			*connection_lst;
}							t_room;

typedef struct				s_history
{
	size_t			line_nr;
	t_room			room;
	size_t			move_order;
}							t_history;

typedef struct				s_ant
{
	int				id;
	t_room			current_room;
	t_history		*room_history;
}							t_ant;

typedef struct				s_move_action
{
	t_ant			ant;
	t_room			room;
}							t_move_action;

typedef struct				s_move_line
{
	t_move_action	move_action;
}							t_move_line;

typedef struct				s_transportation
{
	t_ant			*ants;
	size_t			number_of_ants;
	int64_t			*room_reservation;
	t_list			*move_lines;
}							t_transportation;

typedef enum				e_input_error
{
	file_open_failure = 1,
	num_of_ants_error,
	faulty_room_data,
	invalid_room_data,
	invalid_connection_data,
	input_file_missing
}							t_input_error;

typedef struct				s_input
{
	t_input_error	error;
	t_opt			opt;
	char			*input_file;
	t_list			*valid_input_lines;
	size_t			number_of_ants;
	t_list			*start_room;
	t_list			*room_lst;
	t_room			**room_array;
	size_t			num_of_rooms;
	t_list			*end_room;
}							t_input;

typedef struct				s_report
{
	int				error;
	t_list			**path;
	size_t			number_of_rooms;
	t_room			**valid_path;
}							t_report;

void						ft_read_opt(t_input *input, int *argc,
																char ***argv);
int							ft_strtoi(const char *str, char **endptr,
																	int base);
t_read_status				get_room_data(char *line, t_input *input,
													t_read_status read_status);
t_read_status				get_connection_data(char *line, t_input *input,
													t_read_status read_status);
void						ft_arraydel(char **array);
void						print_result(t_input *input);
void						ft_step_args(int *argc, char ***argv);
t_report					*ants_transportation(t_input *input);

#endif
