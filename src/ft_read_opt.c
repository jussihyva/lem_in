/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_opt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 14:14:32 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/25 16:54:23 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		step_args(int *argc, char ***argv)
{
	(*argc)--;
	(*argv)++;
}

static void		save_input_file(t_input *input, int *argc, char ***argv)
{
	step_args(argc, argv);
	if (*argc > 0)
	{
		input->input_file = ft_strdup(*argv[0]);
		input->opt |= map_file;
		step_args(argc, argv);
	}
	else
		input->error = input_file_missing;
	return ;
}

void			ft_read_opt(t_input *input, int *argc, char ***argv)
{
	while (*argc)
	{
		if (ft_strequ((*argv)[0], "-l"))
		{
			input->opt |= leaks;
			step_args(argc, argv);
		}
		else if (ft_strequ((*argv)[0], "-f"))
			save_input_file(input, argc, argv);
		else
			break ;
	}
	return ;
}
