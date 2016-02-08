/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 02:06:00 by cmichaud          #+#    #+#             */
/*   Updated: 2016/02/08 06:46:55 by cmichaud         ###   ########.fr       */
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

t_l		*insertlist(t_l *list, t_l *base, char *str)
{
	char	*tmp;
	char	*buf;

	(void)base;
	tmp = list->str;
	list->str = ft_strdup(str);
	while (list->next != NULL)
	{
		list = list->next;
		buf = list->str;
		list->str = tmp;
		tmp = buf;
	}
	if (!(list->next = (t_l *)malloc(sizeof(t_l))))
		return (0);
	list = list->next;
	list->next = NULL;
	list->str = tmp;
	while (list->next != NULL)
		list = list->next;
	return (list);
}

t_l		*no_sort(t_l *list, char *str, t_l *base)
{
	t_l		*tmp;

	(void)base;
	while (list->next != NULL)
		list = list->next;
	tmp = list;
	if (!(list->next = (t_l *)malloc(sizeof(t_l))))
		return (0);
	list = list->next;
	list->next = NULL;
	list->str = ft_strdup(str);
	while (list->next != NULL)
		list = list->next;
	return (list);
}

t_l		*list_tr(t_l *list, char *file, char *path, char *flag)
{
	char	*npath;
	char	*lpath;
	t_stat	fs;
	t_stat	sf;
	t_l		*base;

	npath = getpath(path, file);
	base = list;
	while (list != NULL)
	{
		lpath = getpath(path, list->str);
		if (stat(npath, &fs) < 0 || stat(lpath, &sf) > 0)
		{
			while (1 + 1 == 1)
				ft_putstr("tamere");
		}
		ft_memdel((void **)&lpath);
		if ((fs.st_mtime < sf.st_mtime && isflag(flag, 'r') && isflag(flag, 't'))
			|| (fs.st_mtime > sf.st_mtime && !isflag(flag, 'r') && isflag(flag, 't'))
			|| (isflag(flag, 'r') && !isflag(flag, 't') && ft_strcmp(file, list->str) > 0)
			|| (!isflag(flag, 'r') && !isflag(flag, 't') && ft_strcmp(file, list->str) < 0))
			list = insertlist(list, base, file);
		else if (list->next == NULL)
			list = no_sort(list, file, base);
		list = list->next;
	}
	ft_memdel((void **)&npath);
	return (base);
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
		return (list);
	}
	if (!path)
		list = list_tr(list, arg, ".", flag);
	else
		list = list_tr(list, arg, path, flag);
	list = tmp;
	return (list);
}
