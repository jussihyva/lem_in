/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 12:08:07 by jkauppi           #+#    #+#             */
/*   Updated: 2020/03/29 07:03:37 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void				prepare_input_data(t_input *input)
{
	size_t			c;

	c = -1;
	while (++c < input->num_of_rooms)
		input->room_array[c]->is_visited = 0;
	update_ants(input->ant_array, input->number_of_ants, input->start_room_ptr);
	return ;
}

static int				run_algorithms(t_input *input, t_result *result)
{
	t_list			*algorithm_elem;
	int				return_code;
	t_report		*report;
	t_algorithm		algorithm;
	t_list			*elem;

	return_code = 1;
	algorithm_elem = *input->algorithm_lst;
	while (algorithm_elem)
	{
		prepare_input_data(input);
		report = initialize_report(input);
		algorithm = *(t_algorithm *)algorithm_elem->content;
		if (algorithm.function(input, report))
		{
			elem = ft_lstnew(report, sizeof(*report));
			ft_lstadd(result->report_lst, elem);
			free(report);
			return_code = 0;
		}
		else
			release_report(report);
		algorithm_elem = algorithm_elem->next;
	}
	return (return_code);
}

int						main(int argc, char **argv)
{
	int				return_code;
	t_input			input;
	t_result		result;

	result.report_lst = (t_list **)ft_memalloc(sizeof(*result.report_lst));
	read_input_data(&input, &argc, &argv, e_lem_in);
	return_code = 1;
	if (input.error != invalid_connection_data && input.error)
		print_error(&input);
	else
	{
		calc_distance(&input);
		if (!(return_code = run_algorithms(&input, &result)))
			print_result(&input, &result);
	}
	release_result(&result);
	release_input(&input);
	if (input.opt & leaks)
		system("leaks lem-in");
	return (return_code);
}
