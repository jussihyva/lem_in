/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_opt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 14:14:32 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/26 13:03:17 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		save_input_file(t_input *input, int *argc, char ***argv)
{
	if (*argc > 0)
	{
		if (!(input->opt & map_file))
		{
			input->input_file = ft_strdup(*argv[0]);
			input->opt |= map_file;
		}
		ft_step_args(argc, argv);
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
			ft_step_args(argc, argv);
			input->opt |= leaks;
		}
		else if (ft_strequ((*argv)[0], "-f"))
		{
			ft_step_args(argc, argv);
			save_input_file(input, argc, argv);
		}
		else
			break ;
	}
	return ;
}
