/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 02:06:00 by cmichaud          #+#    #+#             */
/*   Updated: 2016/02/08 03:41:21 by cmichaud         ###   ########.fr       */
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

t_l		**insertlist(t_l **list, char *str)
{
	t_l		*nlist;

	if (!(nlist = (t_l *)malloc(sizeof(t_l))))
		return (0);
	nlist->str = ft_strdup(str);
	if ((*list)->back == NULL)
	{
		(*list)->back = nlist;
		nlist->next = (*list);
		nlist->back = NULL;
	}
	else
	{
		ft_putstr("\nSTR  : ");
		ft_putstr(str);
		nlist->back = (*list)->back;
		nlist->next = (*list);
		(*list)->back = nlist;
		ft_putstr(" NLIST ");
		ft_putstr(nlist->back->str);
		ft_putstr(" --- ");
		ft_putstr(nlist->str);
		ft_putstr(" --- ");
		if (nlist->next)
			ft_putstr(nlist->next->str);
		ft_putstr(" LIST ");
		ft_putstr((*list)->back->str);
		ft_putstr(" --- ");
		ft_putstr((*list)->str);
		ft_putstr(" --- ");
		if ((*list)->next)
			ft_putstr((*list)->next->str);
		ft_putstr("\n");		
	}
	while ((*list)->next != NULL)
		(*list) = (*list)->next;
	return (list);
}

t_l		*no_sort(t_l *list, char *str)
{
	t_l		*tmp;

	while (list->next != NULL)
		list = list->next;
	tmp = list;
	if (!(list->next = (t_l *)malloc(sizeof(t_l))))
		return (0);
	list = list->next;
	list->back = tmp;
	list->next = NULL;
	list->str = ft_strdup(str);
	return (list);
}

t_l		*list_tr(t_l *list, char *file, char *path, char *flag)
{
	char	*npath;
	char	*lpath;
	t_stat	fs;
	t_stat	sf;

	npath = getpath(path, file);
	while (list != NULL)
	{
		lpath = getpath(path, list->str);
		if (stat(npath, &fs) < 0 || stat(lpath, &sf) < 0)
			erroret("");
		if ((fs.st_mtime < sf.st_mtime && isflag(flag, 'r') && isflag(flag, 't'))
			|| (fs.st_mtime > sf.st_mtime && !isflag(flag, 'r') && isflag(flag, 't'))
			|| (isflag(flag, 'r') && !isflag(flag, 't') && ft_strcmp(file, list->str) > 0)
			|| (!isflag(flag, 'r') && !isflag(flag, 't') && ft_strcmp(file, list->str) < 0))
			insertlist(&list, file);
		else if (list->next == NULL)
			list = no_sort(list, file);
		ft_memdel((void **)&lpath);
		list = list->next;
	}
	ft_memdel((void **)&npath);
	return (list);
}

t_l		*listadd(t_l *list, char *arg, char *path, char *flag)
{
	t_l	*tmp;

	tmp = list;
	if (!(list))
	{
		if (!(list = (t_l *)malloc(sizeof(t_l))))
			return (0);
		list->str = ft_strdup(arg);
		list->next = NULL;
		list->back = NULL;
		return (list);
	}
	ft_putstr(arg);
	ft_putstr("\nqq");
	ft_putstr("\n");
	while (list)
	{
		ft_putstr(list->str);
		ft_putstr("aa\n");
		list = list->next;
	}
	list = tmp;
	if (!path)
		list = list_tr(list, arg, ".", flag);
	else
		list = list_tr(list, arg, path, flag);
	while (tmp->back != NULL)
		tmp = tmp->back;
	list = tmp;
	return (list);
}
