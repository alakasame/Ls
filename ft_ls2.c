/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 10:59:43 by cmichaud          #+#    #+#             */
/*   Updated: 2016/01/29 14:39:56 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		without(char *flag)
{
	DIR			*rep;
	t_dirent	*ent;

	if ((rep = opendir("./")) == NULL)
		erroret("");
	while ((ent = readdir(rep)))
	{
		if (ent->d_name[0] != '.' || isflag(flag, 'a'))
		{
			flag = NULL;
		}
	}
	if (closedir(rep) == -1)
		erroret("");
	return (0);
}

int		ft_ls2(int argc, char **argv, char *flag)
{
	int		f;
	int		i;
	char	**tab;
	int		c;

	c = 0;
	f = 0;
	i = 0;
	if (!(tab = (char **)malloc(sizeof(char *) * argc)))
		return (0);
	while (argv[++i])
		if (i != argc)
		{
			if (argv[i][0] == '-' && c == 0)
				f++;
			else
			{
				tab[c] = ft_strdup(argv[i]);
				c++;
			}
		}
	if (f + 1 == argc)
		return (without(flag));
	tab[c] = 0;
	return (0);
}
