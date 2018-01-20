/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_misc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 01:51:57 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/20 20:46:04 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "ft_ls.h"

/*
** Utilities functions
** Or functions I didn't know where to put
*/

void		fillinf(size_t *dest, size_t new)
{
	if (*dest < new)
		*dest = new;
}

void		ls_elem_err(char *path, int err)
{
	char	*elem_name;

	if (err == ENOENT || err == ENOTDIR)
		elem_name = path;
	else
	{
		elem_name = ft_strrchr(path, '/');
		elem_name = (!elem_name) ? path : elem_name + 1;
	}
	ft_lsprint_fd(2, "%s: %s: %s\n", PRGM_NAME, elem_name, strerror(err));
}

int			optexists(int opt)
{
	return (((g_opts & opt) != 0));
}

void		launch_groups_sort(t_group **grps)
{
	if (optexists(A_TOPT) || optexists(A_ROPT))
		ft_group_mergesort(grps, \
			optexists(A_TOPT) ? &ft_group_sortmtime : &ft_group_sortalpha, \
			optexists(A_ROPT));
}
