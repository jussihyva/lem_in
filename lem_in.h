/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 13:51:44 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/23 17:46:34 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include <stdlib.h>
# include "ft_printf.h"
# include "libft.h"

typedef enum	e_opt
{
	leaks = 0x1
}				t_opt;

typedef struct		s_move_line
{
	s_move_action	move_action;
}			t_move_line;

typedef struct		s_room
{
	char	*name;
	int	coord_x;
	int	coord_y;
	int	id;
}			t_roon;

typedef struct		s_history
{
	size_t		line_nr;
	t_room		room;
	size_t		move_order;
}			t_history;

typedef struct		s_ant
{
	int		id;
	t_room		current_room;
	t_history	*room_history;
}			t_ant;

typedef struct		t_move_action
{
	s_ant		ant;
	s_room		room;
}

typedef struct		s_transportation
{
	t_ant		*ants;
	int128		*room_reservation;
	t_list		*move_lines;
}			t_transportation;

t_opt			ft_read_opt(int *argc, char ***argv);

#endif
