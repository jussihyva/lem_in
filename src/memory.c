/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 15:25:14 by jkauppi           #+#    #+#             */
/*   Updated: 2020/02/28 10:39:07 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			del_path(void *room, size_t size)
{
	(void)size;
	(void)room;
	return ;
}

void			del_path_2(void *room, size_t size)
{
	(void)size;
	free(room);
	room = NULL;
	return ;
}
