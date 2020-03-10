/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 13:51:44 by jkauppi           #+#    #+#             */
/*   Updated: 2020/03/10 11:01:21 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include <stdlib.h>
# include "ft_printf.h"
# include "libft.h"
# include "limits.h"
# include "stdint.h"
# include "errno.h"
# include <fcntl.h>

typedef enum				e_read_status
{
	e_start_reading,
	e_num_of_ants,
	e_comment,
	e_read_start_room_data,
	e_read_end_room_data,
	e_read_room_data,
	e_read_connection_data,
	e_stop_reading
}							t_read_status;

typedef enum				e_opt
{
	leaks = 0x1,
	map_file = 0x2,
	verbose = 0x4
}							t_opt;

typedef struct				s_ant
{
	t_list			**path;
	t_list			*current_room_elem;
	char			*name;
}							t_ant;

typedef struct				s_room
{
	char			*name;
	int				coord_x;
	int				coord_y;
	size_t			id;
	t_list			*connection_lst;
	size_t			num_of_conn_to_end;
	t_ant			*ant;
}							t_room;

typedef enum				e_input_error
{
	file_open_failure = 1,
	num_of_ants_error,
	faulty_room_data,
	invalid_room_name,
	invalid_room_data,
	invalid_connection_data,
	input_file_missing
}							t_input_error;

typedef struct				s_input
{
	t_input_error	error;
	t_opt			opt;
	char			*input_file;
	t_list			**valid_input_lines;
	size_t			number_of_ants;
	t_room			**start_room_ptr;
	t_room			**end_room_ptr;
	t_list			*room_lst;
	t_room			**room_array;
	size_t			num_of_rooms;
}							t_input;

typedef struct				s_valid_path
{
	t_list			**path;
	size_t			num_of_conn_to_end;
	size_t			*visited_rooms;
}							t_valid_path;

typedef struct				s_report
{
	int				error;
	t_opt			opt;
	t_list			**lst_of_valid_paths;
	size_t			connection_counter;
	t_room			**end_room_ptr;
	t_ant			*ant_array;
	size_t			number_of_paths;
	size_t			number_of_ants;
}							t_report;

void						ft_read_opt(t_input *input, int *argc,
																char ***argv);
int							ft_strtoi(const char *str, char **endptr,
																	int base);
t_read_status				read_room_data(char *line, t_input *input,
													t_read_status read_status);
t_read_status				read_connection_data(char *line, t_input *input,
													t_read_status read_status);
void						ft_arraydel(char **array);
void						print_result(t_input *input, t_report *report);
void						ft_step_args(int *argc, char ***argv);
void						calc_distance(t_input *input);
void						del_report(void *room, size_t size);
void						del_path(void *room, size_t size);
void						print_line(t_input *input, char *line,
																int add_line);
void						is_road_to_start_room(t_room *room, t_input *input,
															t_report *report);
void						release_report(t_report *report);
void						validate_adj_rooms(size_t *connection_counter,
												t_input *input, t_room *room);
void						select_paths(t_input *input, t_report *report);
t_report					*initialize_report(t_input *input);
void						transportation(t_report *report);
void						print_instructions(t_report *report);
t_room						**add_room(char **splitted_line, t_input *input);
t_room						*get_room(char *name, t_room **room_array);
t_room						**create_room_array_1(t_input *input);
t_room						**create_room_array_2(t_input *input);

#endif
