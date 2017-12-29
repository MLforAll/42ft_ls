/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_queuing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/23 21:21:40 by kdumarai          #+#    #+#             */
/*   Updated: 2017/12/29 18:05:01 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "ft_ls.h"

#include <stdio.h>

/*
** printf is later to be replaced by ft_printf
** or perhaps maybe some putstrs..
*/

static int			get_dcs(t_queue **dcs, t_list *paths)
{
	t_fstats	*dc;
	int			total;
	int			err;

	if (!dcs)
		return (-1);
	*dcs = NULL;
	err = 0;
	while (paths)
	{
		if ((total = get_dir_content(paths->content, &dc)) == -1)
		{
			printf("%s: %s: %s\n", PRGM_NAME, paths->content, strerror(errno));
			err += (err == 0);
		}
		else
			ft_queue_pb(dcs, paths->content, dc, total);
		paths = paths->next;
	}
	return (err);
}

int					list_dirs(t_list *paths, int optsb, int add_nl)
{
	int			err;
	t_queue		*dcs;

	err = get_dcs(&dcs, paths);
	print_dcs(dcs, optsb, add_nl);
	ft_queue_del(&dcs);
	return (err);
}