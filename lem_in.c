/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 12:08:07 by jkauppi           #+#    #+#             */
/*   Updated: 2020/03/28 21:34:21 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int						main(int argc, char **argv)
{
	int				return_code;
	t_input			input;
	t_report		*report;
	t_result		result;
	t_list			*elem;
	t_list			*tmp_elem;
	t_list			*algorithm_lst;
	t_list			*algorithm_elem;
	t_algorithm		algorithm;
	size_t			c;

	algorithm_lst = NULL;
	result.report_lst = (t_list **)ft_memalloc(sizeof(*result.report_lst));
	read_input_data(&input, &argc, &argv, e_lem_in);
	return_code = 1;
	if (input.error != invalid_connection_data && input.error)
		print_error(&input);
	else
	{
		calc_distance(&input);
		algorithm.function = (void *)select_paths;
		algorithm_elem = ft_lstnew(&algorithm, sizeof(&algorithm));
		ft_lstadd(&algorithm_lst, algorithm_elem);
		algorithm_elem = ft_lstnew(&algorithm, sizeof(algorithm));
		ft_lstadd(&algorithm_lst, algorithm_elem);
		algorithm_elem = algorithm_lst;
		while (algorithm_elem)
		{
			report = initialize_report(&input);
			algorithm = *(t_algorithm *)algorithm_elem->content;
			if (algorithm.function(&input, report))
			{
				elem = ft_lstnew(report, sizeof(*report));
				ft_lstadd(result.report_lst, elem);
				free(report);
				return_code = 0;
			}
			else
			{
				print_error(&input);
				release_report(report);
			}
			c = -1;
			while (++c < input.num_of_rooms)
				input.room_array[c]->is_visited = 0;
			algorithm_elem = algorithm_elem->next;
		}
	}
	elem = algorithm_lst;
	while (elem)
	{
		tmp_elem = elem->next;
		free(elem->content);
		free(elem);
		elem = tmp_elem;
	}
	print_result(&input, &result);
	release_result(&result);
	release_input(&input);
	if (input.opt & leaks)
		system("leaks lem-in");
	return (return_code);
}
