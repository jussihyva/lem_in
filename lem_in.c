/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 12:08:07 by jkauppi           #+#    #+#             */
/*   Updated: 2020/03/29 19:48:05 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void				prepare_input_data(t_input *input)
{
	size_t			c;

	c = -1;
	while (++c < input->num_of_rooms)
		input->room_array[c]->is_visited = 0;
	return ;
}

static int				run_algorithms(t_input *input, t_result *result)
{
	t_list			*algorithm_elem;
	int				return_code;
	t_output		*output;
	t_algorithm		algorithm;
	t_list			*elem;

	return_code = 1;
	algorithm_elem = *input->algorithm_lst;
	while (algorithm_elem)
	{
		prepare_input_data(input);
		output = initialize_output(input);
		algorithm = *(t_algorithm *)algorithm_elem->content;
		if (algorithm.function(input, output))
		{
			elem = ft_lstnew(output, sizeof(*output));
			ft_lstadd(result->output_lst, elem);
			free(output);
			return_code = 0;
		}
		else
			release_output(output);
		algorithm_elem = algorithm_elem->next;
	}
	return (return_code);
}

int						main(int argc, char **argv)
{
	int				return_code;
	t_input			input;
	t_result		result;
	t_output		*output;

	init_input_structure(&input, e_lem_in);
	result.output_lst = (t_list **)ft_memalloc(sizeof(*result.output_lst));
	output = NULL;
	read_input_data(&input, output, &argc, &argv);
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
