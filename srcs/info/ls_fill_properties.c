/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_fill_properties.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 00:48:01 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/04 05:53:45 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <grp.h>
#include <pwd.h>
#include "ft_ls.h"

static int		get_num_bytes(off_t size)
{
	int			nlen;
	int			ret;

	if (size == 0)
		return (0);
	ret = 0;
	nlen = 0;
	while (size)
	{
		nlen++;
		size /= 2;
	}
	nlen += (nlen == 0);
	while (ret < nlen)
		ret += 8;
	return (ret);
}

static char		*get_elem_path(char *path, char *fname, char *d_name)
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
	ft_strcat(ret, fname);
	return (ret);
}

static int		fill_usr_grp(t_stat *sstat, t_fstats *fstats)
{
	t_pw		*pw;
	t_group		*grp;

	grp = getgrgid(sstat->st_gid);
	pw = getpwuid(sstat->st_uid);
	if (grp)
		if (!(fstats->grname = ft_strdup(grp->gr_name)))
			return (0);
	if (pw)
		if (!(fstats->usrname = ft_strdup(pw->pw_name)))
			return (0);
	return (1);
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
	int			nbblocks;

	if (!(fstats->fname = ft_strdup(d_name)))
		return (-1);
	if (!(fstats->fpath = get_elem_path(queue->dname, fstats->fname, d_name)))
		ft_strdel(&fstats->fname);
	if (!fstats->fname || stat(fstats->fpath, &sstat) == -1)
		return (-1);
	fstats->fmode = sstat.st_mode;
	fstats->mtime = sstat.st_mtime;
	size = sstat.st_size;
	fstats->size = size;
	fstats->nblink = sstat.st_nlink;
	if (!fill_usr_grp(&sstat, fstats))
		return (-1);
	nbblocks = get_num_bytes(size);
	fill_if_smaller(&queue->maxlens[0], ft_nbrlen(nbblocks));
	fill_if_smaller(&queue->maxlens[1], ft_nbrlen(fstats->nblink));
	fill_if_smaller(&queue->maxlens[2], ft_strlen(fstats->usrname));
	fill_if_smaller(&queue->maxlens[3], ft_strlen(fstats->grname));
	fill_if_smaller(&queue->maxlens[4], ft_nbrlen(size));
	return (((fstats->fmode & S_IFMT) == S_IFREG) ? nbblocks : 0);
}
