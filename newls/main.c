/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 01:15:01 by cmichaud          #+#    #+#             */
/*   Updated: 2016/02/10 04:34:46 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*int		nextmain(t_arg *file, t_l *error)
{


	return (0);
	}*/

int		main(int argc, char **argv)
{
	int		i;
	t_arg	file;
	t_l		*error;

	file.flag = NULL;
	file.file = NULL;
	file.path = NULL;
	error = NULL;
	i = searchflag(argv, &file.flag, argc);
	if (i + 1 == argc)
		file.path = listadd(".");
	while (++i < argc)
	{
		if (isdirorfile(argv[i]) == 1)
			file.path = initlist(&file.path, argv[i], file.flag, ".");
		if (isdirorfile(argv[i]) == 2)
		{
			ft_putstr("try file main \n");
			ft_putstr(argv[i]);
			file.file = initlist(&file.file, argv[i], file.flag, ".");
		}
		else
			error = initlist(&error, argv[i], "o", NULL);
	}
	while (file.file)
	{
		ft_putstr("\nTEST AFF FILE MAIN\n");
		ft_putstr(file.file->str);
		file.file = file.file->next;
	}
	while (file.path)
	{
		ft_putstr("\nTEST AFF PATH MAIN\n");
		ft_putstr(file.path->str);
		file.path = file.path->next;
	}
	return (0);
}
