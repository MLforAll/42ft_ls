/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_queuing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/23 21:21:40 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/10 19:24:21 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include "ft_ls.h"

static int			get_dcs(t_queue **dcs, t_list *paths)
{
	t_queue		*files;
	t_queue		*new;
	t_fstats	**ptr;
	int			err;

	if (!dcs)
		return (-1);
	*dcs = NULL;
	files = NULL;
	ptr = NULL;
	err = 0;
	while (paths)
	{
		new = ft_queue_new((char*)paths->content);
		if ((new->total = get_dir_content(new)) == -1)
		{
			ft_queue_free(&new);
			if (!files)
				files = ft_queue_new(NULL);
			if ((files->total = get_file_content(files, &ptr, (char*)paths->content)) == -1)
			{
				ft_queue_free(&files);
				ft_lsprint_fd(2, "%s: %s: %s\n", PRGM_NAME, paths->content, \
				strerror(errno));
				err += (err == 0);
			}
		}
		else
			ft_queue_pb(dcs, new);
		paths = paths->next;
	}
	if (files)
		ft_queue_pf(dcs, files);
	return (err);
}

static void			print_dcs(t_queue *dcs, int add_nl)
{
	t_queue		*tmp;
	t_list		*reclst;

	reclst = NULL;
	tmp = dcs;
	while (tmp)
	{
		if (tmp != dcs || add_nl)
			ft_putchar('\n');
		if (((dcs->next) || add_nl) && tmp->dname)
			ft_lsprint("%s:\n", tmp->dname);
		print_elems(tmp, &reclst);
		if (reclst)
		{
			list_dirs(reclst, 1);
			ft_lstdel(&reclst, &ft_lstdelf);
		}
		tmp = tmp->next;
	}
}

int					list_dirs(t_list *paths, int add_nl)
{
	int			err;
	t_queue		*dcs;

	ft_lstsort(&paths, &ft_lst_sortalpha);
	err = get_dcs(&dcs, paths);
	print_dcs(dcs, add_nl);
	ft_queue_del(&dcs);
	return (err);
}
