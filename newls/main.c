/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 01:15:01 by cmichaud          #+#    #+#             */
/*   Updated: 2016/02/10 09:42:40 by cmichaud         ###   ########.fr       */
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
/*		ft_putstr("WHILE - RECUR - RECUP FILE du PATH : ");
		ft_putstr(env.ent->d_name);
		ft_putstr("\n");
		ft_putstr("RECUP PATH du NEW FILE: ");
		ft_putstr(env.npath);
	ft_putstr("\n");
*/		env.npath = getpath(path, env.ent->d_name);
		if (isdirorfile(env.npath) == 1 && isflag(flag, "R")
			&& ft_strcmp(env.ent->d_name, "..") != 0 &&
			ft_strcmp(env.ent->d_name, ".") != 0 && (env.ent->d_name[0] != '.'
			|| isflag(flag, "a")))
		{
			ft_putstr(env.npath);
			ft_putstr("<==== is PATH\n");
			env.path = initlist(&env.path, env.npath, flag, ".");
		}
		if (env.ent->d_name[0] != '.' || isflag(flag, "a"))
		{
			//ft_putstr(env.ent->d_name);
			//ft_putstr("<=== is FILE\n");
			env.file = initlist(&env.file, env.ent->d_name, flag, path);
		}
		ft_memdel((void **)&env.npath);
	}
	if (closedir(env.rep) == -1)
		return (erroret(""));
	env.file = freeafflist(&env.file, path, flag);
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
		file->y = 1;
		file->file = freeafflist(&file->file, "", file->flag);
	}
	ft_putstr("\n");
	while (file->path)
	{
		if (file->y > 0)
		{
			ft_putstr(file->path->str);
			ft_putstr(":\n");
		}
		mainrecur(file->path->str, file->flag);
		file->y = 1;
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
	file.y = -1;
	error = NULL;
	i = searchflag(argv, &file.flag, argc);
	if (i + 1 == argc)
	{
		ft_putstr("buf");
		file.path = listadd(".");
	}
	while (++i < argc)
	{
		ft_putstr("WHILE - MAIN - RECUP ARG : ");
		ft_putstr(argv[i]);
		ft_putstr("\n");
		if (isdirorfile(argv[i]) == 1)
		{
			file.y++;
			ft_putstr(argv[i]);
			ft_putstr("<==== is PATH\n");
			file.path = initlist(&file.path, argv[i], file.flag, ".");
		}
		else if (isdirorfile(argv[i]) == 2)
		{
			ft_putstr("<=== is FILE\n");
			file.file = initlist(&file.file, argv[i], file.flag, ".");
		}
		else
		{
			ft_putstr("<==== is ERROR\n");
			error = initlist(&error, argv[i], "o", NULL);
		}
	}
	return (nextmain(&file, &error));
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
