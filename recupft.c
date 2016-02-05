/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recupft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 19:29:53 by cmichaud          #+#    #+#             */
/*   Updated: 2016/02/05 22:33:43 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_l			*recupft(t_work file, DIR *rep, t_dirent *ent, char *rstr)
{
	char *str;
	char *tmp;

	file.rtab = NULL;
    while ((ent = readdir(rep)))
    {
        if ((isflag(file.flag, 'a') || ent->d_name[0] != '.')
            && ft_strcmp(ent->d_name, ".") && ft_strcmp(ent->d_name, ".."))
		{
			str = ft_strjoin(rstr, "/");
			tmp = ft_strjoin(str, ent->d_name);
			if (isopen(tmp))
				file.rtab = listadd(file.rtab, tmp);
			free(str);
			free(tmp);
			str = NULL;
			tmp = NULL;
        }
		if (isflag(file.flag, 'a') || ent->d_name[0] != '.')
            file.ftab = listadd(file.ftab, ent->d_name);
    }
    if (file.ftab)
	{
		file.ftab = sort(file.ftab, file.flag);
		file.ftab = afffile(file.ftab, file.flag);
	}
		if (file.rtab)
        file.rtab = sort(file.rtab, file.flag);
    return (file.rtab);
}
