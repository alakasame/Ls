/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 08:28:12 by cmichaud          #+#    #+#             */
/*   Updated: 2016/02/05 20:06:21 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			nextmain(t_l *rtab, char *flag)
{
	DIR			*rep;
	t_dirent	*ent;
	t_work		file;
	t_l			*tmp;

	file.ftab = NULL;
	file.rtab = NULL;
	file.flag = flag;
	ent = NULL;
	rep = NULL;
	while (rtab) // boucle tourne trouve et affiche fichier eatch rep. 
	{
		ft_putstr(rtab->str); // !! si no error, no arg, pas afficher au premier tour
		ft_putstr(":\n"); //
		if ((rep = opendir(rtab->str)))
			file = recupft(file, rep, ent, rtab->str); // on recup les dossiers et fichiers;
		else
			erroret(rtab->str);
		if (closedir(rep) == -1)
			return (erroret(""));
		file.ftab = afffile(file.ftab, file.flag); // free and aff ftab;
		ft_putstr("\n");
		tmp = file.rtab;
		while (file.rtab)
		{
			ft_putstr(file.rtab->str);
			file.rtab = file.rtab->next;
		}
		file.rtab = tmp;
		free(rtab->str);
		tmp = rtab->next;
		free(rtab);
		rtab = tmp;
		if (isflag(flag, 'R') && file.rtab)
			return (nextmain(file.rtab, file.flag));
	}
	rtab = NULL;
	free(flag);
	return (0);
}

int			main(int argc, char **argv)
{
	t_arg	sarg;
	int		i;

	sarg.flag = NULL;
	sarg.trep = NULL;
	sarg.terror = NULL;
	i = searchflag(argv, &sarg.flag, argc);
	if (i + 1 == argc)
		sarg.trep = listadd(sarg.trep, ".");
	while (argc > ++i) // i = nb argvflag - 1 et flag is ok;
	{
		if (isopen(argv[i]))
			sarg.trep = listadd(sarg.trep, argv[i]); // LIST ADD ok;
		else
			sarg.terror = listadd(sarg.terror, argv[i]);
	}
	sort(sarg.trep, sarg.flag); //sort is ok
	sor(sarg.terror); //sor is ok;
	sarg.terror = freeafflist(sarg.terror);
	return (nextmain(sarg.trep, sarg.flag));
}
