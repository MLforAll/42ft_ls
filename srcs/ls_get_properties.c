/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_get_properties.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 00:48:01 by kdumarai          #+#    #+#             */
/*   Updated: 2017/12/17 05:38:58 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>
#include <sys/stat.h>
#include <grp.h>
#include <pwd.h>
#include "ft_ls.h"

/*
** printf is later to be replaced by ft_printf
*/

static int		fill_fstats(const char *path, t_dirent *dird, t_fstats *fstats)
{
	t_stat		sstat;
	char		*fp;
	char		*timec;

	fstats->fname = dird->d_name;
	if (!(fp = ft_strnew(ft_strlen(path) + ft_strlen(dird->d_name) + 1)))
		return (0);
	ft_strcat(fp, path);
	ft_strcat(fp, "/");
	ft_strcat(fp, fstats->fname);
	stat(fp, &sstat);
	timec = ctime(&sstat.st_atimespec.tv_sec);
	fstats->timec = ft_strsub(timec, 0, ft_strlen(timec) - 1);
	fstats->size = sstat.st_size;
	fstats->nblink = sstat.st_nlink;
	fstats->grname = getgrgid(sstat.st_gid)->gr_name;
	fstats->usrname = getpwuid(sstat.st_uid)->pw_name;
	ft_strdel(&fp);
	return (1);
}

static void		print_file(const char *path, t_dirent *dird)
{
	t_fstats	fstats;
	
	if (!fill_fstats(path, dird, &fstats))
		exit(1);
	printf("perms %i %s %s %lli %s %s\n", fstats.nblink, fstats.usrname, fstats.grname, fstats.size, fstats.timec, dird->d_name);
	ft_strdel(&fstats.timec);
	
}

void			get_dir_content(const char *path)
{
	DIR			*dirp;
	t_dirent	*dird;
	
	if (!(dirp = opendir(path)))
		return ;
	while ((dird = readdir(dirp)))
		print_file(path, dird);
	free(dird);
	closedir(dirp);
}
