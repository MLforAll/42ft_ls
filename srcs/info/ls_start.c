/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/23 21:21:40 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/20 20:50:37 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include "ft_ls.h"

/*
** my ft_ls works in the following fashion:
**
**	it tries to read every path.
**		when reading a path, it assumes it's a folder
**		if reading fails, it now assumes it's a file
**		if errno is set to ENOENT or ENOTDIR
**	upon completion, it caches the new folder (or group).
**	if it is at 'lvl0', meaning it's the first iteration of those funcs.
**	otherwise, it shows and frees directly.
**
**	if a sorting option such as -t and -r are found, the cached groups
**	are sorted using a merge sort algorithm applied to linked list.
*/

static t_list	*print_group_props(t_group *grp)
{
	int			rev;
	t_elem		*bw;
	t_list		*ret;

	if (!grp || !grp->elems || grp->total == -1)
		return (NULL);
	rev = optexists(A_ROPT);
	sort_ls(&grp->elems, optexists(A_TOPT) ? &sort_mtime : &sort_alpha, rev);
	if ((optexists(A_LOPT) || optexists(A_SOPT)) && grp->grp_name)
		ft_lsprint("total %l\n", grp->total);
	print_elems(grp);
	ret = NULL;
	bw = grp->elems;
	if (optexists(A_RROPT))
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

static int		print_groups(t_group *groups, int force_print, int add_nl)
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
		if (((groups->next) || add_nl || force_print) && tmp->grp_name)
			ft_lsprint("%s:\n", tmp->grp_name);
		if (tmp->err >= 0)
		{
			ls_elem_err(tmp->grp_name, tmp->err);
			err += 1;
		}
		reclst = print_group_props(tmp);
		if (reclst)
			err += list_dirs(&reclst, 1);
		tmp = tmp->next;
	}
	return (err);
}

static int		try_file(t_group **files, char *path, int getd_ret)
{
	int			get_ret;
	int			errno_bak;

	errno_bak = errno;
	if (!files || (errno != ENOTDIR && errno != ENOENT && getd_ret != -1))
		return (-1);
	if (!*files)
		*files = ft_group_new(NULL);
	if ((get_ret = get_file_content(*files, path)) <= 0)
	{
		ls_elem_err(path, errno_bak);
		if (get_ret == -1)
			return (0);
		if (!(*files)->elems)
			ft_group_del(files);
		return (0);
	}
	return (1);
}

static int		get_group(t_group **dirs, t_group **files, char *path, int now)
{
	t_group		*new;
	int			getd_ret;
	int			tryf_err;
	int			err;

	err = 0;
	if (!dirs || !files || !(new = ft_group_new(path)))
		return (-1);
	if ((getd_ret = get_dir_content(new)) <= 0)
	{
		free_dir_content(&new->elems);
		if ((tryf_err = try_file(files, path, getd_ret)) <= 0)
			err = (tryf_err == -1) ? 2 : 1;
		if (tryf_err == -1)
			new->err = errno;
		else
			ft_group_del(&new);
	}
	if (now)
	{
		err = print_groups(new, 0, 1);
		ft_group_del(&new);
	}
	ft_group_push(dirs, new);
	return (err);
}

int				list_dirs(t_list **paths, int add_nl)
{
	int			err;
	int			aux_err;
	t_list		*bw;
	t_group		*groups;
	t_group		*files;

	groups = NULL;
	files = NULL;
	bw = *paths;
	err = 0;
	while (bw)
	{
		if ((aux_err = get_group(&groups, &files, bw->content, add_nl)) == -1)
			return (1);
		err += (aux_err == 1);
		bw = bw->next;
	}
	if (!add_nl && !err)
		launch_groups_sort(&groups);
	ft_group_add(&groups, files);
	if (!add_nl)
		err += print_groups(groups, (err > 0), add_nl);
	ft_group_delall(&groups);
	ft_lstdel(paths, &ft_lstdelf);
	return ((err > 0 || aux_err > 0));
}
