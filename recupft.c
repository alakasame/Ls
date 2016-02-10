/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recupft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 19:29:53 by cmichaud          #+#    #+#             */
/*   Updated: 2016/02/09 11:26:48 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_l			*recupft(t_arg file, DIR *rep, t_dirent *ent, char *path) // CREE DES FONCTION DAJOUT DIRECTEMENT PAS PLACER, ABORT TIME A CAUSE DES BOUCLE DANS listadd, sort, sor
{
	char *tmp;

	file.path = NULL;
    while ((ent = readdir(rep)))
    {
		/*ft_putstr(path);
		ft_putstr("----");
		ft_putstr(ent->d_name);
		ft_putstr("---- RECUPFT\n");*/
		tmp = getpath(path, ent->d_name);
		if ((isflag(file.flag, 'a') || ent->d_name[0] != '.')
            && ft_strcmp(ent->d_name, ".") && ft_strcmp(ent->d_name, ".."))
		{
			if (isopen(tmp) && isflag(file.flag, 'R'))
			{
				ft_putstr("GETPATH---------");
				ft_putstr(tmp);
				ft_putstr("  <--NEWPATH -- ");
				ft_putstr(path);
				ft_putstr("  <--OLDPATH -- ");
				ft_putstr(tmp);
				ft_putstr(" <--FILE --\n");
				file.path = listadd(file.path, tmp, NULL, file.flag);
			}
        }
		if (isflag(file.flag, 'a') || ent->d_name[0] != '.')
		{
			/*ft_putstr("GETFILE---------");
			ft_putstr(tmp);
			ft_putstr("  <--NEWPATH -- ");
			ft_putstr(path);
			ft_putstr("  <--OLDPATH -- ");
			ft_putstr(ent->d_name);
			ft_putstr(" <--FILE --\n");*/
            file.file = listadd(file.file, ent->d_name, tmp, file.flag);
		}
		ft_memdel((void **)&tmp);
    }
	/*
	if (file.rtab)
	sort(file.rtab, file.flag, path);*/
    if (file.file)
	{
//		sort(file.ftab, file.flag, path);
		file.file = afffile(file.file, file.flag, path);
	}
    return (file.path);
}
