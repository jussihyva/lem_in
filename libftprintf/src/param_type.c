/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 16:43:33 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/16 15:17:33 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void				check_type(t_list **type_list, t_substring *substring)
{
	t_list			*type_elem;
	char			*type_string;
	char			*start_ptr;

	type_elem = *type_list;
	while (type_elem)
	{
		type_string = ((t_param_type *)type_elem->content)->type_string;
		start_ptr = substring->end_ptr - ft_strlen(type_string) + 1;
		if (!(ft_strncmp(start_ptr, type_string, ft_strlen(type_string))))
		{
			substring->param_type = (t_param_type *)type_elem->content;
			substring->end_ptr = start_ptr - 1;
			break ;
		}
		type_elem = type_elem->next;
	}
	return ;
}

void					add_param_type(t_list **list, t_list **type_list)
{
	t_list			*elem;
	t_substring		*substring;

	elem = *list;
	while (elem)
	{
		substring = (t_substring *)elem->content;
		check_type(type_list, substring);
		elem = elem->next;
	}
}

static t_list			*new_type(t_type type, char *s)
{
	t_list			*type_elem;
	t_param_type	param_type;

	param_type.type = type;
	param_type.type_string = s;
	type_elem = ft_lstnew(&param_type, sizeof(param_type));
	return (type_elem);
}

t_list					**create_param_type_list(void)
{
	t_list			**type_list;

	type_list = (t_list **)ft_memalloc(sizeof(*type_list));
	ft_lstadd_e(type_list, new_type(hh, "hh"));
	ft_lstadd_e(type_list, new_type(h, "h"));
	ft_lstadd_e(type_list, new_type(ll, "ll"));
	ft_lstadd_e(type_list, new_type(l, "l"));
	ft_lstadd_e(type_list, new_type(j, "j"));
	ft_lstadd_e(type_list, new_type(z, "z"));
	ft_lstadd_e(type_list, new_type(t, "t"));
	ft_lstadd_e(type_list, new_type(L, "L"));
	return (type_list);
}
