/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 13:51:44 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/24 12:41:07 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include <stdlib.h>
# include "ft_printf.h"
# include "libft.h"
# include "limits.h"
# include "errno.h"

typedef enum		e_read_status
{
	start_reading,
	num_of_ants,
	comment,
	read_start_room,
	read_end_room,
	read_room_name,
	read_connection,
	stop_reading
}					t_read_status;

typedef enum		e_opt
{
	leaks = 0x1
}					t_opt;

typedef struct		s_room
{
	char			*name;
	int				coord_x;
	int				coord_y;
	int				id;
}					t_room;

typedef struct		s_history
{
	size_t			line_nr;
	t_room			room;
	size_t			move_order;
}					t_history;

typedef struct		s_ant
{
	int				id;
	t_room			current_room;
	t_history		*room_history;
}					t_ant;

typedef struct		s_move_action
{
	t_ant			ant;
	t_room			room;
}					t_move_action;

typedef struct		s_move_line
{
	t_move_action	move_action;
}					t_move_line;

typedef struct		s_transportation
{
	t_ant			*ants;
	size_t			number_of_ants;
	int64_t			*room_reservation;
	t_list			*move_lines;
}					t_transportation;

typedef enum		e_input_error
{
	num_of_ants_error = 1
}					t_input_error;

typedef struct		s_input
{
	t_input_error	error;
	size_t			number_of_ants;
}					t_input;

t_opt				ft_read_opt(int *argc, char ***argv);
int					ft_strtoi(const char *str, char **endptr, int base);

#endif
