/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flagl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 03:44:46 by cmichaud          #+#    #+#             */
/*   Updated: 2016/02/06 01:08:40 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			ft_lenbr(int n)
{
	int i;

	i = 1;
	while (n > 10)
	{
		i++;
		n /= 10;
	}
	return (i);
}

t_aff		recupflagl(char *str, t_aff saff)
{
	t_stat		fs;
	t_passwd	*user;
	t_group		*group;

	ft_putstr(str);
	ft_putstr("\n");
	if (stat(str, &fs) < 0)
	{
		ft_putstr("FS");
		return (saff);
	}
	if (!(user = getpwuid(fs.st_uid))
		|| !(group = getgrgid(fs.st_gid)))
		return (saff);
	ft_putnbr(ft_lenbr((saff.link = fs.st_nlink)));
	ft_putstr("\n");
	ft_putnbr((saff.usr = ft_strlen(user->pw_name)));
	ft_putstr("\n");
	ft_putnbr((saff.grp = ft_strlen(group->gr_name)));
	ft_putstr("\n");
	ft_putnbr(ft_lenbr((saff.byte = fs.st_size)));
	ft_putstr("\n");
	return (saff);
}

t_aff		inits(t_aff saff)
{
	saff.link = 0;
	saff.usr = 0;
	saff.grp = 0;
	saff.byte = 0;
	saff.day = 0;
	saff.minor = 0;
	saff.major = 0;
	return (saff);
}

t_l			*flagl(t_l *ftab)
{
	t_aff		saff;
	t_l			*tmp;

	saff = inits(saff);
	tmp = ftab;
	while (ftab)
	{
		saff = recupflagl(ftab->str, saff);		
		ftab = ftab->next;
	}
	return (0);
}
