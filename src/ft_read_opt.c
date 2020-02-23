/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_opt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 14:14:32 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/23 15:09:51 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		step_args(int *argc, char ***argv)
{
	(*argc)--;
	(*argv)++;
}

t_opt			ft_read_opt(int *argc, char ***argv)
{
	t_opt	opt;

	opt = 0;
	while (*argc)
	{
		if (ft_strequ((*argv)[*argc - 1], "-l"))
			opt |= leaks;
		else
			break ;
		step_args(argc, argv);
	}
	return (opt);
}