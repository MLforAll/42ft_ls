/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_fill_properties.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 00:48:01 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/05 20:47:51 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <grp.h>
#include <pwd.h>
#include "ft_ls.h"

static char		*get_elem_path(char *path, char *d_name)
{
	int			is_root;
	char		*ret;

	is_root = ft_strcmp(path, "/") == 0 ? 1 : 2;
	ret = ft_strnew(ft_strlen(path) + ft_strlen(d_name) + is_root);
	if (!ret)
		return (NULL);
	ft_strcat(ret, path);
	if (is_root == 2)
		ft_strcat(ret, "/");
	ft_strcat(ret, d_name);
	return (ret);
}

static char		*get_sym_path(char *path, off_t size)
{
	char	*ret;

	if (!(ret = ft_strnew(size + 1)))
		return (NULL);
	readlink(path, ret, size);
	return (ret);
}

static int		fill_usr_grp(t_stat *sstat, t_fstats *fstats)
{
	t_pw		*pw;
	t_group		*grp;

	grp = getgrgid(sstat->st_gid);
	pw = getpwuid(sstat->st_uid);
	fstats->grname = (!grp) ? ft_itoa(sstat->st_gid) : ft_strdup(grp->gr_name);
	fstats->usrname = (!pw) ? ft_itoa(sstat->st_uid) : ft_strdup(pw->pw_name);
	return ((fstats->grname != NULL && fstats->usrname != NULL));
}

static void		fill_if_smaller(size_t *dest, size_t new)
{
	if (*dest < new)
		*dest = new;
}

/*
** COMPATIBILITY CONCERNS:
** fstats->mtime = sstat.st_mtimespec.tv_sec;
** sstat.st_mtime; ==> compatibility with Linux
*/

int				fill_fstats(char *d_name, t_fstats *fstats, t_queue *queue)
{
	t_stat		sstat;
	off_t		size;

	if (!(fstats->fname = ft_strdup(d_name)))
		return (0);
	if (!(fstats->fpath = get_elem_path(queue->dname, d_name)))
		ft_strdel(&fstats->fname);
	if (!fstats->fpath || lstat(fstats->fpath, &sstat) == -1)
		return (0);
	fstats->nbblk = sstat.st_blocks;
	fstats->fmode = sstat.st_mode;
	fstats->mtime = sstat.st_mtime;
	size = sstat.st_size;
	fstats->size = size;
	fstats->nblink = sstat.st_nlink;
	fstats->sympath = (S_ISLNK(fstats->fmode)) ? get_sym_path(fstats->fpath, size) : NULL;
	if (!fill_usr_grp(&sstat, fstats))
		return (0);
	fill_if_smaller(&queue->maxlens[0], ft_nbrlen(fstats->nbblk));
	fill_if_smaller(&queue->maxlens[1], ft_nbrlen(fstats->nblink));
	fill_if_smaller(&queue->maxlens[2], !fstats->usrname ? 6 : ft_strlen(fstats->usrname));
	fill_if_smaller(&queue->maxlens[3], !fstats->grname ? 6 : ft_strlen(fstats->grname));
	fill_if_smaller(&queue->maxlens[4], ft_nbrlen(size));
	return (1);
}
