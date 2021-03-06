/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 08:30:00 by cmichaud          #+#    #+#             */
/*   Updated: 2016/01/21 12:23:19 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_ls1(char const *str)
{
	DIR			*rep;
	t_dirent	*ent;
	int			c;

	c = 0;
	if ((rep = opendir(str)) == NULL)
		erroret("");
	while ((ent = readdir(rep)))
	{
		if (ent->d_name[0] != '.')
		{
			ft_putstr(ent->d_name);
			if ((c - 1) % 5 == 0)
				ft_putstr("\n");
			else
				ft_putstr("\t");
		}
		c++;
	}
	if (closedir(rep) == -1)
		erroret("");
	return (0);
}
