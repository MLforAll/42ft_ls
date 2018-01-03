/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_get_properties.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 00:48:01 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/03 19:39:39 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <dirent.h>
#include "ft_ls.h"

int				get_dir_content(const char *path, t_queue *alst)
{
	DIR			*dirp;
	t_dirent	*dird;
	t_fstats	**tmp;

	if (!(dirp = opendir(path)))
		return (-1);
	ret = 0;
	tmp = NULL;
	while ((dird = readdir(dirp)))
	{
		if (!tmp)
			tmp = &alst->dc;
		else
			tmp = &(*tmp)->next;
		*tmp = (t_fstats*)malloc(sizeof(t_fstats));
		if (((*tmp)->nbblk = fill_fstats(path, dird, *tmp, alst)) == -1)
			return (-1);
		alst->maxlens[0] = (*tmp)->nbblk;
		ret += (*tmp)->nbblk;
		(*tmp)->next = NULL;
	}
	free(dird);
	closedir(dirp);
	return (1);
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
		if (curr->usrname)
			ft_strdel(&curr->usrname);
		if (curr->grname)
			ft_strdel(&curr->grname);
		free(curr);
		curr = tmp;
	}
	*alst = NULL;
}

size_t			dclen(t_fstats *dc)
{
	size_t		ret;

	ret = 0;
	while (dc)
	{
		ret++;
		dc = dc->next;
	}
	return (ret);
}
