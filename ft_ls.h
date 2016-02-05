/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/15 08:13:18 by cmichaud          #+#    #+#             */
/*   Updated: 2016/02/05 19:36:57 by cmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "libft/includes/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <errno.h>
# include <stdio.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>

typedef struct tm		t_time;
typedef struct passwd	t_passwd;
typedef struct group	t_group;
typedef struct dirent	t_dirent;
typedef struct stat		t_stat;

typedef struct			s_l
{
	char				*str;
	struct s_l			*next;
}						t_l;

typedef struct			s_aff
{
	int		tailleline;
	int		tailletab;
	int		tailleblock;
	char	**tab;
	char	*flag;
	int		*sort;
}						t_aff;

typedef struct			s_arg
{
	char				*flag;
	t_l					*trep;
	t_l					*terror;
}						t_arg;

typedef struct			s_work
{
	char				*flag;
	t_l					*rtab;
	t_l					*ftab;
}						t_work;

int						searchflag(char **argv, char **flag, int argc);
int						onlyflag(char **argv, int argc);
int						ft_ls1(char const *str);
int						ft_ls3(char const *str, char *flag);
int						ft_ls2(int argc, char **argv, char *flag);
int						isflag(char *flag, char a);
int						erroret(char *str);
int						isopen(char *str);
char					**getfile(char *str, char **tab, int c);
t_l						*listadd(t_l *list, char *arg);
t_l						*freeafflist(t_l *list);
t_l						*sor(t_l *list);
t_l						*sort(t_l *list, char *flag);
t_work					recupft(t_work file, DIR *rep, t_dirent *ent, char *rstr);
t_l						*afffile(t_l *ftab, char *flag);
char					*affflagl(char *str, char *tmp);

#endif
