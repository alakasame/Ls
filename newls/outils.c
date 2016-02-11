/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 08:35:11 by cmichaud          #+#    #+#             */
/*   Updated: 2016/02/11 15:10:03 by cmichaud         ###   ########.fr       */
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
	DIR		*rep;
	t_stat	fs;
	int		i;
	char	*link;

	if ((rep = opendir(str)))
	{
		if (lstat(str, &fs) < 0)
			return (0);
		if (S_ISLNK(fs.st_mode))
		{
			if (!(link = (char *)malloc(sizeof(char) * 256)))
				return (0);
			if ((i = readlink(str, link, sizeof(link)-1)) != -1)
			{
				link[i] = '\0';
				if (!(ft_strcmp(link, "private")))
				{
					free(link);
					return (2);
				}
			}
			free(link);
		}
		if (closedir(rep) == -1)
			return (erroret(str));
		return (1);
	}
	if (S_ISDIR(fs.st_mode))
		return (1);
	return (2);
}

t_l			*gofreenext(t_l *list)
{
	t_l	*tmp;

	tmp = list->next;
	free(list->str);
	free(list);
	return (tmp);
}

char		*getpath(char *path, char *str)
{
	char	*way;
	char	*tmp;
	int		i;

	i = ft_strlen(path);
	if (str[0] == '/')
		return (ft_strdup(str));
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
