/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_get_properties.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 00:48:01 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/16 17:01:46 by kdumarai         ###   ########.fr       */
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

t_blkc			get_file_content(t_queue *alst, char *d_name)
{
	t_blkc			ret;
	t_fstats		*new;

	if (!(new = ft_dcnew()))
		return (-1);
	ft_dcadd(&alst->dc, new);
	if (!fill_fstats(d_name, new, alst))
		return (-1);
	if (!alst->dname && S_ISDIR(new->st.st_mode))
		return (-1);
	ret = new->st.st_blocks;
	alst->nbfiles++;
	return (ret);
}

t_blkc			get_dir_content(t_queue *alst)
{
	DIR				*dirp;
	t_dirent		*dird;
	t_blkc			rets[2];

	if (((OPTEXISTS(A_LOPT) || OPTEXISTS(A_FFOPT))
		&& readlink(alst->dname, NULL, 0) == 0
		&& (alst->dname)[ft_strlen(alst->dname) - 1] != '/')
		|| !(dirp = opendir(alst->dname)))
		return (-1);
	rets[0] = 0;
	while ((dird = readdir(dirp)))
	{
		if (*dird->d_name != '.' || OPTEXISTS(A_AOPT))
		{
			if ((rets[1] = get_file_content(alst, dird->d_name)) == -1)
				return (-1);
			else
				rets[0] += rets[1];
		}
	}
	free(dird);
	closedir(dirp);
	return (rets[0]);
}

void			free_dir_elem_content(t_fstats **alst)
{
	t_fstats	*tmp;
	int			path_nomalloc;

	tmp = (*alst)->next;
	path_nomalloc = ((*alst)->fname == (*alst)->fpath);
	if ((*alst)->fname)
		ft_strdel(&(*alst)->fname);
	if (!path_nomalloc && (*alst)->fpath)
		ft_strdel(&(*alst)->fpath);
	if ((*alst)->sympath)
		ft_strdel(&(*alst)->sympath);
	if ((*alst)->usrname)
		ft_strdel(&(*alst)->usrname);
	if ((*alst)->grname)
		ft_strdel(&(*alst)->grname);
	free(*alst);
	*alst = tmp;
}

void			free_dir_content(t_fstats **alst)
{
	while (*alst)
		free_dir_elem_content(alst);
	*alst = NULL;
}
