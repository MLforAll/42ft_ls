/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_queuing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/23 21:21:40 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/04 06:13:45 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include "ft_ls.h"

static int			get_dcs(t_queue **dcs, t_list *paths, int optsb)
{
	t_queue		*new;
	int			err;

	if (!dcs)
		return (-1);
	*dcs = NULL;
	err = 0;
	while (paths)
	{
		new = ft_queue_new(paths->content);
		if ((new->total = get_dir_content(new, OPTEXISTS(optsb, A_AOPT))) == -1)
		{
			ft_strdel(&new->dname);
			free(new);
			ft_miniprintf("%s: %s: %s\n", PRGM_NAME, paths->content, \
				strerror(errno));
			err += (err == 0);
		}
		else
			ft_queue_pb(dcs, new);
		paths = paths->next;
	}
	return (err);
}

int					list_dirs(t_list *paths, int optsb, int add_nl)
{
	int			err;
	t_queue		*dcs;

	ft_lstsort(&paths, &ft_lst_sortalpha);
	err = get_dcs(&dcs, paths, optsb);
	print_dcs(dcs, optsb, add_nl);
	ft_queue_del(&dcs);
	return (err);
}
