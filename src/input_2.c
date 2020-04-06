/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/29 05:30:49 by ubuntu            #+#    #+#             */
/*   Updated: 2020/04/06 17:59:33 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				add_valid_input_line(t_list **valid_input_lines, char *line)
{
	t_list			*elem;

	elem = ft_lstnew(line, sizeof(*line) * (ft_strlen(line) + 1));
	ft_lstadd(valid_input_lines, elem);
	return ;
}

void				select_algorithms(t_list **algorithm_lst)
{
	t_algorithm		algorithm;
	t_list			*elem;

	*algorithm_lst = NULL;
	// algorithm.function = (void *)select_paths;
	// elem = ft_lstnew(&algorithm, sizeof(&algorithm));
	// ft_lstadd(algorithm_lst, elem);
	// algorithm.function = (void *)algorithm_ford_fulkerson1;
	// elem = ft_lstnew(&algorithm, sizeof(algorithm));
	// ft_lstadd(algorithm_lst, elem);
	// algorithm.function = (void *)algorithm_ford_fulkerson2;
	// elem = ft_lstnew(&algorithm, sizeof(algorithm));
	// ft_lstadd(algorithm_lst, elem);
	algorithm.function = (void *)algorithm_ford_fulkerson3;
	elem = ft_lstnew(&algorithm, sizeof(algorithm));
	ft_lstadd(algorithm_lst, elem);
	return ;
}
