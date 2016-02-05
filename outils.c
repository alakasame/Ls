/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 08:35:11 by cmichaud          #+#    #+#             */
/*   Updated: 2016/02/05 19:35:16 by cmichaud         ###   ########.fr       */
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

int			isopen(char *str)
{
	DIR *rep;

	if ((rep = opendir(str)) == NULL)
		return (0);
	if (closedir(rep) == -1)
		return (erroret(str));
	return (1);
}

