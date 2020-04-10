/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 13:51:44 by jkauppi           #+#    #+#             */
/*   Updated: 2020/04/10 15:06:52 by ubuntu           ###   ########.fr       */
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
# include <stdio.h>

typedef enum				e_app
{
	e_lem_in,
	e_checker
}							t_app;

typedef enum				e_read_status
{
	e_read_num_of_ants,
	e_num_of_ants,
	e_comment,
	e_read_start_room_data,
	e_read_end_room_data,
	e_read_room_data,
	e_read_connection_data,
	e_read_instruction_data,
	e_stop_reading
}							t_read_status;

typedef enum				e_opt
{
	leaks = 0x01,
	map_file = 0x02,
	verbose = 0x04,
	verbose1 = 0x08,
	ants = 0x10,
	errors = 0x20
}							t_opt;

typedef struct				s_ant
{
	t_list			**path;
	t_list			*current_room_elem;
	void			*current_room;
	char			*name;
}							t_ant;

typedef struct				s_room
{
	char			*name;
	int				coord_x;
	int				coord_y;
	size_t			id;
	t_list			*connection_lst;
	int				num_of_conn_to_start;
	int				num_of_conn_to_end;
	size_t			num_of_connections;
	t_ant			*ant;
	int				is_visited;
	void			*prev_room;
	void			*next_room;
}							t_room;

typedef struct				s_instruction
{
	t_ant			*ant;
	t_room			*room;
}							t_instruction;

typedef struct				s_instruction_line
{
	t_list			**instruction_lst;
}							t_instruction_line;

typedef enum				e_input_error
{
	file_open_failure = 1,
	empty_line,
	unknown_order,
	num_of_ants_error,
	faulty_room_data,
	invalid_room_name,
	invalid_room_data,
	invalid_connection_data,
	input_file_missing,
	num_of_ants_missing,
	invalid_instruction_line,
	incorrect_move,
	no_path_available
}							t_input_error;

typedef struct				s_input
{
	t_app			app;
	t_input_error	error;
	t_opt			opt;
	char			*input_file;
	size_t			input_line_cnt;
	t_list			**valid_input_lines;
	size_t			number_of_ants;
	t_room			*start_room_ptr;
	t_room			*end_room_ptr;
	t_list			*room_lst;
	t_room			**room_array;
	t_list			**instruction_line_lst;
	size_t			num_of_rooms;
	t_list			**algorithm_lst;
}							t_input;

typedef enum				e_validity
{
	no_room = 0,
	valid_room,
	valid,
	invalid,
	many
}							t_validity;

typedef struct				s_valid_path
{
	size_t			id;
	t_list			**path;
	t_validity		validity;
	int				num_of_conn_to_end;
	size_t			num_of_ants;
	size_t			*room_vector;
}							t_valid_path;

typedef struct				s_output
{
	int				error;
	t_opt			opt;
	t_list			**lst_of_valid_paths;
	t_valid_path	**valid_paths;
	t_list			**lst_of_selectd_paths;
	t_list			**instruction_line_lst;
	size_t			number_of_instruction_line;
	size_t			connection_counter;
	t_room			*start_room_ptr;
	t_room			*end_room_ptr;
	size_t			num_of_rooms;
	size_t			number_of_paths;
	size_t			number_of_selected_paths;
	t_ant			**ant_array;
	size_t			number_of_ants;
	int				first;
}							t_output;

typedef struct				s_algorithm
{
	void			*(*function)(t_output *output);
}							t_algorithm;

typedef struct				s_result
{
	t_list			**output_lst;
}							t_result;

void						ft_read_opt(t_input *input, int *argc,
																char ***argv);
int							ft_strtoi(const char *str, char **endptr,
																	int base);
void						read_room_data(char *line, t_input *input,
													t_read_status *read_status);
void						read_connection_data(char *line, t_input *input,
													t_read_status *read_status);
