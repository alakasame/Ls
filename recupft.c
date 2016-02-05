/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recupft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 19:29:53 by cmichaud          #+#    #+#             */
/*   Updated: 2016/02/05 20:12:23 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_work      recupft(t_work file, DIR *rep, t_dirent *ent, char *rstr)
{
	char *str;
	char *tmp;

    while ((ent = readdir(rep)))
    {
        if ((isflag(file.flag, 'a') || ent->d_name[0] != '.')
            && isopen(ent->d_name) && ft_strcmp(ent->d_name, ".")
            && ft_strcmp(ent->d_name, ".."))
		{
//			str = ft_strjoin(rstr, "/");
//			tmp = ft_strjoin(str, ent->d_name);
            file.rtab = listadd(file.rtab, ent->d_name);//tmp);
//			free(str);
//			free(tmp);
			str = rstr;//NULL;
			tmp = NULL;
        }
		if (isflag(file.flag, 'a') || ent->d_name[0] != '.')
            file.ftab = listadd(file.ftab, ent->d_name);
    }
    if (file.ftab)
        sort(file.ftab, file.flag);
    if (file.rtab)
        sort(file.rtab, file.flag);
    return (file);
}
