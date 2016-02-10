/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 03:32:05 by cmichaud          #+#    #+#             */
/*   Updated: 2016/02/09 11:32:28 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
//		|| (fs.st_mtime > sf.st_mtime && !isflag(flag, 'r') && isflag(flag, 't'))
//	|| (isflag(flag, 'r') && !isflag(flag, 't') && ft_strcmp(file, sl) > 0) 
//	|| (!isflag(flag, 'r') && !isflag(flag, 't') && ft_strcmp(file, sl) < 0))

int istrue(char *flag, char *file, char *sl, char *path)
{
	char *npath;
	char *lpath;
	t_stat	fs;
	t_stat sf;
	int		i;
	int		c;

	c = 0;
	i = 0;
	if (path)
	{
		npath = getpath(path, file);
		lpath = getpath(path, sl);
		c = -1;
	}
	else
	{
		npath = file;
		lpath = sl;
	}
	if (fs.st_mtime < sf.st_mtime && isflag(flag, 'r') && isflag(flag, 't'))
		i = 1;
	if (c == -1)
	{
		ft_memdel((void **)&npath);
		ft_memdel((void **)&lpath);
	}
	return (i);
}

t_l		*sor(t_l *list)
{
	t_l		*base;
	t_l		*tmp;
	char	*mtp;

	if (!(list))
		return (0);
	base = list;
	tmp = list;
	list = list->next;
	while (list)
	{
		if (ft_strcmp(list->str, tmp->str) < 0)
		{
			mtp = tmp->str;
			tmp->str = list->str;
			list->str = mtp;
			list = base;
		}
		tmp = list;
		list = list->next;
	}
	return (base);
}

void	sortswap(t_l *tmp, t_l *list)
{
	char *mtp;

	mtp = tmp->str;
	tmp->str = list->str;
	list->str = mtp;
}

t_l		*sort_t(t_l *list, char *flag, t_l *base, char *path)
{
	t_stat	fs;
	t_stat	sf;
	t_l		*tmp;
	char	*npath;
	char	*xpath;

	tmp = list;
	list = list->next;
	while (list)
	{
		xpath = getpath(path, tmp->str);
		npath = getpath(path, list->str);
		ft_putstr("/nPATH ______________");
		ft_putstr(npath);
		if (stat(npath, &fs) < 0 || stat(xpath, &sf) < 0)
			return (0);
		ft_memdel((void *)&npath);
		ft_memdel((void *)&xpath);
		if (isflag(flag, 'r') && fs.st_mtime < sf.st_mtime)
		{
			sortswap(tmp, list);
			list = base;
		}
		else if (!(isflag(flag, 'r')) && fs.st_mtime > sf.st_mtime)
		{
			sortswap(tmp, list);
			list = base;
		}
		tmp = list;
		list = list->next;
	}
	return (base);
}

t_l		*sort_r(t_l *list, t_l *base)
{
	t_l		*tmp;
	char	*mtp;

	tmp = list;
	list = list->next;
	while (list)
	{
		ft_putstr(list->str);
		if (ft_strcmp(list->str, tmp->str) > 0)
		{
			mtp = tmp->str;
			tmp->str = list->str;
			list->str = mtp;
			return (sort_r(base, base));
		}
		tmp = list;
		list = list->next;
	}
	return (base);	
}

t_l		*sort(t_l *list, char *flag, char *path)
{
	t_l	*base;

	base = list;
	sor(list);
	if (isflag(flag, 't'))
		list = sort_t(list, flag, base, path);
	else if (isflag(flag, 'r'))
		list = sort_r(list, base);
	return (list);
}
