/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_get_properties.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 00:48:01 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/12 20:36:34 by kdumarai         ###   ########.fr       */
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

t_blkc			get_file_content(t_queue *alst, t_fstats ***dc, char *d_name)
{
	t_blkc			ret;

	if (!dc)
		return (-1);
	if (!*dc)
		*dc = &alst->dc;
	if (!(**dc = (t_fstats*)malloc(sizeof(t_fstats))))
		return (-1);
	if (!fill_fstats(d_name, **dc, alst))
		return (-1);
	(**dc)->next = NULL;
	ret = (**dc)->st.st_blocks;
	*dc = &(**dc)->next;
	alst->nbfiles++;
	return (ret);
}

t_blkc			get_dir_content(t_queue *alst)
{
	DIR				*dirp;
	t_dirent		*dird;
	t_fstats		**tmp;
	t_blkc			rets[2];

	if (((OPTEXISTS(A_LOPT) || OPTEXISTS(A_FFOPT))
		&& readlink(alst->dname, NULL, 0) == 0
		&& (alst->dname)[ft_strlen(alst->dname) - 1] != '/')
		|| !(dirp = opendir(alst->dname)))
		return (-1);
	rets[0] = 0;
	tmp = NULL;
	while ((dird = readdir(dirp)))
	{
		if (*dird->d_name != '.' || OPTEXISTS(A_AOPT))
		{
			if ((rets[1] = get_file_content(alst, &tmp, dird->d_name)) == -1)
				return (-1);
			else
				rets[0] += rets[1];
		}
	}
	free(dird);
	closedir(dirp);
	return (rets[0]);
}

void			free_dir_content(t_fstats **alst)
{
	t_fstats		*curr;
	t_fstats		*tmp;
	int				path_nomalloc;

	curr = *alst;
	while (curr)
	{
		tmp = curr->next;
		path_nomalloc = (curr->fname == curr->fpath);
		if (curr->fname)
			ft_strdel(&curr->fname);
		if (!path_nomalloc && curr->fpath)
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

t_fstats	*get_nnext_elem(t_fstats *alst, size_t len)
{
	unsigned int	cnt;

	if (!alst)
		return (NULL);
	cnt = 0;
	while (alst && cnt++ < len)
		alst = alst->next;
	return (alst);
}
