/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_queuing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/23 21:21:40 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/17 21:36:12 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include "ft_ls.h"

static int			try_file(t_group **files, char *path)
{
	int			errno_bak;
	int			err_gfc;

	errno_bak = errno;
	if (!files)
		return (0);
	if (!*files)
		*files = ft_group_new(NULL);
	if ((err_gfc = get_file_content(*files, path)) == -1)
	{
		ft_lsprint_fd(2, "%s: %s: %s\n", PRGM_NAME, path, strerror(errno_bak));
		free_dir_elem_content(&(*files)->elems);
		if (!(*files)->elems)
			ft_group_del(files);
		return (0);
	}
	(*files)->total += err_gfc;
	return (1);
}

static int			get_groups(t_group **groups, t_list *paths)
{
	t_group		*files;
	t_group		*new;
	int			err;

	if (!groups)
		return (-1);
	*groups = NULL;
	files = NULL;
	err = 0;
	while (paths)
	{
		new = ft_group_new((char*)paths->content);
		if ((new->total = get_dir_content(new)) == -1)
		{
			ft_group_del(&new);
			if (!try_file(&files, (char*)paths->content))
				err += (err == 0);
		}
		else
			ft_group_push(groups, new);
		paths = paths->next;
	}
	if (files)
		ft_group_add(groups, files);
	return (err);
}

static t_list		*print_group_props(t_group *grp)
{
	int			rev;
	t_elem		*bw;
	t_list		*ret;

	if (!grp || !grp->elems || grp->total == -1)
		return (NULL);
	rev = OPTEXISTS(A_ROPT);
	sort_ls(&grp->elems, OPTEXISTS(A_TOPT) ? &sort_mtime : &sort_alpha, rev);
	if ((OPTEXISTS(A_LOPT) || OPTEXISTS(A_SOPT)) && grp->grp_name)
		ft_lsprint("total %l\n", grp->total);
	print_elems(grp);
	ret = NULL;
	bw = grp->elems;
	if (OPTEXISTS(A_RROPT))
	{
		while (bw)
		{
			if (S_ISDIR(bw->st.st_mode) && ft_strcmp(bw->fname, ".")
				&& ft_strcmp(bw->fname, ".."))
				ft_lstpushback(&ret, bw->fpath, ft_strlen(bw->fpath) + 1);
			bw = bw->next;
		}
	}
	free_dir_content(&grp->elems);
	return (ret);
}

static int			print_groups(t_group *groups, int add_nl)
{
	t_group		*tmp;
	t_list		*reclst;
	int			err;

	tmp = groups;
	err = 0;
	while (tmp)
	{
		if (tmp != groups || add_nl)
			ft_putchar('\n');
		if (((groups->next) || add_nl) && tmp->grp_name)
			ft_lsprint("%s:\n", tmp->grp_name);
		reclst = print_group_props(tmp);
		if (reclst)
			err = list_dirs(&reclst, 1);
		tmp = tmp->next;
	}
	return (err);
}

int					list_dirs(t_list **paths, int add_nl)
{
	int			err;
	int			print_err;
	t_group		*groups;

	ft_lstsort(paths, &ft_lst_sortalpha);
	err = get_groups(&groups, *paths);
	print_err = print_groups(groups, add_nl);
	ft_group_delall(&groups);
	ft_lstdel(paths, &ft_lstdelf);
	return ((err || print_err));
}
