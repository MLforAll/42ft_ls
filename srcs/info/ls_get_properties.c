/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_get_properties.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 00:48:01 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/05 20:47:43 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <dirent.h>
#include "ft_ls.h"

/*
** Improvements: In case of err, it'd be nice to free stuff
** before leaving...
*/

quad_t			get_dir_content(t_queue *alst, int show_all)
{
	DIR			*dirp;
	t_dirent	*dird;
	t_fstats	**tmp;
	quad_t		ret;

	if (!(dirp = opendir(alst->dname)))
		return (-1);
	ret = 0;
	tmp = NULL;
	while ((dird = readdir(dirp)))
	{
		if (*dird->d_name != '.' || show_all)
		{
			tmp = (!tmp) ? &alst->dc : &(*tmp)->next;
			if (!(*tmp = (t_fstats*)malloc(sizeof(t_fstats))))
				return (-1);
			if (!fill_fstats(dird->d_name, *tmp, alst))
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
		if (curr->sympath)
			ft_strdel(&curr->sympath);
		if (curr->usrname)
			ft_strdel(&curr->usrname);
		if (curr->grname)
			ft_strdel(&curr->grname);
		free(curr);
		curr = tmp;
	}
	*alst = NULL;
}
