/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 02:06:00 by cmichaud          #+#    #+#             */
/*   Updated: 2016/02/09 11:35:13 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_l		*listdelone(t_l *list)
{
	t_l	*tmp;

	tmp = list->next;
	free(list->str);
	list = tmp;
	return (list);
}

t_l		*insertlist(t_l **list, t_l **base, t_l **back, char *str)
{
	t_l		*tmp;

	ft_putstr(str);
	tmp = listadd(NULL, str, NULL, NULL);
	tmp->next = (*base);
	if (back)
	{
		(*back)->next = tmp;
		return ((*list));		
	}
	return (tmp);
}

t_l		*no_sort(t_l **tmp, char *str)
{
	t_l		*list;
	t_l		*listnext;

	list = (*tmp);
	if (ft_strcmp(list->str, str) > 0)
	{
		if (!(listnext = (t_l *)malloc(sizeof(t_l))))
			return (0);
		listnext->str = ft_strdup(str);
		listnext->next = list;
		return (listnext);
	}
	listnext = list->next;
	while (listnext != NULL)
	{
		if (ft_strcmp(listnext->str, str) > 0)
		{
			listnext = listadd(NULL, str, NULL, NULL);
			listnext->str = ft_strdup(str);
			listnext->next = list->next;
			list->next = listnext;
			return ((*tmp));
		}			
		list = listnext;
		listnext = list->next;
	}
	if (!(listnext = (t_l *)malloc(sizeof(t_l))))
		return (0);
	listnext->str = ft_strdup(str);
	listnext->next = list->next;
	list->next = listnext;
	return ((*tmp));
}

t_l		*list_tr(t_l **list, char *file, char *path, char *flag)
{
	t_l	*base;
	t_l *tmp;
	t_l *nl;
	int i;

//	ft_putstr("LIST_TR\n");
	i = 0;
	base = (*list);
	tmp = NULL;
	while (base)
	{
		if (istrue(flag, file, base->str, path))
		{
			nl = listadd(NULL, file, NULL, NULL);
			nl->next = base;
			if (i == 0)
				return (nl);
			if (tmp)
			{
				tmp->next = nl;
				return ((*list));
			}
		}
		i++;
		tmp = base;
		base = base->next;
	}
	return ((*list));
}

t_l		*listadd(t_l *list, char *arg, char *path, char *flag)
{
	if (path)
		ft_putstr(path);
	ft_putstr("------LISTADD\n");
	if (!(list))
	{
		if (!(list = (t_l *)malloc(sizeof(t_l))))
			return (0);
		list->str = ft_strdup(arg);
		list->next = NULL;
		return (list);
	}
	if (!flag || (flag && !isflag(flag, 't') && !isflag(flag, 'r')))
		list = no_sort(&list, arg);
	else
		list = list_tr(&list, arg, path, flag);
	(void)path;
	(void)flag;
	return (list);
}
