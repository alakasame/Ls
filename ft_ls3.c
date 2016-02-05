/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/29 14:08:41 by cmichaud          #+#    #+#             */
/*   Updated: 2016/01/29 16:41:47 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_ls31(char **tab, DIR *rep, t_dirent *ent)
{
	int		i;
	DIR		*ptr;
	t_stat	*fs;

	i = -1;
	fs = NULL;
	ptr = rep;
	while ((ent = readdir(rep)))
		if (isflag(flag, 'a') == 1 || ent->d_name[0] != '-')
			tab[++i] = ft_strdup(ent->d_name);
	tab[++i] = 0;
	if (isflag(flag, 't') == 1)
		tab = sort_t(tab, ptr, fs, 0);
	if (isflag(flag, 'r') == 1)
		tab = sort_r(tab);
	return (0);
}

int		ft_ls3(char const *str, char *flag)
{
	DIR			*rep;
	DIR			*ptr;
	t_dirent	*ent;
	int			i;

	ft_putstr("\nBegin LS3\n");
	i = 0;
	if ((rep = opendir(str)) == NULL)
		return (erroret(""));
	ptr = rep;
	while ((ent = readdir(rep)))
		i++;
	if (!(tab = (char **)malloc(sizeof(char *) * i + 1)))
		return (erroret(""));
	return (ft_ls31(tab, ptr, ent));
}
