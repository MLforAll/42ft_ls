/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_fill_properties.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 00:48:01 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/10 21:26:03 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include "ft_ls.h"

static char		*get_elem_path(char *path, char *d_name, char *fname)
{
	int			is_root;
	size_t		pathlen;
	char		*ret;

	if (!path)
		return (fname);
	is_root = (path && ft_strcmp(path, "/") == 0);
	pathlen = (path) ? ft_strlen(path) : 0;
	if (!(ret = ft_strnew(pathlen + ft_strlen(d_name) + is_root + 1)))
		return (NULL);
	ft_strcat(ret, path);
	if (!is_root)
		ft_strcat(ret, "/");
	ft_strcat(ret, d_name);
	return (ret);
}

static char		*get_sym_path(t_fstats *dc)
{
	char	*ret;
	ssize_t	rl_ret;
	off_t	size;

	if (!S_ISLNK(dc->st.st_mode))
		return (NULL);
	ret = NULL;
	size = dc->st.st_size;
	rl_ret = 0;
	while (rl_ret == size)
	{
		size = (size == 0) ? 20 : size;
		if (ret)
		{
			size *= 2;
			ft_strdel(&ret);
		}
		if (!(ret = ft_strnew(size + 1)))
			return (NULL);
		rl_ret = readlink(dc->fpath, ret, size);
		if (dc->st.st_size > 0)
			break ;
	}
	return (ret);
}

static int		fill_usr_grp(t_fstats *dc)
{
	t_pw		*pw;
	t_group		*grp;

	grp = getgrgid(dc->st.st_gid);
	pw = getpwuid(dc->st.st_uid);
	if (!grp)
		dc->grname = ft_itoa(dc->st.st_gid);
	else
		dc->grname = ft_strdup(grp->gr_name);
	if (!pw)
		dc->usrname = ft_itoa(dc->st.st_uid);
	else
		dc->usrname = ft_strdup(pw->pw_name);
	return ((dc->grname != NULL && dc->usrname != NULL));
}

static void		fillinf(size_t *dest, size_t new)
{
	if (*dest < new)
		*dest = new;
}

/*
** COMPATIBILITY CONCERNS:
** st.st_mtimespec.tv_sec;
** st.st_mtime; ==> compatibility with Linux
*/

int				fill_fstats(char *d_name, t_fstats *dc, t_queue *queue)
{
	if (!(dc->fname = ft_strdup(d_name)))
		return (0);
	if (!(dc->fpath = get_elem_path(queue->dname, d_name, dc->fname)))
		ft_strdel(&dc->fname);
	if (!dc->fpath || lstat(dc->fpath, &dc->st) == -1)
		return (0);
	dc->sympath = get_sym_path(dc);
	if (!fill_usr_grp(dc))
		return (0);
	fillinf(&queue->maxlens[0], ft_nbrlen(dc->st.st_blocks));
	fillinf(&queue->maxlens[1], ft_nbrlen(dc->st.st_nlink));
	fillinf(&queue->maxlens[2], !dc->usrname ? 6 : ft_strlen(dc->usrname));
	fillinf(&queue->maxlens[3], !dc->grname ? 6 : ft_strlen(dc->grname));
	if (S_ISCHR(dc->st.st_mode) || S_ISBLK(dc->st.st_mode))
		fillinf(&queue->maxlens[4], 8);
	else
		fillinf(&queue->maxlens[4], ft_nbrlen(dc->st.st_size));
	return (1);
}
