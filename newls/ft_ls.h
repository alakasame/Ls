/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmichaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/15 08:13:18 by cmichaud          #+#    #+#             */
/*   Updated: 2016/02/10 08:57:20 by cmichaud         ###   ########.fr       */
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
	struct s_l			*back;
}						t_l;

typedef struct			s_aff
{
	int		link;
	int		usr;
	int		grp;
	int		byte;
	int		day;
	int		minor;
	int		major;
}						t_aff;

typedef struct			s_arg
{
	char				*npath;
	char				*lpath;
	char				*flag;
	t_l					*path;
	t_l					*file;
	t_stat				fs;
	t_stat				sf;
	t_dirent			*ent;
	DIR					*rep;
	int					y;
}						t_arg;

int						searchflag(char **argv, char **flag, int argc);
int						onlyflag(char **argv, int argc);
int						isflag(char *flag, char *a);
int						erroret(char *str);
int						isdirorfile(char *str);
t_l						*gofreenext(t_l *op);
int						isfile(char *str);
int						istrue(char *flag, char *file, char *sl, char *path);
int						ft_lenbr(int n);
char					*getpath(char *str, char *tmp);
char					**getfile(char *str, char **tab, int c);
t_l						*listadd(char *str);
t_l						*initlist(t_l **file, char *str, char *flag, char *path);
t_l						*listt(t_l **file, char *str, char *path);
t_l						*listr(t_l **file, char *str);
t_l						*alphalistsort(t_l **file, char *str);
t_l						*freeret(char **lpath, char **npath, t_l *list);
t_l						*cond1(t_arg *stmp, t_l **file);
t_l						*list_tr(t_l **list, char *arg, char *path, char *flag);
t_l						*no_sort(t_l **list, char *arg);
t_l						*listdelone(t_l *list);
t_l						*errorlist(t_l **list);
t_l						*freeafflist(t_l **list, char *path, char *flag);
//t_l						*sor(t_l *list);
//t_l						*sort(t_l *list, char *flag, char *path);
t_l						*recupft(t_arg file, DIR *rep, t_dirent *ent, char *path);
t_l						*afffile(t_l *ftab, char *flag, char *path);
t_l						*flagl(t_l *flag, char *path);
void					affflagl(char *str, t_aff saff, char *name);
void					nextaff(char *str, t_stat fs, t_aff saff, char *name);

#endif
