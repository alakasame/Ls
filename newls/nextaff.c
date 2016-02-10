/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 19:33:06 by cmichaud          #+#    #+#             */
/*   Updated: 2016/02/10 10:00:55 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ultraeasy(char *path, t_stat fs, char *name, t_aff saff)
{
	int		i;
	char	*str;

	if (saff.minor != 0 && saff.major != 0)
	{
		if (S_ISCHR(fs.st_mode) || S_ISBLK(fs.st_mode))
		{
			ft_putstr(" ");
			if ((saff.minor + saff.major + 2) < saff.byte)
			{
				i = saff.minor + saff.major + 2;
				while (saff.byte > i++)
					ft_putstr(" ");
				i = ft_lenbr(major(fs.st_rdev));
				while (saff.major > i++)
					ft_putstr(" ");
				ft_putstr((str = ft_itoa(major(fs.st_rdev))));
				ft_putstr(", ");
				free(str);
				i = ft_lenbr(minor(fs.st_rdev));
				while (saff.minor > i++)
						ft_putstr(" ");
				ft_putstr((str = ft_itoa(minor(fs.st_rdev))));
				free(str);
			}
			else
			{
				i = ft_lenbr(major(fs.st_rdev));
				while (saff.major > i++)
					ft_putstr(" ");
				ft_putstr((str = ft_itoa(major(fs.st_rdev))));
				ft_putstr(", ");
				free(str);
				i = ft_lenbr(minor(fs.st_rdev));
				while (saff.minor > i++)
					ft_putstr(" ");
				ft_putstr((str = ft_itoa(minor(fs.st_rdev))));
				free(str);
			}
		}
		else
		{
			if ((saff.minor + saff.major + 2) > saff.byte)
			{
				i = ft_lenbr(fs.st_size);
				while ((saff.minor + saff.major + 3) > i++)
					ft_putstr(" ");
				ft_putstr((str = ft_itoa(fs.st_size)));
				free(str);
			}			
			else
			{
				i = ft_lenbr(fs.st_size);
				while (saff.byte > i++)
					ft_putstr(" ");
				ft_putstr((str = ft_itoa(fs.st_size)));
				free(str);
			}
		}
	}
	else
	{
		i = ft_lenbr(fs.st_size);
		while (saff.byte > i++)
			ft_putstr(" ");
		ft_putstr((str = ft_itoa(fs.st_size)));
		free(str);
	}
	ft_putstr(" ");
	str = ctime(&fs.st_mtime);
	i = 3;
	if (time(0) - fs.st_mtime < 15778800 && time(0) - fs.st_mtime > 0)
	{
		while (str[++i] != ':')
			write(1, &str[i], 1);
		write(1, ":", 1);
		while (str[++i] != ':')
			write(1, &str[i], 1);
	}
	else
	{
		while (!ft_isdigit(str[++i]))
			write(1, &str[i], 1);
		write(1, &str[i++], 1);
		i += 9;
		ft_putstr(" ");
		write(1, &str[i], 5);
	}
	ft_putstr(" ");
	ft_putstr(name);
	if (!(str = (char *)malloc(sizeof(char) * 256)))
		return ;
	if (S_ISLNK(fs.st_mode))
	{
		if ((i = readlink(path, str, sizeof(str)-1)) != -1)
			str[i] = '\0';
		ft_putstr(" -> ");
		ft_putstr(str);
	}
	free(str);
	ft_putstr("\n");
	(void)path;
	(void)name;
}

void	easynextl(char *path, t_stat fs, char *name, t_aff saff)
{
	int			i;
	t_passwd	*user;
	t_group		*group;

	if (!(group = getgrgid(fs.st_gid)) || !(user = getpwuid(fs.st_uid)))
		return ;
	ft_putstr(user->pw_name);
	i = ft_strlen(user->pw_name);
	while (saff.usr > i++)
		ft_putstr(" ");
	ft_putstr("  ");
	ft_putstr(group->gr_name);
	i = ft_strlen(group->gr_name);
	while (saff.grp > i++)
		ft_putstr(" ");
	ft_putstr("  ");
	ultraeasy(path, fs, name, saff);
}

void	nextaff(char *path, t_stat fs, t_aff saff, char *name)
{
	int		i;
	char	*str;

    fs.st_mode & S_IRUSR ? ft_putstr("r") : ft_putstr("-");
    fs.st_mode & S_IWUSR ? ft_putstr("w") : ft_putstr("-");
    fs.st_mode & S_IXUSR ? ft_putstr("x") : ft_putstr("-");
    fs.st_mode & S_IRGRP ? ft_putstr("r") : ft_putstr("-");
    fs.st_mode & S_IWGRP ? ft_putstr("w") : ft_putstr("-");
    fs.st_mode & S_IXGRP ? ft_putstr("x") : ft_putstr("-");
    fs.st_mode & S_IROTH ? ft_putstr("r") : ft_putstr("-");
    fs.st_mode & S_IWOTH ? ft_putstr("w") : ft_putstr("-");
    fs.st_mode & S_IXOTH ? ft_putstr("x") : ft_putstr("-");
	ft_putstr("  ");
	i = ft_lenbr(fs.st_nlink);
	while (saff.link > i++)
		ft_putstr(" ");
	ft_putstr((str = ft_itoa(fs.st_nlink)));
	free(str);
	ft_putstr(" ");
	return (easynextl(path, fs, name, saff));
}
