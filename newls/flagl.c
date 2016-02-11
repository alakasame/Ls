/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flagl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 03:44:46 by cmichaud          #+#    #+#             */
/*   Updated: 2016/02/11 14:37:41 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		affflagl(char *str, t_aff saff, char *name)
{
	t_stat		fs;

	if (lstat(str, &fs) < 0)
		return ;
	if (S_ISDIR(fs.st_mode))
		ft_putstr("d");
	if (S_ISCHR(fs.st_mode))
		ft_putstr("c");
	if (S_ISBLK(fs.st_mode))
		ft_putstr("b");
	if (S_ISLNK(fs.st_mode))
		ft_putstr("l");
	if (S_ISSOCK(fs.st_mode))
		ft_putstr("s");
	if (S_ISFIFO(fs.st_mode))
		ft_putstr("p");
	if (S_ISREG(fs.st_mode))
		ft_putstr("-");
	nextaff(str, fs, saff, name);
}

t_aff		recupflagl(char *str, t_aff saff)
{
	t_stat		fs;
	t_passwd	*user;
	t_group		*group;

	if (lstat(str, &fs) < 0)
		return (saff);
	if (S_ISCHR(fs.st_mode) || S_ISBLK(fs.st_mode))
	{
		if (saff.major < ft_lenbr(major(fs.st_rdev)))
			saff.major = ft_lenbr(major(fs.st_rdev));
		if (saff.minor < ft_lenbr(minor(fs.st_rdev)))
			saff.minor = ft_lenbr(minor(fs.st_rdev));
	}
	else if (saff.byte < ft_lenbr(fs.st_size))
		saff.byte = ft_lenbr(fs.st_size);
	saff.block += fs.st_blocks;
	if (!(user = getpwuid(fs.st_uid)) || !(group = getgrgid(fs.st_gid)))
		return (saff);
	if ((int)ft_lenbr(fs.st_nlink) > saff.link)
		saff.link = ft_lenbr(fs.st_nlink);
	if (!user->pw_name)
	{
		if ((int)user->pw_uid > saff.usr)
			saff.usr = ft_lenbr(user->pw_uid);
	}
	else if ((int)ft_strlen(user->pw_name) > saff.usr)
		 saff.usr = ft_strlen(user->pw_name);
	if (!group->gr_name)
	{
		if ((int)group->gr_gid > saff.grp)
			saff.grp = ft_lenbr(group->gr_gid);
	}
	else if ((int)ft_strlen(group->gr_name) > saff.grp)
		saff.grp = ft_strlen(group->gr_name);	
	return (saff);
}

t_aff		inits(t_aff saff)
{
	saff.link = 0;
	saff.block = 0;
	saff.usr = 0;
	saff.grp = 0;
	saff.byte = 0;
	saff.day = 0;
	saff.minor = 0;
	saff.major = 0;
	return (saff);
}

t_l			*flagl(t_l *ftab, char *path, int i)
{
	t_aff		saff;
	char		*npath;
	t_l			*tmp;
	char		*str;

	saff = inits(saff);
	tmp = ftab;
	while (ftab)
	{
		npath = getpath(path, ftab->str);
		saff = recupflagl(npath, saff);
		free(npath);
		ftab = ftab->next;
	}
	ftab = tmp;
	if (i == 1)
	{
		str = ft_itoa(saff.block);
		ft_putstr("total ");
		ft_putstr(str);
		ft_putstr("\n");
		free(str);
	}
	while (ftab)
	{
		npath = getpath(path, ftab->str);
		affflagl(npath, saff, ftab->str);
		free(npath);
		ftab = gofreenext(ftab);
		ft_putstr("\n");
	}
	return (0);
}
