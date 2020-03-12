/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_opt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 14:14:32 by jkauppi           #+#    #+#             */
/*   Updated: 2020/03/12 10:28:09 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		save_num_of_ants(t_input *input, int *argc, char ***argv)
{
	if (*argc > 1)
	{
		if (!(input->opt & ants))
		{
			input->number_of_ants = (size_t)ft_atoi((*argv)[1]);
			input->opt |= ants;
		}
		ft_step_args(argc, argv);
	}
	else
		input->error = num_of_ants_missing;
	return ;
}

static void		save_input_file(t_input *input, int *argc, char ***argv)
{
	if (*argc > 1)
	{
		if (!(input->opt & map_file))
		{
			input->input_file = ft_strdup((*argv)[1]);
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
			input->opt |= leaks;
		else if (ft_strequ((*argv)[0], "-v"))
			input->opt |= verbose;
		else if (ft_strequ((*argv)[0], "-e"))
			input->opt |= errors;
		else if (ft_strequ((*argv)[0], "-f"))
			save_input_file(input, argc, argv);
		else if (ft_strequ((*argv)[0], "-a"))
			save_num_of_ants(input, argc, argv);
		else
			break ;
		ft_step_args(argc, argv);
	}
	return ;
}
