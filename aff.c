/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 19:33:06 by cmichaud          #+#    #+#             */
/*   Updated: 2016/02/05 20:10:39 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_l     *afffile(t_l *ftab, char *flag)
{
    t_l     *tmp;
    char    *str;

    str = flag;//= NULL;
    while (ftab)
    {
//      if (isflag(flag, 'l'))
        //      str = affflagl(ftab->str, str);
//      else
        //  {
		ft_putstr(ftab->str);
		ft_putstr("\t");
		//  }
        free(ftab->str);
        tmp = ftab->next;
        free(ftab);
        ftab = tmp;
    }
    ftab = NULL;
    return (ftab);
}

t_l         *freeafflist(t_l *list)
{
    DIR *rep;
    t_l *listnext;

    while (list)
    {
        if (!(rep = opendir(list->str)))
            erroret(list->str);
        listnext = list->next;
        free(list->str);
        free(list);
        list = listnext;
    }
    list = NULL;
    return (list);
}
