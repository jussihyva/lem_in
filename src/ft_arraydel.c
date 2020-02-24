/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraydel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:06:33 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/24 16:06:36 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_arraydel(char **array)
{
	size_t		i;

	i = -1;
	while (*(array + ++i))
		ft_strdel(array + i);
	free(array);
	array = 0;
	return ;
}
