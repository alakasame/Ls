/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recupft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 19:29:53 by cmichaud          #+#    #+#             */
/*   Updated: 2016/02/08 02:01:11 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_l			*recupft(t_work file, DIR *rep, t_dirent *ent, char *path) // CREE DES FONCTION DAJOUT DIRECTEMENT PAS PLACER, ABORT TIME A CAUSE DES BOUCLE DANS listadd, sort, sor
{
	char *tmp;

	file.rtab = NULL;
    while ((ent = readdir(rep)))
    {
		if ((isflag(file.flag, 'a') || ent->d_name[0] != '.')
            && ft_strcmp(ent->d_name, ".") && ft_strcmp(ent->d_name, ".."))
		{
			tmp = getpath(path, ent->d_name);
			if (isopen(tmp))
				file.rtab = listadd(file.rtab, tmp, path, file.flag);
			ft_memdel((void **)&tmp);
        }
		if (isflag(file.flag, 'a') || ent->d_name[0] != '.')
            file.ftab = listadd(file.ftab, ent->d_name, path, file.flag);
    }
    if (file.ftab)
		file.ftab = afffile(file.ftab, file.flag, path);
    return (file.rtab);
}
