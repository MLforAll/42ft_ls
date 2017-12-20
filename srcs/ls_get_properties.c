/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_get_properties.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 00:48:01 by kdumarai          #+#    #+#             */
/*   Updated: 2017/12/20 21:40:11 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <grp.h>
#include <pwd.h>
#include "ft_ls.h"

static char		get_ifmt_char(mode_t st_mode)
{
	if ((st_mode & S_IFMT) == S_IFDIR)
		return ('d');
	if ((st_mode & S_IFMT) == S_IFLNK)
		return ('l');
	if ((st_mode & S_IFMT) == S_IFBLK)
		return ('b');
	if ((st_mode & S_IFMT) == S_IFCHR) /* Not sure about that one */
		return ('c');
	if ((st_mode & S_IFMT) == S_IFIFO) /* Not sure about that one */
		return ('f');
	return ('-');
}

static int		fill_fstats(const char *path, t_dirent *dird, t_fstats *fstats)
{
	t_stat		sstat;
	t_pw		*pw;
	t_group		*grp;
	int			staterr;

	if (!(fstats->fname = ft_strdup(dird->d_name)))
		return (0);
	if (!(fstats->fpath = ft_strnew(ft_strlen(path) + ft_strlen(dird->d_name) + 1)))
		return (0);
	ft_strcat(fstats->fpath, path);
	ft_strcat(fstats->fpath, "/");
	ft_strcat(fstats->fpath, fstats->fname);
	if ((staterr = stat(fstats->fpath, &sstat)) == -1)
		return (staterr);
	fstats->ftype = get_ifmt_char(sstat.st_mode);
	fstats->mtime = sstat.st_mtimespec.tv_sec;
	fstats->size = sstat.st_size;
	fstats->nblink = sstat.st_nlink;
	grp = getgrgid(sstat.st_gid);
	pw = getpwuid(sstat.st_uid);
	fstats->grname = (grp != NULL) ? grp->gr_name : NULL;
	fstats->usrname = (pw != NULL) ? pw->pw_name : NULL;
	return (1);
}

int				get_dir_content(const char *path, t_fstats **alst)
{
	DIR			*dirp;
	t_dirent	*dird;
	t_fstats	**tmp;
	int			ret;
	
	if (!(dirp = opendir(path)))
		return (-1);
	ret = 0;
	tmp = NULL;
	while ((dird = readdir(dirp)))
	{
		if (!tmp)
			tmp = alst;
		else
			tmp = &(*tmp)->next;
		*tmp = (t_fstats*)malloc(sizeof(t_fstats));
		ret += fill_fstats(path, dird, *tmp);
		(*tmp)->next = NULL;
	}
	free(dird);
	closedir(dirp);
	return (ret);
}

void			free_dir_content(t_fstats **alst)
{
	t_fstats	*curr;
	t_fstats	*tmp;

	curr = *alst;
	while (curr)
	{
		tmp = curr->next;
		if (curr->fname)
			ft_strdel(&curr->fname);
		if (curr->fpath)
			ft_strdel(&curr->fpath);
		free(curr);
		curr = tmp;
	}
	*alst = NULL;
}
