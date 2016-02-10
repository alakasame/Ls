/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listnext.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 04:33:29 by cmichaud          #+#    #+#             */
/*   Updated: 2016/02/10 06:50:25 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_l		*listt(t_l **file, char *str, char *path)
{
	t_arg   stmp;
	
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
		if (stmp.fs.st_mtime > stmp.sf.st_mtime)
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

t_l     *condr(t_arg *stmp, t_l **file)
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
    return ((*file));
}

t_l		*listr(t_l **file, char *str)
{
	t_arg   stmp;
	
	stmp.file = (*file);
	stmp.path = listadd(str);
	while (stmp.file != NULL)
	{
		ft_putstr("\n WHILE \n");
		if (ft_strcmp(stmp.file->str, str) < 0)
			return (condr(&stmp, file));
		if (stmp.file->next == NULL)
		{
			ft_putstr("COND 3\n");
			stmp.file->next = stmp.path;
			stmp.path->back = stmp.file;
			return ((*file));
		}
		stmp.file = stmp.file->next;
	}
	return ((*file));
}

t_l		*alphalistsort(t_l **file, char *str)
{
	t_arg   stmp;
	
	stmp.file = (*file);
	stmp.path = listadd(str);
	while (stmp.file != NULL)
	{
//		ft_putstr("\n WHILE \n");
		if (ft_strcmp(stmp.file->str, str) > 0)
			return (condr(&stmp, file));
		if (stmp.file->next == NULL)
		{
			//		ft_putstr("COND 3\n");
			stmp.file->next = stmp.path;
			stmp.path->back = stmp.file;
			return ((*file));
		}
		stmp.file = stmp.file->next;
	}
	return ((*file));
}
