/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_fill_properties.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 00:48:01 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/19 05:28:27 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/xattr.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include "ft_ls.h"

/*
** Functions that fill the linked lists
*/

static char		*ls_get_elem_path(char *path, char *d_name, char *fname)
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

static char		*get_sym_path(t_elem *elem)
{
	char	*ret;
	ssize_t	rl_ret;
	off_t	size;

	if (!S_ISLNK(elem->st.st_mode))
		return (NULL);
	ret = NULL;
	size = elem->st.st_size;
	rl_ret = 0;
	while (rl_ret == size || !ret)
	{
		size = (size == 0) ? 20 : size;
		if (ret)
		{
			size *= 2;
			ft_strdel(&ret);
		}
		if (!(ret = ft_strnew(size + 1)))
			return (NULL);
		rl_ret = readlink(elem->fpath, ret, size);
		if (elem->st.st_size > 0)
			break ;
	}
	return (ret);
}

static int		fill_usr_grp(t_elem *elem)
{
	t_grp		*elem_grp;
	t_pw		*elem_pw;

	elem_grp = optexists(A_NOPT) ? NULL : getgrgid(elem->st.st_gid);
	elem_pw = optexists(A_NOPT) ? NULL : getpwuid(elem->st.st_uid);
	if (!elem_grp)
		elem->grname = ft_itoa(elem->st.st_gid);
	else
		elem->grname = ft_strdup(elem_grp->gr_name);
	if (!elem_pw)
		elem->usrname = ft_itoa(elem->st.st_uid);
	else
		elem->usrname = ft_strdup(elem_pw->pw_name);
	return ((elem->grname != NULL && elem->usrname != NULL));
}

/*
** COMPATIBILITY CONCERNS:
** st.st_mtimespec.tv_sec;
** st.st_mtime; ==> compatibility with Linux
*/

int				fill_elem(char *d_name, t_elem *elem, t_group *grp)
{
	if (!(elem->fname = ft_strdup(d_name)))
		return (0);
	elem->fpath = ls_get_elem_path(grp->grp_name, d_name, elem->fname);
	if (!elem->fpath || lstat(elem->fpath, &elem->st) == -1)
		return (0);
	elem->sympath = get_sym_path(elem);
	if (!fill_usr_grp(elem))
		return (0);
	if ((elem->lxattr = listxattr(elem->fpath, NULL, 0, XATTR_NOFOLLOW)) > 0)
	{
		elem->xattrs = (char*)malloc(sizeof(char) * elem->lxattr);
		listxattr(elem->fpath, elem->xattrs, elem->lxattr, XATTR_NOFOLLOW);
	}
	fillinf(&grp->maxlens[0], ft_nbrlen(elem->st.st_blocks));
	fillinf(&grp->maxlens[1], ft_nbrlen(elem->st.st_nlink));
	fillinf(&grp->maxlens[2], !elem->usrname ? 6 : ft_strlen(elem->usrname));
	fillinf(&grp->maxlens[3], !elem->grname ? 6 : ft_strlen(elem->grname));
	if (S_ISCHR(elem->st.st_mode) || S_ISBLK(elem->st.st_mode))
		fillinf(&grp->maxlens[4], 8);
	else
		fillinf(&grp->maxlens[4], ft_nbrlen(elem->st.st_size));
	fillinf(&grp->maxlens[5], ft_strlen(elem->fname));
	return (1);
}
