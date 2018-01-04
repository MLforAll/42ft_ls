/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_get_properties.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 00:48:01 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/04 04:37:08 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <dirent.h>
#include "ft_ls.h"

int				get_dir_content(t_queue *alst, int show_all)
{
	DIR			*dirp;
	t_dirent	*dird;
	t_fstats	**tmp;
	int			ret;

	if (!(dirp = opendir(alst->dname)))
		return (-1);
	ret = 0;
	tmp = NULL;
	while ((dird = readdir(dirp)))
	{
		if (*dird->d_name != '.' || show_all)
		{
			if (!tmp)
				tmp = &alst->dc;
			else
				tmp = &(*tmp)->next;
			*tmp = (t_fstats*)malloc(sizeof(t_fstats));
			if (((*tmp)->nbblk = fill_fstats(dird, *tmp, alst)) == -1)
				return (-1);
			ret += (*tmp)->nbblk;
			(*tmp)->next = NULL;
		}
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
