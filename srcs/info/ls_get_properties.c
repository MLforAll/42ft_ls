/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_get_properties.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 00:48:01 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/06 21:29:46 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include "ft_ls.h"

/*
** Improvements: In case of err, it'd be nice to free stuff
** before leaving...
*/

quad_t			get_file_content(t_queue *alst, t_fstats ***dc, char *d_name)
{
	quad_t		ret;

	if (!dc)
		return (-1);
	if (!*dc)
		*dc = &alst->dc;
	if (!(**dc = (t_fstats*)malloc(sizeof(t_fstats))))
		return (-1);
	if (!fill_fstats(d_name, **dc, alst))
		return (-1);
	(**dc)->next = NULL;
	ret = (**dc)->nbblk;
	*dc = &(**dc)->next;
	return (ret);
}

quad_t			get_dir_content(t_queue *alst, int optsb)
{
	DIR			*dirp;
	t_dirent	*dird;
	t_fstats	**tmp;
	quad_t		ret;
	quad_t		gfc_ret;

	if ((OPTEXISTS(optsb, A_LOPT) || OPTEXISTS(optsb, A_FFOPT))
		&& readlink(alst->dname, NULL, 0) == 0
		&& (alst->dname)[ft_strlen(alst->dname) - 1] != '/')
		return (-1);
	if (!(dirp = opendir(alst->dname)))
		return (-1);
	ret = 0;
	tmp = NULL;
	while ((dird = readdir(dirp)))
	{
		if (*dird->d_name != '.' || OPTEXISTS(optsb, A_AOPT))
		{
			if ((gfc_ret = get_file_content(alst, &tmp, dird->d_name)) == -1)
				return (-1);
			else
				ret += gfc_ret;
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
