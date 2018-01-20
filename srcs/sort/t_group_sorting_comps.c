/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_group_sorting_comps.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 21:23:13 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/20 22:00:34 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_group_sortalpha(t_group *a, t_group *b, int rev)
{
	int			diff;

	if (!a->grp_name || !b->grp_name)
		return (0);
	diff = ft_strcmp(a->grp_name, b->grp_name);
	if (diff == 0)
		return (0);
	return ((diff > 0) == !rev);
}

int		ft_group_sortmtime(t_group *a, t_group *b, int rev)
{
	t_stat	sta;
	t_stat	stb;

	if (lstat(a->grp_name, &sta) == -1
		|| lstat(b->grp_name, &stb) == -1)
		return (0);
	if (sta.st_mtime == stb.st_mtime)
	{
		if (sta.st_mtimespec.tv_nsec == stb.st_mtimespec.tv_nsec)
			return (ft_group_sortalpha(a, b, rev));
		return ((sta.st_mtimespec.tv_nsec < stb.st_mtimespec.tv_nsec) == !rev);
	}
	return ((sta.st_mtime < stb.st_mtime) == !rev);
}