void						ft_arraydel(char **array);
size_t						ft_lstlen(t_list **lst);
void						print_output(t_input *input, t_output *output);
void						ft_step_args(int *argc, char ***argv);
void						calc_distance(t_input *input);
void						del_output(void *room, size_t size);
void						del_path(void *room, size_t size);
void						ft_lstdel_1(t_list **lst_ptr);
void						is_road_to_start_room(t_room *room, t_input *input,
															t_output *output);
void						release_output(t_output *output);
void						release_input(t_input *input);
void						validate_adj_rooms(size_t *connection_counter,
												t_input *input, t_room *room);
int							select_paths(t_output *output);
t_output					*initialize_output(t_input *input);
void						transportation(t_output *output);
t_room						**add_room(char **splitted_line, t_input *input);
t_room						*get_room(char *name, t_input *input);
t_room						**create_room_array_2(t_input *input);
void						set_error(t_input *input, char *line,
											t_input_error error, char *text);
void						print_path(t_list **path_lst);
int							put_ants_to_paths(t_output *output);
t_valid_path				*create_valid_path(t_list **path,
														t_validity validity);
void						delete_valid_path(t_output *output, t_list *elem);
void						update_valid_path(t_valid_path *valid_path);
size_t						count_max_num_of_paths(t_output *output);
void						preliminary_path_selection(t_output *output,
										size_t max_num_of_paths, int *offset);
t_validity					add_rooms_to_path(t_output *output, t_list **path,
																	int offset);
void						finalize_path_selection(t_output *output,
																int *offset);
void						read_input_data(t_input *input, t_output **output,
													int *argc, char ***argv);
void						print_error(t_input *input);
void						print_ok(t_input *input);
void						print_input_lines(t_input *input);
void						read_instruction_data(char *line, t_input *input,
															t_output **output);
t_ant						*get_ant(char *name, t_output *output);
void						create_ants(t_output *output);
int							validate_instructions(t_input *input);
void						update_instructions(t_output *output);
void						print_instructions(t_output *output);
int							move_ant(t_instruction *instruction,
														t_room *end_room_ptr);
int							move_ant_next_room(t_output *output, size_t c,
														int *first_instruction);
void						release_result(t_result *result);
void						print_result(t_input *input, t_result *result);
void						select_algorithms(t_list **algorithm_lst);
void						read_num_of_ants(char *line, t_input *input,
													t_read_status *read_status);
void						add_valid_input_line(t_list **valid_input_lines,
																	char *line);
void						init_input_structure(t_input *input, t_app app);
int							algorithm_ford_fulkerson1(t_output *output);
int							algorithm_ford_fulkerson2(t_output *output);
int							algorithm_ford_fulkerson3(t_output *output);
int							algorithm_ford_fulkerson4(t_output *output);
void						add_line(t_list **instruction_line_lst, char *line);
void						set_ants_to_start_room(t_output *output);
int							create_new_valid_path(t_output *output,
																t_room *room);
void						add_room_to_paths(t_output *output, t_room *room,
									t_room *start_room, size_t num_of_paths);
void						release(t_input *input, t_result *result);
void						sort_valid_paths(t_list **lst_of_valid_paths,
													t_valid_path **valid_paths);
int							get_next_room(t_output *output,
										t_room *current_room,
										t_room *start_room, t_room *end_room);
void						select_best_group(t_list **path_lst,
							size_t *merged_room_vector, t_output *output,
							size_t path_index);
void						ft_lstrem(t_list **lst, t_list *elem);
size_t						count_num_of_instruction_lines(t_list **path_lst,
							size_t number_of_ants, size_t nr_instruction_lines);
void						add_connection(t_input *input, char **splitted_line,
																	char *line);
void						sort_connections(t_input *input);
void						ft_lstadd_sort(t_list **alst, t_list *new,
									int (*cmp)(t_list *elem1, t_list *elem2));
int							trace_path(t_room *current_room, t_room *start_room,
															t_room *end_room);

#endif
