/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 09:23:53 by cmichaud          #+#    #+#             */
/*   Updated: 2016/02/03 01:32:09 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*conflag(char *str, char *flag)
{
	int i;
	int c;
	int d;

	d = 0;
	c = 0;
	i = 0;
	while (str[++i])
	{
		if (str[i] == 'a' || str[i] == 'l' || str[i] == 't'
			|| str[i] == 'r' || str[i] == 'R')
		{
			while (flag[c])
			{
				if (flag[c] == str[i])
					d = 1;
				c++;
			}
			c = 0;
			if (d == 0)
				ft_strncat(flag, &str[i], 1);
			d = 0;
		}
	}
	return (flag);
}

int		searchflag(char **argv, char **flag, int argc)
{
	int		i;
	int		c;
	int		d;

	d = 0;
	c = 0;
	i = 0;
	if (!(*flag = (char *)malloc(sizeof(char) * 6)))
		return (0);
	ft_bzero(*flag, 6);
	while (++i < argc)
	{
		if (argv[i][0] == '-' && c == 0)
		{
			*flag = conflag(argv[i], *flag);
			d++;
		}
		else
			c = 1;
	}
	return (d);
}

int		isflag(char *str, char a)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] == a)
			return (1);
	return (0);
}
