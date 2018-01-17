/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_sorting_comps.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdumarai <kdumarai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 21:23:13 by kdumarai          #+#    #+#             */
/*   Updated: 2018/01/17 17:50:49 by kdumarai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** SORT FUNCTIONS RETURN:
**	1 if swapping is needed
**	0 if swapping is not needed
*/

int		sort_alpha(t_elem *a, t_elem *b, int rev)
{
	int			diff;

	if (!a->fname || !b->fname)
		return (0);
	diff = ft_strcmp(a->fname, b->fname);
	if (diff == 0)
		return (0);
	return ((diff > 0) == !rev);
}

int		sort_mtime(t_elem *a, t_elem *b, int rev)
{
	if (a->st.st_mtime == b->st.st_mtime)
		return (sort_alpha(a, b, rev));
	return ((a->st.st_mtime < b->st.st_mtime) == !rev);
}
