/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width_and_prediction.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 13:16:14 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/09 11:17:15 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		save_width_and_prediction(char **ptr,
												t_list *substring_elem)
{
	if (**ptr == '.')
	{
		((t_substring *)substring_elem->content)->precision =
													ft_atoi(*ptr + 1);
		(*ptr)--;
		while (**ptr && ft_isdigit(**ptr))
			(*ptr)--;
		((t_substring *)substring_elem->content)->width =
													ft_atoi(*ptr + 1);
	}
	else
	{
		((t_substring *)substring_elem->content)->precision = -1;
		((t_substring *)substring_elem->content)->width =
													ft_atoi(*ptr + 1);
	}
	if (*(*ptr + 1) == '0')
		(*ptr)++;
	return ;
}

void			add_width_and_prediction(t_list **substring_list)
{
	t_list			*substring_elem;
	char			*ptr;

	substring_elem = *substring_list;
	while (substring_elem)
	{
		ptr = ((t_substring *)substring_elem->content)->end_ptr;
		while (*ptr && (ft_isdigit(*ptr)))
			ptr--;
		if (*ptr == '.' ||
					ptr < ((t_substring *)substring_elem->content)->end_ptr)
		{
			save_width_and_prediction(&ptr, substring_elem);
		}
		((t_substring *)substring_elem->content)->end_ptr = ptr;
		substring_elem = substring_elem->next;
	}
	return ;
}
