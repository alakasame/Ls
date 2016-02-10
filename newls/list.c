/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 01:27:40 by cmichaud          #+#    #+#             */
/*   Updated: 2016/02/10 08:21:56 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_l		*listadd(char *str)
{
	t_l *list;

	if (!(list = (t_l *)malloc(sizeof(t_l))))
		return (0);
	list->next = NULL;
	list->back = NULL;
	list->str = ft_strdup(str);
	return (list);
}

t_l		*freeret(char **lpath, char **npath, t_l *list)
{
	ft_memdel((void **)lpath);
	ft_memdel((void **)npath);
	return (list);
}

t_l		*cond1(t_arg *stmp, t_l **file)
{
	if (stmp->file->back == NULL)
	{
		ft_putstr("COND 1\n");
		stmp->path->next = stmp->file;
		stmp->file->back = stmp->path;
		file = &stmp->path;
	}
	else
	{
		ft_putstr("COND 2\n");
		stmp->file->back->next = stmp->path;
		stmp->path->back = stmp->file->back;
		stmp->file->back = stmp->path;
		stmp->path->next = stmp->file;
	}
	return (freeret(&stmp->lpath, &stmp->npath, (*file)));
}

t_l		*listtr(t_l **file, char *str, char *path)
{
	t_arg	stmp;

	stmp.file = (*file);
	stmp.path = listadd(str);
	ft_putstr(path);
	stmp.npath = getpath(path, str);
	while (stmp.file != NULL)
	{
		stmp.lpath = getpath(path, stmp.file->str);
		ft_putstr("\n WHILE \n");
		ft_putstr("LIST PATH :  ");
		ft_putstr(stmp.lpath);
		ft_putstr("\n");
		ft_putstr("NEW PATH :  ");
		ft_putstr(stmp.npath);
		ft_putstr("\n");
		if (stat(stmp.npath, &stmp.fs) < 0 || stat(stmp.lpath, &stmp.sf) < 0)
			return (0);
		if (stmp.fs.st_mtime < stmp.sf.st_mtime)
			return (cond1(&stmp, file));
		if (stmp.file->next == NULL)
		{
			ft_putstr("COND 3\n");
			stmp.file->next = stmp.path;
			stmp.path->back = stmp.file;
			return (freeret(&stmp.lpath, &stmp.npath, *(file)));
		}
		ft_memdel((void **)&stmp.lpath);
		stmp.file = stmp.file->next;
	}
	ft_putstr("\n WHILE \n");
	return ((*file));
}


t_l	*initlist(t_l **file, char *str, char *flag, char *path)
{
	if (!*file)
		return (listadd(str));
	if (isflag(flag, "tr"))
	{
		ft_putstr("\n LIST TR \n");
		return (listtr(file, str, path));
	}
	if (isflag(flag, "t"))
	{
		ft_putstr("\n LIST T \n");
		return (listt(file, str, path));
	}
	if (isflag(flag, "r"))
	{
		ft_putstr("\n LIST R \n");
		return (listr(file, str));
	}
//	ft_putstr("\n LIST Alpha \n");	
	return (alphalistsort(file, str));
}
