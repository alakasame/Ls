/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 05:25:38 by cmichaud          #+#    #+#             */
/*   Updated: 2016/02/10 08:56:50 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_l         *freeafflist(t_l **file, char *path, char *flag)
{
    t_l *list;

	list = *file;
	while (list)
	{
		if (isflag(flag, "l"))
			return (flagl(list, path));
		ft_putstr(list->str);
		ft_putstr("\n");
        free(list->str);
        free(list);
        list = list->next;
    }
    list = NULL;
    return (list);
}

t_l         *errorlist(t_l **file)
{
    DIR *rep;
    t_l *list;

	list = *file;
	while (list)
	{
		if (!(rep = opendir(list->str)))
            erroret(list->str);
        free(list->str);
        free(list);
        list = list->next;
    }
    list = NULL;
    return (list);
}
