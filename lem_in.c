/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 12:08:07 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/23 15:21:27 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		read_input_data(void)
{
	char	*line;
	int		ret;

	line = NULL;
	while ((ret = ft_get_next_line(0, &line)) > 0)
	{
		ft_putendl(line);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	return ;
}

int				main(int argc, char **argv)
{
	int		return_code;
	t_opt	opt;

	argc--;
	argv++;
	opt = ft_read_opt(&argc, &argv);
	read_input_data();
	return_code = 0;
	if (opt & leaks)
		system("leaks lem-in");
	return (return_code);
}
