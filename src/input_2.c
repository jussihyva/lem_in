/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/29 05:30:49 by ubuntu            #+#    #+#             */
/*   Updated: 2020/03/29 05:30:59 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				select_algorithms(t_list **algorithm_lst)
{
	t_algorithm		algorithm;
	t_list			*elem;

	*algorithm_lst = NULL;
	algorithm.function = (void *)select_paths;
	elem = ft_lstnew(&algorithm, sizeof(&algorithm));
	ft_lstadd(algorithm_lst, elem);
	elem = ft_lstnew(&algorithm, sizeof(algorithm));
	ft_lstadd(algorithm_lst, elem);
	return ;
}
