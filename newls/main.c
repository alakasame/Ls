/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 01:15:01 by cmichaud          #+#    #+#             */
/*   Updated: 2016/02/11 14:17:53 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		mainrecur(char *path, char *flag)
{
	t_arg env;

	env.file = NULL;
	env.path = NULL;
	if ((env.rep = opendir(path)) == NULL)
		return (0);
	while ((env.ent = readdir(env.rep)))
	{
		env.npath = getpath(path, env.ent->d_name);
/*		ft_putstr(path);
		ft_putstr("\nPATH\n");
		ft_putstr(env.npath);
		ft_putstr("\nNPATH\n");
		ft_putstr(env.ent->d_name);
		ft_putstr("\nFILE\n");*/
		if (isdirorfile(env.npath) == 1 && isflag(flag, "R")
			&& ft_strcmp(env.ent->d_name, "..") != 0 &&
			ft_strcmp(env.ent->d_name, ".") != 0 && (env.ent->d_name[0] != '.'
			|| isflag(flag, "a")))
			env.path = initlist(&env.path, env.npath, flag, ".");
		if (env.ent->d_name[0] != '.' || isflag(flag, "a"))
			env.file = initlist(&env.file, env.ent->d_name, flag, path);
		ft_memdel((void **)&env.npath);
	}
	if (closedir(env.rep) == -1)
		return (erroret(""));
	env.file = freeafflist(&env.file, path, flag, 1);
/*	while (env.path)
	{
		ft_putstr("\n");
		ft_putstr(env.path->str);
		ft_putstr(":\n");		
		env.path = gofreenext(env.path);
		}*/
	while (env.path)
	{
		ft_putstr("\n");
		ft_putstr(env.path->str);
		ft_putstr(":\n");		
		mainrecur(env.path->str, flag);
		env.path = gofreenext(env.path);
	}
	return (0);
}

int		nextmain(t_arg *file, t_l **error)
{
	if (*error)
		*error = errorlist(error);
	if (file->file)
	{
		file->file = freeafflist(&file->file, ".", file->flag, 0);
		ft_putstr("\n");
	}
	while (file->path)
	{
		if (file->y != 1)
		{
			ft_putstr(file->path->str);
			ft_putstr(":\n");
		}
		file->y = 0;
		mainrecur(file->path->str, file->flag);
		file->path = gofreenext(file->path);
		if (file->path)
			ft_putstr("\n");
	}
	free(file->flag);
	return (0);
}

int		main(int argc, char **argv)
{
	int		i;
	t_arg	file;
	t_l		*error;

	file.flag = NULL;
	file.file = NULL;
	file.path = NULL;
	file.y = 0;
	file.o = 0;
	error = NULL;
	i = searchflag(argv, &file.flag, argc);
	if (i + 1 == argc)
	{
		file.y = 1;
		file.path = listadd(".");
	}
	while (++i < argc)
	{
		if (isdirorfile(argv[i]) == 1)
			file.path = initlist(&file.path, argv[i], file.flag, ".");
		else if (isdirorfile(argv[i]) == 2)
			file.file = initlist(&file.file, argv[i], file.flag, ".");
		else
		{
			file.o = 1;
			error = initlist(&error, argv[i], "o", NULL);
		}
	}
	nextmain(&file, &error);
	return (file.o);
}
/*
	while (file.file)
	{
		ft_putstr("\nTEST AFF FILE MAIN\n");
		ft_putstr(file.file->str);
		file.file = file.file->next;
	}
	return (0);
}
*/
