/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 03:32:05 by cmichaud          #+#    #+#             */
/*   Updated: 2016/02/08 01:41:19 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

t_l		*sort_t(t_l *list, char *flag, t_l *base)
{
	t_stat	fs;
	t_stat	sf;
	t_l		*tmp;

	tmp = list;
	list = list->next;
	while (list)
	{
		if (stat(list->str, &fs) < 0 || stat(tmp->str, &sf) < 0)
			return (0);
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

t_l		*sort(t_l *list, char *flag)
{
	t_l	*base;

	base = list;
	sor(list);
	if (isflag(flag, 't'))
		list = sort_t(list, flag, base);
	else if (isflag(flag, 'r'))
		list = sort_r(list, base);
	return (list);
}
