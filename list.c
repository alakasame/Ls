/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 02:06:00 by cmichaud          #+#    #+#             */
/*   Updated: 2016/02/05 22:33:32 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_l		*listadd(t_l *list, char *arg)
{
	t_l *tmp;

	tmp = list;
	if (!(list))
	{
		if (!(list = (t_l *)malloc(sizeof(t_l))))
			return (0);
		list->str = ft_strdup(arg);
		list->next = NULL;
		return (list);
	}
	while (list->next != NULL)
		list = list->next;
	if (!(list->next = (t_l *)malloc(sizeof(t_l))))
		return (0);
	list = list->next;
	list->next = NULL;
	list->str = ft_strdup(arg);
	list = tmp;
	return (list);
}
