/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 08:28:12 by cmichaud          #+#    #+#             */
/*   Updated: 2016/02/09 05:53:03 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			nextmain(t_l *path, char *flag)
{
	DIR			*rep;
	t_dirent	*ent;
	t_arg		file;
	t_l			*tmp;

	file.file = NULL;
	file.path = NULL;
	file.flag = flag;
	ent = NULL;
	rep = NULL;
	while (path) // boucle tourne trouve et affiche fichier eatch rep. 
	{
		ft_putstr(path->str); // !! si no error, no arg, pas afficher au premier tour
		ft_putstr(":\n"); //
		if ((rep = opendir(path->str)))
		{
			file.path = recupft(file, rep, ent, path->str); // on recup les dossiers et fichiers;
			if (closedir(rep) == -1)
				return (erroret(""));
		}
		else
			erroret(path->str);
		ft_putstr("lol");
		ft_putstr("\n");
		free(path->str);
		tmp = path->next;
		free(path);
		path = tmp;
		if (isflag(flag, 'R') && file.path)
			nextmain(file.path, file.flag);
	}
	path = NULL;
	return (0);
}

int			main(int argc, char **argv)
{
	t_arg	sarg;
	t_l		*error;
	int		i;

	sarg.flag = NULL;
	sarg.path = NULL;
	sarg.file = NULL;
	error = NULL;
	i = searchflag(argv, &sarg.flag, argc);
	if (i + 1 == argc)
	{
		sarg.path = listadd(sarg.path, ".", NULL, sarg.flag);
		ft_putstr(sarg.path->str);
	}
	while (argc > ++i) // i = nb argvflag - 1 et flag is ok;
	{
		if (isopen(argv[i]))
			sarg.path = listadd(sarg.path, argv[i], ".", sarg.flag); // LIST ADD ok;
		else if (isfile(argv[i]))
			sarg.file = listadd(sarg.file, argv[i], ".", sarg.flag);
		else
			error = listadd(error, argv[i], NULL, NULL); // !!!!!! ON DOIT RECUP LS FILE
	}
	error = freeafflist(error);
	if (sarg.file)
		sarg.file = afffile(sarg.file, sarg.flag, ".");
	nextmain(sarg.path, sarg.flag);
	free(sarg.flag);
	return (0);
}
