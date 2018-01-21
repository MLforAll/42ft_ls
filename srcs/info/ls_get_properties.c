/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_get_properties.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 00:48:01 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/21 17:18:31 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include "ft_ls.h"

/*
** Functions that create the linked lists
*/

int				get_file_content(t_group *alst, char *d_name)
{
	t_elem			*new;

	if (!(new = ft_elem_new()))
		return (-1);
	if (!fill_elem(d_name, new, alst)
		|| (!alst->grp_name && S_ISDIR(new->st.st_mode)))
	{
		free_dir_elem_content(&new);
		return (0);
	}
	ft_elem_add(&alst->elems, new);
	alst->total += new->st.st_blocks;
	alst->nbfiles++;
	return (1);
}

static int		is_link(char *path)
{
	char	buff[1];

	if (path[ft_strlen(path) - 1] == '/')
		return (0);
	return ((readlink(path, buff, 0) == 0));
}

int				get_dir_content(t_group *alst, int chk_lnk)
{
	DIR				*dirp;
	t_dirent		*dird;

	if (chk_lnk && ((optexists(A_LOPT) || optexists(A_FFOPT))
		&& is_link(alst->grp_name)))
		return (-1);
	if (!(dirp = opendir(alst->grp_name)))
		return (0);
	while ((dird = readdir(dirp)))
	{
		if (*dird->d_name != '.' || optexists(A_AOPT))
			get_file_content(alst, dird->d_name);
	}
	free(dird);
	closedir(dirp);
	return (1);
}

void			free_dir_elem_content(t_elem **alst)
{
	t_elem		*tmp;
	int			path_nomalloc;

	if (!alst || !*alst)
		return ;
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
	if (!alst)
		return ;
	while (*alst)
		free_dir_elem_content(alst);
	*alst = NULL;
}
