/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flagl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 03:44:46 by cmichaud          #+#    #+#             */
/*   Updated: 2016/02/04 03:58:07 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		affflagl(char *str, char *tmp)
{
	t_stat		*fs;
	t_passwd	*mdp;
	t_group		*group;

	if (stat(str, fs) < 0 || !(mdp = getpwuid(fs.st_uid))
		|| !(group = getgrgid(fs.st_gid))
		return (0);
	
}
