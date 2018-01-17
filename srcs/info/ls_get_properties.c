/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_get_properties.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 00:48:01 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/17 19:00:26 by kdumarai         ###   ########.fr       */
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

t_blkc			get_file_content(t_group *alst, char *d_name)
{
	t_blkc			ret;
	t_elem			*new;

	if (!(new = ft_elem_new()))
		return (-1);
	ft_elem_add(&alst->elems, new);
	if (!fill_elem(d_name, new, alst))
		return (-1);
	if (!alst->grp_name && S_ISDIR(new->st.st_mode))
		return (-1);
	ret = new->st.st_blocks;
	alst->nbfiles++;
	return (ret);
}

static int		is_link(char *path)
{
	char	buff[1];

	if (path[ft_strlen(path) - 1] == '/')
		return (0);
	return ((readlink(path, buff, 0) == 0));
}

t_blkc			get_dir_content(t_group *alst)
{
	DIR				*dirp;
	t_dirent		*dird;
	t_blkc			rets[2];

	if (((OPTEXISTS(A_LOPT) || OPTEXISTS(A_FFOPT))
		&& is_link(alst->grp_name)) || !(dirp = opendir(alst->grp_name)))
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

void			free_dir_elem_content(t_elem **alst)
{
	t_elem		*tmp;
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
	if ((*alst)->xattrs)
		ft_strdel(&(*alst)->xattrs);
	free(*alst);
	*alst = tmp;
}

void			free_dir_content(t_elem **alst)
{
	while (*alst)
		free_dir_elem_content(alst);
	*alst = NULL;
}
