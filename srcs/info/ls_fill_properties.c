/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_fill_properties.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 00:48:01 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/08 00:51:46 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include "ft_ls.h"

static char		*get_elem_path(char *path, char *d_name)
{
	int			is_root;
	size_t		pathlen;
	char		*ret;

	is_root = (path && ft_strcmp(path, "/") == 0);
	pathlen = (path) ? ft_strlen(path) : 0;
	ret = ft_strnew(pathlen + ft_strlen(d_name) + is_root + 1);
	if (!ret)
		return (NULL);
	if (path)
		ft_strcat(ret, path);
	if (!is_root && path)
		ft_strcat(ret, "/");
	ft_strcat(ret, d_name);
	return (ret);
}

static char		*get_sym_path(t_fstats *fstats)
{
	char	*ret;
	char	*path;
	off_t	size;

	path = fstats->fpath;
	size = fstats->st.st_size;
	if (!S_ISLNK(fstats->st.st_mode) || !(ret = ft_strnew(size + 1)))
		return (NULL);
	readlink(path, ret, size);
	return (ret);
}

static int		fill_usr_grp(t_fstats *fstats)
{
	t_pw		*pw;
	t_group		*grp;

	grp = getgrgid(fstats->st.st_gid);
	pw = getpwuid(fstats->st.st_uid);
	if (!grp)
		fstats->grname = ft_itoa(fstats->st.st_gid);
	else
		fstats->grname = ft_strdup(grp->gr_name);
	if (!pw)
		fstats->usrname = ft_itoa(fstats->st.st_uid);
	else
		fstats->usrname = ft_strdup(pw->pw_name);
	return ((fstats->grname != NULL && fstats->usrname != NULL));
}

static void		fillinf(size_t *dest, size_t new)
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
	if (!(fstats->fname = ft_strdup(d_name)))
		return (0);
	if (!(fstats->fpath = get_elem_path(queue->dname, d_name)))
		ft_strdel(&fstats->fname);
	if (!fstats->fpath || lstat(fstats->fpath, &fstats->st) == -1)
		return (0);
	fstats->sympath = get_sym_path(fstats);
	if (!fill_usr_grp(fstats))
		return (0);
	fillinf(&queue->maxlens[0], ft_nbrlen(fstats->st.st_blocks));
	fillinf(&queue->maxlens[1], ft_nbrlen(fstats->st.st_nlink));
	fillinf(&queue->maxlens[2], !fstats->usrname ? 6 : ft_strlen(fstats->usrname));
	fillinf(&queue->maxlens[3], !fstats->grname ? 6 : ft_strlen(fstats->grname));
	fillinf(&queue->maxlens[4], ft_nbrlen(fstats->st.st_size));
	return (1);
}
