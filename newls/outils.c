/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 08:35:11 by cmichaud          #+#    #+#             */
/*   Updated: 2016/02/10 02:58:02 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			erroret(char *str)
{
	if (str != NULL)
		ft_putstr("ls: ");
	perror(str);
	return (0);
}

int			isdirorfile(char *str)
{
	DIR *rep;
	t_stat fs;

	if (lstat(str, &fs) < 0)
		return (0);
	if ((rep = opendir(str)))
	{
		if (closedir(rep) == -1)
			return (erroret(str));
		return (1);
	}
	return (2);
}

char		*getpath(char *path, char *str)
{
	char	*way;
	char	*tmp;
	int		i;

	i = ft_strlen(path);
	if (path[i - 1] != '/')
	{
		way = ft_strjoin(path, "/");
		tmp = ft_strjoin(way, str);
		free(way);
		return (tmp);
	}
	tmp = ft_strjoin(path, str);
	return (tmp);
}

int			ft_lenbr(int n)
{
	int i;

	i = 1;
	while (n >= 10)
	{
		i++;
		n /= 10;
	}
	return (i);
}